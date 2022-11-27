#pragma once
#include <vector>
#include <stdint.h>
struct pixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
    uint8_t&operator [](unsigned);
    const uint8_t&operator [](unsigned)const;
};
using bitmap=std::vector<std::vector<pixel>>;

