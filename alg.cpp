#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <variant>
#include <functional>
#include "alg.hpp"
using namespace std;

using llu=long long unsigned;
using lli=long long int;

bitmap same(bitmap data){
    return data;
}

bitmap negative(bitmap data){
    for (auto&q:data){
        for (auto&w:q){
            w.alpha=~w.alpha;
            w.blue=~w.blue;
            w.green=~w.green;
            w.red=~w.red;
        }
    }
    return data;
};

bitmap scale(const bitmap &in,llu z,llu x){
    if (z*x==0){
        cerr<<"size must not be zero"<<endl;
        throw exception();
    }
    bitmap out;
    llu a=0,s=0;
    a=in.size();
    s=a?in[0].size():0;
    for (llu q=0;q<z;++q){
        out.emplace_back();
        for (llu w=0;w<x;++w){
            out.back().emplace_back();
            for (llu e=0;e<4;++e){
                out.back().back()[e]=(
                    in[    q*a/z               ][    w*s/x               ][e]*((z-1-q*a%z)*(x-1-w*s%x))+
                    in[min(q*a/z+!!(q*a%z),a-1)][min(w*s/x+!!(w*s/x),s-1)][e]*((    q*a%z)*(    w*s%x))+
                    in[    q*a/z               ][min(w*s/x+!!(w*s/x),s-1)][e]*((z-1-q*a%z)*(    w*s%x))+
                    in[min(q*a/z+!!(q*a%z),a-1)][    w*s/x               ][e]*((    q*a%z)*(x-1-w*s%x))
                )/z/x;
            }
        }
    }
    return out;
};



