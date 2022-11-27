#include "pix.hpp"
const uint8_t&pixel::operator[](unsigned l)const{
    return ((uint8_t*)(this))[l];
}

uint8_t&pixel::operator[](unsigned l){
    return ((uint8_t*)(this))[l];
}

