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
        throw exception();
    }
}

auto open_file(string filename,llu len=-1){
    const char*file=filename.c_str();
    int fd=open(file,len==-1 ? O_RDWR : (O_RDWR|O_CREAT|O_TRUNC));
    if (errno){
        perror(nullptr);
        throw exception();
    }
    if (len==-1){
        struct stat st;
        lstat(file,&st);
        len=st.st_size;
    }else{
        ftruncate(fd,len);
    }
    if (errno){
        perror(nullptr);
        close(fd);
        throw exception();
    }
    char*data=(char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (errno){
        perror(nullptr);
        close(fd);
        throw exception();
    }
    close(fd);
    if (errno){
        perror(nullptr);
        munmap(data,len);
        throw exception();
    }
    pair t(data,len);
    auto p=new pair(data,len);
    auto d=[](auto p){
        munmap(p->first,p->second);
        delete p;
    };
    unique_ptr<decltype(t),decltype(d)> u(p,d);
    return u;
}

template<llu n>
struct sized_int_s{
    using type=tuple_element_t<min("-\x00\x01-\x02---\x03-"[min(n,9LLU)]+0,4),tuple<int8_t,int16_t,int32_t,int64_t,void>>;
};

template<llu n>
using sized_int=typename sized_int_s<n>::type;

static_assert(is_same_v<sized_int< 0>,void>);
static_assert(is_same_v<sized_int< 1>,int8_t>);
static_assert(is_same_v<sized_int< 2>,int16_t>);
static_assert(is_same_v<sized_int< 3>,void>);
static_assert(is_same_v<sized_int< 4>,int32_t>);
static_assert(is_same_v<sized_int< 5>,void>);
static_assert(is_same_v<sized_int< 6>,void>);
static_assert(is_same_v<sized_int< 7>,void>);
static_assert(is_same_v<sized_int< 8>,int64_t>);
static_assert(is_same_v<sized_int< 9>,void>);
static_assert(is_same_v<sized_int<10>,void>);
static_assert(is_same_v<sized_int<11>,void>);
static_assert(is_same_v<sized_int<12>,void>);
static_assert(is_same_v<sized_int<13>,void>);
static_assert(is_same_v<sized_int<14>,void>);
static_assert(is_same_v<sized_int<15>,void>);

template<llu n>
struct chars{
    char data[n];
    operator sized_int<n>(){
        sized_int<n> res;
        memmove(&res,data,n);
        return res;
    }
};

#ifdef py_func
    py_func(print_data)({
        def print_data(data):
            return f"{int.from_bytes(bytearray(data),'little')}"
            return f"(repr={bytearray(data)}, list={data}, int={int.from_bytes(bytearray(data),'little')})"
    })

    template<llu n>
    auto&operator<<(ostream&o,const chars<n>&q){
        o<<string(print_data(vector<uint8_t>(q.data,q.data+n)));
        return o;
    }
#endif

consteval llu field_size_prefix(llu l,llu n){
    if (n==32){
        return l;
    }
    array<llu,64> a;
    for (auto&w:a){
        w=4;
    }
    if (l<16){
        a[1]=2;
        a[2]=2;
    }
    a[4]=2;
    a[3]=2;
    if (n==0){
        return 0;
    }
    llu prev=field_size_prefix(l,n-1);
    if (prev+a[n-1]>l){
        return prev;
    }else{
        return prev+a[n-1];
    }
}

static_assert(field_size_prefix(16,0)==0);
static_assert(field_size_prefix(16,1)==4);
static_assert(field_size_prefix(16,2)==8);
static_assert(field_size_prefix(16,3)==12);
static_assert(field_size_prefix(16,4)==14);
static_assert(field_size_prefix(16,5)==16);
static_assert(field_size_prefix(16,6)==16);
static_assert(field_size_prefix(16,16)==16);
static_assert(field_size_prefix(12,0)==0);
static_assert(field_size_prefix(12,1)==4);
static_assert(field_size_prefix(12,2)==6);
static_assert(field_size_prefix(12,3)==8);
static_assert(field_size_prefix(12,4)==10);
static_assert(field_size_prefix(12,5)==12);
static_assert(field_size_prefix(12,12)==12);

template<llu l,llu n>
using field=chars<field_size_prefix(l,n+1)-field_size_prefix(l,n)>;

struct bitmap_file_header{
    chars<2> header_field;
    chars<4> size_of_file_in_bytes;
    chars<2> reserved1;
    chars<2> reserved2;
    chars<4> starting_address_of_data; 
};

static_assert(sizeof(bitmap_file_header)==14);

template<llu l>
struct device_independent_bitmap{
    field<l, 0> size_of_header;
    field<l, 1> bitmap_width;
    field<l, 2> bitmap_height;
    field<l, 3> number_of_color_planes;
    field<l, 4> number_of_bits_per_pixel;
    field<l, 5> way_of_compression;
    field<l, 6> size_of_raw_data;
    field<l, 7> horizontal_resolution_pixel_per_metre;
    field<l, 8> vertical_resolution_pixel_per_metre;
    field<l, 9> number_of_colors_in_color_palette;
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
    constexpr static llu size=l;
};

static_assert(sizeof(device_independent_bitmap<12>)==12);
static_assert(sizeof(device_independent_bitmap<16>)==16);
static_assert(sizeof(device_independent_bitmap<40>)==40);
static_assert(sizeof(device_independent_bitmap<64>)==64);
static_assert(sizeof(device_independent_bitmap<108>)==108);
static_assert(sizeof(device_independent_bitmap<124>)==124);



#define get_bit(a,s)   (((a)[(s)/8LLU/sizeof((a)[0])]>>(s)%(8LLU*sizeof((a)[0])))&1LLU)
#define set_bit(a,s,d) {(a)[(s)/8LLU/sizeof((a)[0])]&=~(1LLU<<(s)%(8LLU*sizeof((a)[0])));(a)[(s)/8LLU/sizeof((a)[0])]+=((d)+0LLU)<<(s)%(8LLU*sizeof((a)[0]));}

struct pixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
};

template<llu l>
void bmp_parse(char*data,llu len,vector<vector<pixel>>&end){
    using device_independent_bitmap_l=device_independent_bitmap<l>;
    static_assert(sizeof(device_independent_bitmap_l)==device_independent_bitmap_l::size);
    send_error(len<sizeof(bitmap_file_header)+sizeof(device_independent_bitmap_l),"file is too small");
    assert(data[sizeof(bitmap_file_header)]==sizeof(device_independent_bitmap_l));
    bitmap_file_header&bit_data=*(bitmap_file_header*)(data);
    auto&device_independent_bitmap_data=*(device_independent_bitmap_l*)(data+sizeof(bitmap_file_header));
    if constexpr(sizeof(device_independent_bitmap_l)>=40){
        string comps[]={
            "RGB",
            "RLE8",
            "RLE4",
            "BITFIELDS",
            "JPEG",
            "PNG",
            "ALPHABITFIELDS",
            "CMYK",
            "CMYK",
            "CMYK",
            "CMYK",
            "CMYK",
            "CMYKRLE8",
            "CMYKRLE4",
        };
        send_error(device_independent_bitmap_data.way_of_compression,"compression method "+comps[device_independent_bitmap_data.way_of_compression]+" is not supported");
    }
    char*colors=(data+sizeof(bitmap_file_header)+sizeof(device_independent_bitmap_l));
    char*main=data+(int)bit_data.starting_address_of_data;
    llu horizontal_len=0;
    llu width=0;
    llu height=0;
    if constexpr(sizeof(device_independent_bitmap_data.bitmap_width)==2){
        width=device_independent_bitmap_data.bitmap_width;
    }else{
        width=device_independent_bitmap_data.bitmap_width;
    }
    if constexpr(sizeof(device_independent_bitmap_data.bitmap_height)==2){
        height=device_independent_bitmap_data.bitmap_height;
    }else{
        height=device_independent_bitmap_data.bitmap_height;
    }
    llu from_top=0;
    if ((lli)height<0){
        height=-height;
        from_top=1;
    }
    horizontal_len=(device_independent_bitmap_data.number_of_bits_per_pixel*width+31)/32*4;
    send_error(main+height*horizontal_len>data+len,"file is too small");
    for (llu w=0;w<height;++w){
        end.emplace_back();
        vector<char> line(main+w*horizontal_len,main+(w+1)*horizontal_len);
        for (llu e=0;e<width;++e){
            llu res=0;
            llu bit_len=device_independent_bitmap_data.number_of_bits_per_pixel;
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
}


template<llu b=12,llu e=128>
auto get_bmp_parse(llu n){
    assert(b<=n and n<e);
    if constexpr(b+1==e){
        return bmp_parse<b>;
    }else if (n<(b+e)/2){
        return get_bmp_parse<b,(b+e)/2>(n);
    }else{
        return get_bmp_parse<(b+e)/2,e>(n);
    }
}

auto bmp_read(string filename){
    auto uptr=open_file(filename);
    char*data=uptr->first;
    llu len=uptr->second;
    vector<vector<pixel>> t;
    send_error(len<=sizeof(bitmap_file_header),"file is too small");
    get_bmp_parse(llu(data[sizeof(bitmap_file_header)]))(data,len,t);
    return t;
}

void bmp_write(const vector<vector<pixel>> &a,string filename){
    uint32_t height=a.size();
    uint32_t width=height?a[0].size():0;
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
    auto t=bmp_read("index.bmp");
    bmp_write(t,"test.bmp");
}




