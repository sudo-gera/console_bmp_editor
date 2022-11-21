#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <bits/stdc++.h>
using namespace std;

using llu=long long unsigned;
using lli=long long int;

void send_error(bool con,string mes){
    if (con){
        cerr<<mes<<endl;
        exit(1);
    }
}

auto open_file(string filename,llu len=-1){
    const char*file=filename.c_str();
    int fd=open(file,len==-1 ? O_RDWR : (O_RDWR|O_CREAT|O_TRUNC));
    if (errno){perror(nullptr);exit(1);}
    struct stat st;
    if (len==-1){
        lstat(file,&st);
    }else{
        ftruncate(fd,len);
        st.st_size=len;
    }
    if (errno){perror(nullptr);exit(1);}
    char*mmem=(char*)mmap(NULL,st.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (errno){perror(nullptr);exit(1);}
    close(fd);
    if (errno){perror(nullptr);exit(1);}
    auto p=new pair(mmem,st.st_size);
    auto d=[](auto p){
        munmap(p->first,p->second);
        delete p;
    };
    unique_ptr<remove_reference_t<decltype(*p)>,decltype(d)> u(p,d);
    return u;
}

#ifdef HOME
py_func(print_data)({
    def print_data(data):
        return f"{int.from_bytes(bytearray(data),'little')}"
        return f"(repr={bytearray(data)}, list={data}, int={int.from_bytes(bytearray(data),'little')})"
})
#endif

template<llu n>
struct chars{
    char data[n];
    // array<char,n> data;
#ifdef HOME
    void out(ostream&o)const{
        o<<string(print_data(vector<uint8_t>(data,data+n)));
    }
#endif
    template<typename Y,typename=enable_if_t<sizeof(Y)==n,void>>
    operator Y(){
        Y res;
        memmove(&res,data,sizeof(Y));
        return res;
    }
};

#ifdef HOME
template<llu n>
auto&operator<<(ostream&o,const chars<n>&q){
    q.out(o);
    return o;
}
#endif

consteval llu field_size(llu l,llu n){
    array<llu,64> a;
    for (auto&w:a){
        w=4;
    }
    if (l==12){
        a[1]=2;
        a[2]=2;
    }
    a[4]=2;
    a[3]=2;
    llu sum=0;
    for (llu w=0;w<n;++w){
        sum+=a[w];
    }
    return (sum<l)*a[n];
}

template<llu l,llu n>
struct dib_fields_s{
    using type=chars<field_size(l,n)>;
};

template<llu l,llu n>
using field=typename dib_fields_s<l,n>::type;

struct bitmap_file_header{
    chars<2> header_field;
    chars<4> size_of_file_in_bytes;
    chars<2> reserved1;
    chars<2> reserved2;
    chars<4> starting_address_of_data; 
};

static_assert(sizeof(bitmap_file_header)==14);

template<llu l>
struct dib{
    field<l, 0> size_of_header;
    field<l, 1> bitmap_width;
    field<l, 2> bitmap_height;
    field<l, 3> number_of_color_planes;
    field<l, 4> number_of_bits_per_pixel;
    field<l, 5> way_of_compression;
    field<l, 6> size_of_raw_data;
    field<l, 7> horizontal_resolution_pixel_per_metre;
    field<l, 8> vertical_resolution_pixel_per_metre;
    field<l, 9> number_of_colors_in_color_palete;
    field<l,10> number_of_important_colors;
    field<l,11> red_mask;
    field<l,12> green_mask;
    field<l,13> blue_mask;
    field<l,14> alpha_mask;
    field<l,15> color_space_type;
    field<l,16> red_x_2_30;
    field<l,17> red_y_2_30;
    field<l,18> red_z_2_30;
    field<l,19> green_x_2_30;
    field<l,20> green_y_2_30;
    field<l,21> green_z_2_30;
    field<l,22> blue_x_2_30;
    field<l,23> blue_y_2_30;
    field<l,24> blue_z_2_30;
    field<l,25> red_gamma;
    field<l,26> green_gamma;
    field<l,27> blue_gamma;
    field<l,28> intent;
    field<l,29> profile_data;
    field<l,30> profile_size;
    field<l,31> reserved;
};

static_assert(sizeof(dib<12>)==12);
static_assert(sizeof(dib<16>)==16);
static_assert(sizeof(dib<40>)==40);
static_assert(sizeof(dib<64>)==64);
static_assert(sizeof(dib<108>)==108);
static_assert(sizeof(dib<124>)==124);


vector<pair<llu,string>> _dib={
    {12,"BITMAPCOREHEADER"},
    {64,"OS22XBITMAPHEADER_1"},
    {16,"OS22XBITMAPHEADER_2"},
    {40,"BITMAPINFOHEADER"},
    {52,"BITMAPV2INFOHEADER"},
    {56,"BITMAPV3INFOHEADER"},
    {108,"BITMAPV4HEADER"},
    {124,"BITMAPV5HEADER"},
};

#define get_bit(a,s)   (((a)[(s)/8LLU/sizeof((a)[0])]>>(s)%(8LLU*sizeof((a)[0])))&1LLU)
#define set_bit(a,s,d) {(a)[(s)/8LLU/sizeof((a)[0])]&=~(1LLU<<(s)%(8LLU*sizeof((a)[0])));(a)[(s)/8LLU/sizeof((a)[0])]+=((d)+0LLU)<<(s)%(8LLU*sizeof((a)[0]));}

struct pixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
};

auto bmp_parse(char*data,llu len){
    vector<vector<pixel>> end;
    send_error(len<=sizeof(bitmap_file_header),"file is too small");
    vector<decltype(&_dib[0])> pos;
    for (auto&w:_dib){
        if (w.first==data[sizeof(bitmap_file_header)]){
            pos.push_back(&w);
        }
    }
    send_error(pos.empty(),"unknown bmp header");
    auto l=[&](auto q){
        using ldib=remove_reference_t<decltype(*q)>;
        send_error(len<sizeof(bitmap_file_header)+sizeof(ldib),"file is too small");
        assert(pos[0][0].first==sizeof(ldib));
        bitmap_file_header&bit_data=*(bitmap_file_header*)(data);
        dib<sizeof(ldib)>&dib_data=*(ldib*)(data+sizeof(bitmap_file_header));
        if constexpr(sizeof(ldib)>=40){
            send_error((uint32_t)dib_data.way_of_compression%11,"compression is not supported");
        }
        char*colors=(data+sizeof(bitmap_file_header)+sizeof(ldib));
        char*main=data+(int)bit_data.starting_address_of_data;
        llu horizontal_len=0;
        llu width=0;
        llu height=0;
        if constexpr(sizeof(dib_data.bitmap_width)==2){
            width=(uint16_t)dib_data.bitmap_width;
        }else{
            width=(uint32_t)dib_data.bitmap_width;
        }
        if constexpr(sizeof(dib_data.bitmap_height)==2){
            height=(int16_t)dib_data.bitmap_height;
        }else{
            height=(int32_t)dib_data.bitmap_height;
        }
        llu from_top=0;
        if ((lli)height<0){
            height=-height;
            from_top=1;
        }
        horizontal_len=((uint16_t)dib_data.number_of_bits_per_pixel*width+31)/32*4;
        for (llu w=0;w<height;++w){
            end.emplace_back();
            vector<char> line(main+w*horizontal_len,main+(w+1)*horizontal_len);
            for (llu e=0;e<width;++e){
                llu res=0;
                llu bit_len=(uint16_t)dib_data.number_of_bits_per_pixel;
                for (llu r=0;r<bit_len;++r){
                    llu ind=e*bit_len+r;
                    char*place=line.data();
                    place+=ind/8;
                    ind%=8;
                    ind=(7/bit_len-ind/bit_len)*bit_len+ind%bit_len;
                    llu bit=get_bit(place,ind);
                    res|=bit<<r;
                }
                if (main-colors>res*sizeof(pixel)){
                    pixel tmp;
                    memmove(&tmp,colors+res*sizeof(pixel),sizeof(pixel));
                    end.back().push_back(tmp);
                }else{
                    pixel tmp;
                    memmove(&tmp,&res,sizeof(pixel));
                    if (bit_len==16){
                        tmp.blue=(res&0b11111)*8;
                        tmp.green=(res>>5&0b11111)*8;
                        tmp.red=(res>>10&0b11111)*8;
                        tmp.alpha=(res>>15&0b11111)*8;
                    }
                    end.back().push_back(tmp);
                }
            }
        }
        if (from_top){
            reverse(end.begin(),end.end());
        }
    };
    if (pos[0][0].first==12){
        l((dib<12>*)nullptr);
    }else
    if (pos[0][0].first==16){
        l((dib<16>*)nullptr);
    }else
    if (pos[0][0].first==40){
        l((dib<40>*)nullptr);
    }else
    if (pos[0][0].first==52){
        l((dib<52>*)nullptr);
    }else
    if (pos[0][0].first==64){
        l((dib<64>*)nullptr);
    }else
    if (pos[0][0].first==108){
        l((dib<108>*)nullptr);
    }else
    if (pos[0][0].first==124){
        l((dib<124>*)nullptr);
    }else{
        send_error(1,"unsupported bmp header: "+pos[0][0].second);
    }
    return end;
}

void bmp_write(const vector<vector<pixel>> &a,string filename){
    uint32_t height=a.size();
    uint32_t width=a[0].size();
    auto uptr=open_file(filename,height*width*4+54);
    uint32_t*data=(uint32_t*)(uptr->first);
    llu len=uptr->second;
    data++[0]=height * width * 4 + 54;
    data++[0]=0;
    data++[0]=54;
    data++[0]=40;
    data++[0]=width;
    data++[0]=height;
    data++[0]=2097153;
    data++[0]=0;
    data++[0]=height * width * 4;
    data++[0]=1;
    data++[0]=1;
    data++[0]=0;
    data++[0]=0;
    for (auto&q:a){
        for (auto&w:q){
            data++[0]=(uint32_t&)w;
        }
    }
    char*cdata=uptr->first;
    memmove(cdata+2,cdata,len-2);
    cdata[0]='B';
    cdata[1]='M';
}

int main(){
    auto uptr=open_file("test16.bmp");
    char*data=uptr->first;
    llu len=uptr->second;
    auto t=bmp_parse(data,len);
    bmp_write(t,"test.bmp");
}




