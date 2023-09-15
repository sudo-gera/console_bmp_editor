#pragma once
#include <vector>
#include <stdint.h>
// #define log {printf("%s%i%s%s%s%s\n","line: ",(int)__LINE__," file: ",__FILE__," func: ",__PRETTY_FUNCTION__);fflush(stdout);}
struct pixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
    uint8_t&operator [](unsigned);
    const uint8_t&operator [](unsigned)const;
};
using bitmap=std::vector<std::vector<pixel>>;

