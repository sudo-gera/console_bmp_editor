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

auto open_file(string filename){
    const char*file=filename.c_str();
    int fd=open(file,O_RDWR);
    if (errno){perror(nullptr);exit(1);}
    struct stat st;
    lstat(file,&st);
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
};

#ifdef HOME
template<llu n>
auto&operator<<(ostream&o,const chars<n>&q){
    q.out(o);
    return o;
}
#endif

template<llu l,llu n>
struct dib_fields_s{
    using type=chars<((l/13)*(l/13)+l/20+36/l+32/l>n)*2*(2-(n+10*(l==12)+1)/4%2+((n+10*(l==12)+11)%16<2))>;
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
    field<l,11> enum_for_units_of_resolutions;
    field<l,12> padding;
    field<l,13> enum_for_direction_of_fill;
    field<l,14> enum_for_halftoning_algorithm;
    field<l,15> halftoning_parameter1;
    field<l,16> halftoning_parameter2;
    field<l,17> enum_for_color_encoding;
    field<l,18> app_defined_identifer;
};

static_assert(sizeof(dib<12>)==12);
static_assert(sizeof(dib<16>)==16);
static_assert(sizeof(dib<40>)==40);
static_assert(sizeof(dib<64>)==64);

struct BITMAPCOREHEADER{
    chars<4> size_of_header;
    chars<2> bitmap_width;
    chars<2> bitmap_height;
    chars<2> number_of_color_planes;
    chars<2> number_of_bits_per_pixel;
};

static_assert(sizeof(BITMAPCOREHEADER)==12);

struct BITMAPINFOHEADER{
    chars<4> size_of_header;
    chars<4> bitmap_width;
    chars<4> bitmap_height;
    chars<2> number_of_color_planes;
    chars<2> number_of_bits_per_pixel;
    chars<4> way_of_compression;
    chars<4> size_of_raw_data;
    chars<4> horizontal_resolution_pixel_per_metre;
    chars<4> vertical_resolution_pixel_per_metre;
    chars<4> number_of_colors_in_color_palete;
    chars<4> number_of_important_colors;
};

static_assert(sizeof(BITMAPINFOHEADER)==40);

struct OS22XBITMAPHEADER_1{
    chars<4> size_of_header;
    chars<4> bitmap_width;
    chars<4> bitmap_height;
    chars<2> number_of_color_planes;
    chars<2> number_of_bits_per_pixel;
    chars<4> way_of_compression;
    chars<4> size_of_raw_data;
    chars<4> horizontal_resolution_pixel_per_metre;
    chars<4> vertical_resolution_pixel_per_metre;
    chars<4> number_of_colors_in_color_palete;
    chars<4> number_of_important_colors;
    chars<2> enum_for_units_of_resolutions;
    chars<2> padding;
    chars<2> enum_for_direction_of_fill;
    chars<2> enum_for_halftoning_algorithm;
    chars<4> halftoning_parameter1;
    chars<4> halftoning_parameter2;
    chars<4> enum_for_color_encoding;
    chars<4> app_defined_identifer;
};

static_assert(sizeof(OS22XBITMAPHEADER_1)==64);

struct OS22XBITMAPHEADER_2{
    chars<4> size_of_header;
    chars<4> bitmap_width;
    chars<4> bitmap_height;
    chars<2> number_of_color_planes;
    chars<2> number_of_bits_per_pixel;
};

static_assert(sizeof(OS22XBITMAPHEADER_2)==16);

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

void bmp_parse(char*data,llu len){
    send_error(len<=sizeof(bitmap_file_header),"file is too small");
    // print(*(bitmap_file_header*)(data));
    vector<decltype(&_dib[0])> pos;
    for (auto&w:_dib){
        if (w.first==data[sizeof(bitmap_file_header)]){
            pos.push_back(&w);
        }
    }
    send_error(pos.empty(),"unknown bmp header");
    auto l=[&](auto q){
        using dib=remove_reference_t<decltype(*q)>;
        print(*(bitmap_file_header*)(data));
        print(*(dib*)(data+sizeof(bitmap_file_header)));
        
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
    if (pos[0][0].first==64){
        l((dib<64>*)nullptr);
    }else{
        send_error(1,"unsupported bmp header: "+pos[0][0].second);
    }
}

int main(){
    auto uptr=open_file("test1.bmp");
    char*data=uptr->first;
    llu len=uptr->second;
    bmp_parse(data,len);
}




