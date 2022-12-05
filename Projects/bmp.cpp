#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include <string>
#include <tuple>
#include <memory.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string_view>
#include "bmp.hpp"
using namespace std;

using llu=long long unsigned;
using lli=long long int;

void send_error(bool con,string mes){
    if (con){
        cerr<<mes<<endl;
        throw exception();
    }
}

#ifdef NO_MMAP
    auto portable_mmap(const string&filename,llu len){
        char*data=nullptr;
        if (len==-1){
            ifstream f(filename);
            stringstream ss;
            ss<<f.rdbuf();
            string s=ss.str();
            len=s.size();
            data=(char*)new uint32_t[len/4+!!(len%4)];
            memmove(data,s.data(),s.size());
        }else{
            data=(char*)new uint32_t[len/4+!!(len%4)];
        }
        pair t(data,len);
        return t;
    }
    auto portable_munmap(const string&filename,char*data,llu len){
        ofstream f(filename);
        f<<string_view(data,data+len);
        delete[] data;
    }
#else
    auto portable_mmap(const string&filename,llu len){
        const char*file=filename.c_str();
        int fd=open(file,len==-1LLU ? O_RDWR : (O_RDWR|O_CREAT|O_TRUNC), S_IRWXU|S_IRWXG|S_IRWXO);
        if (errno){
            perror(file);
            throw exception();
        }
        if (len==-1LLU){
            struct stat st;
            lstat(file,&st);
            len=(llu)st.st_size;
        }else{
            int tmp=ftruncate(fd,len);
        }
        if (errno){
            perror((to_string(len)+" lstat|ftruncate").c_str());
            close(fd);
            throw exception();
        }
        char*data=(char*)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        if (errno){
            perror("mmap");
            close(fd);
            throw exception();
        }
        close(fd);
        if (errno){
            perror("close");
            munmap(data,len);
            throw exception();
        }
        pair t(data,len);
        return t;
    }
    auto portable_munmap(const string&filename,char*data,llu len){
        munmap(data,len);
    }
#endif



auto open_file(const string&filename,llu len=-1LLU){
    errno=0;
    auto _t=portable_mmap(filename,len);
    pair t(filename,_t);
    auto p=new auto(t);
    auto d=[=](auto p){
        auto&t=*p;
        portable_munmap(t.first,t.second.first,t.second.second);
        delete p;
    };
    unique_ptr<decltype(t),decltype(d)> u(p,d);
    return u;
}

template<llu n>
struct chars{
    char data[n];
    operator lli(){
        lli t=0;
        memmove(&t,data,min(n,8LLU));
        return t;
    }
    auto&operator=(lli t){
        memmove(data,&t,min(n,8LLU));
        return *this;
    }
};

struct bitmap_file_header{
    chars<2> header_field;
    chars<4> size_of_file_in_bytes;
    chars<2> reserved1;
    chars<2> reserved2;
    chars<4> starting_address_of_data; 
};

struct device_independent_bitmap{
    chars<4> size_of_header;
    chars<4> bitmap_width;
    chars<4> bitmap_height;
    chars<2> number_of_color_planes;
    chars<2> number_of_bits_per_pixel;
    chars<4> way_of_compression;
    chars<4> size_of_raw_data;
    chars<4> horizontal_resolution_pixel_per_metre;
    chars<4> vertical_resolution_pixel_per_metre;
    chars<4> number_of_colors_in_color_palette;
    chars<4> number_of_important_colors;
    chars<4> red_mask;
    chars<4> green_mask;
    chars<4> blue_mask;
    chars<4> alpha_mask;
    chars<4> color_space_type;
    chars<4> red_x_2_30;
    chars<4> red_y_2_30;
    chars<4> red_z_2_30;
    chars<4> green_x_2_30;
    chars<4> green_y_2_30;
    chars<4> green_z_2_30;
    chars<4> blue_x_2_30;
    chars<4> blue_y_2_30;
    chars<4> blue_z_2_30;
    chars<4> red_gamma;
    chars<4> green_gamma;
    chars<4> blue_gamma;
    chars<4> intent;
    chars<4> profile_data;
    chars<4> profile_size;
    chars<4> reserved;
};

#define get_bit(a,s)   (((a)[(s)/8LLU/sizeof((a)[0])]>>(s)%(8LLU*sizeof((a)[0])))&1LLU)
#define set_bit(a,s,d) {(a)[(s)/8LLU/sizeof((a)[0])]&=~(1LLU<<(s)%(8LLU*sizeof((a)[0])));(a)[(s)/8LLU/sizeof((a)[0])]+=((d)+0LLU)<<(s)%(8LLU*sizeof((a)[0]));}

#include "/Users/gera/c/d"

bitmap bmp_read(string filename){
    auto uptr=open_file(filename);
    char*data=uptr->second.first;
    llu len=uptr->second.second;
    bitmap t;
    send_error(len<=sizeof(bitmap_file_header),"file is too small");
    llu sizeof_dib_data=data[sizeof(bitmap_file_header)];
    send_error (len < sizeof(bitmap_file_header) + sizeof_dib_data, "file is too small");
    send_error (sizeof_dib_data<12, "file is too small");
    auto dib_ptr = (data + sizeof(bitmap_file_header));
    bitmap_file_header bit_data;
    device_independent_bitmap dib_data;
    memset(&dib_data,0,sizeof(dib_data));
    char* dibs[]={dib_ptr,dib_ptr,dib_ptr,dib_ptr,dib_ptr};
    dibs[0]+= 0;
    dibs[1]+= 4;
    dibs[2]+= 8-2*(sizeof_dib_data<16);
    dibs[3]+=12-4*(sizeof_dib_data<16);
    dibs[4]+=sizeof_dib_data;
    memmove(&dib_data.size_of_header,dibs[0],dibs[1]-dibs[0]);
    memmove(&dib_data.bitmap_width,dibs[1],dibs[2]-dibs[1]);
    memmove(&dib_data.bitmap_height,dibs[2],dibs[3]-dibs[2]);
    memmove(&dib_data.number_of_color_planes,dibs[3],dibs[4]-dibs[3]);
    memmove(&bit_data,data,sizeof(bit_data));
    vector<pair<llu,string>> comps={
        {0,"RGB",},
        {1,"RLE8",},
        {1,"RLE4",},
        {0,"BITFIELDS",},
        {1,"JPEG",},
        {1,"PNG",},
        {1,"ALPHABITFIELDS",},
        {1,"",},
        {1,"",},
        {1,"",},
        {1,"",},
        {1,"CMYK",},
        {1,"CMYKRLE8",},
        {1,"CMYKRLE4",},
    };
    llu comp=dib_data.way_of_compression;
    send_error(comp+0LLU>=comps.size() or comps[comp].second.size()==0,"unknown way of compression: "+to_string(comp));
    send_error(comps[comp].first,"compression method "+comps[comp].second+" is not supported");
    send_error(comp and dib_data.number_of_bits_per_pixel==16,"compression method "+comps[comp].second+" is not supported for 16 bit per pixel bmp");
    char*_colors=(data+sizeof(bitmap_file_header)+sizeof_dib_data);
    char*main=data+bit_data.starting_address_of_data;
    if (comp==3){
        _colors+=12;
        if (_colors>main){
            _colors-=12;
        }
    }
    if (comp==6){
        _colors+=16;
        if (_colors>main){
            _colors-=16;
        }
    }
    vector<char> colors(_colors,main);
    llu horizontal_len=0;
    llu width=0;
    llu height=0;
    width = dib_data.bitmap_width;
    height = dib_data.bitmap_height;
    llu from_top=0;
    if ((lli)height<0){
        height=-height;
        from_top=1;
    }
    horizontal_len=(dib_data.number_of_bits_per_pixel*width+31)/32*4;
    send_error(main+height*horizontal_len>data+len,"file is too small");
    llu counts[4]={32,32,32,32};
    llu bit_len=dib_data.number_of_bits_per_pixel;
    {
        llu masks[4]={
            0b00000000000000000000000011111111,
            0b00000000000000001111111100000000,
            0b00000000111111110000000000000000,
            0b11111111000000000000000000000000,
        };
        if (bit_len==16){
            masks[0]=0b0000000000011111;
            masks[1]=0b0000001111100000;
            masks[2]=0b0111110000000000;
            masks[3]=0b1000000000000000;
        }
        for (llu c=0;c<4;++c){
            while((masks[c]&1)==0){
                masks[c]>>=1;
                counts[c]-=1;
            }
            while((masks[c]&128)==0){
                masks[c]<<=1;
                counts[c]+=1;
            }
        }
    }
    llu masks[4]={
        0b00000000000000000000000011111111,
        0b00000000000000001111111100000000,
        0b00000000111111110000000000000000,
        0b11111111000000000000000000000000,
    };
    if (bit_len==16){
        masks[0]=0b0000000000011111;
        masks[1]=0b0000001111100000;
        masks[2]=0b0111110000000000;
        masks[3]=0b1000000000000000;
    }
    vector<char> line(horizontal_len+4);
    for (llu w=0;w<height;++w){
        t.emplace_back();
        copy(main+w*horizontal_len,main+(w+1)*horizontal_len,line.begin());
        for (llu e=0;e<width;++e){
            llu bit_r=0;
            memmove(&bit_r,line.data()+e*bit_len/8,4LLU);
            t.back().push_back((pixel&)bit_r);
        }
    }
    if (bit_len<8){
        for (llu w=0;w<height;++w){
            for (llu e=0;e<width;++e){
                uint32_t res=0;
                uint32_t bit_r=(uint32_t&)(t[w][e]);
                for (llu r=0;r<bit_len;++r){
                    char*place=(char*)&bit_r;
                    place+=r/8;
                    llu ind=e*bit_len+r;
                    ind%=8;
                    ind=(7/bit_len-ind/bit_len)*bit_len+ind%bit_len;
                    llu bit=(place[0]>>ind)&1LLU;
                    res|=bit<<r;
                }
                t[w][e]=(pixel&)res;
            }
        }
    }
    for (llu w=0;w<height;++w){
        for (llu e=0;e<width;++e){
            llu res=0;
            res=(uint32_t&)t[w][e];
            res&=(1LLU<<bit_len)-1;
            if (colors.size()+0LLU>=(res+1)*sizeof(pixel)){
                pixel tmp;
                memmove(&tmp,colors.data()+res*sizeof(pixel),sizeof(pixel));
                t[w][e]=tmp;
            }else{
                llu tmp[4]={0,0,0,0};
                for (llu c=0;c<4;++c){
                    tmp[c]=res&masks[c];
                    tmp[c]<<=counts[c];
                }
                t[w][e]={
                    ((uint8_t*)(tmp+0))[4],
                    ((uint8_t*)(tmp+1))[4],
                    ((uint8_t*)(tmp+2))[4],
                    ((uint8_t*)(tmp+3))[4],
                };
            }
        }
    }
    if (from_top){
        reverse(t.begin(),t.end());
    }
    return t;
}


void bmp_write(const bitmap&a,string filename){
    uint32_t height=a.size();
    uint32_t width=height?a[0].size():0;
    auto uptr=open_file(filename,height*width*4+54);
    uint32_t*data=(uint32_t*)(uptr->second.first);
    llu len=uptr->second.second;
    data++[0]=height * width * 4 + 54;
    data++[0]=0;
    data++[0]=54;
    data++[0]=40;
    data++[0]=width;
    data++[0]=height;
    data++[0]=(32LLU<<16)+1;
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
    char*cdata=uptr->second.first;
    memmove(cdata+2,cdata,len-2);
    cdata[0]='B';
    cdata[1]='M';
}



