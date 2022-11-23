#include <vector>
#include <string>

struct pixel{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
};

std::vector<std::vector<pixel>> bmp_read(std::string);

void bmp_write(const std::vector<std::vector<pixel>>&,std::string);
