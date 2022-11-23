#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "bmp_lib.hpp"
using namespace std;
    
using llu=long long unsigned;
using lli=long long int;

using universal=variant<const char*,vector<vector<pixel>>>;

template<typename T>
llu setup_var(const vector<universal>&args,T& var,llu&index){
    visit([&](const auto&q){
        if constexpr (requires{var=q;}){
            var=q;
        }else{
            cerr<<"type error"<<endl;
            throw exception();
        }
    },args.at(index++));
    return 0;
}

template<typename...T>
void setup_vars(const vector<universal>&args,T&...vars){
    llu index=0;
    llu data[]={setup_var(args,vars,index)...};
}

int main(int argc,char**argv){
    map<string,universal> vars;
    map<string,function<universal(vector<universal>)>> funs;
    funs["read"]=[](const vector<universal>&args){
        const char*filename;
        setup_vars(args,filename);
        return bmp_read(filename);
    };
    funs["pwd"]=[](const vector<universal>&args){
        system("pwd");
        return nullptr;
    };
    funs["ls"]=[](const vector<universal>&args){
        system("ls");
        return nullptr;
    };
    funs["write"]=[](const vector<universal>&args){
        vector<vector<pixel>>data;
        const char*filename;
        setup_vars(args,data,filename);
        bmp_write(data,filename);
        return nullptr;
    };
    funs["negative"]=[](const vector<universal>&args){
        vector<vector<pixel>>data;
        setup_vars(args,data);
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
    for (llu w=1;w<argc;){
        if (w+2<argc and argv[w]=="string"s){
            vars[argv[w+1]]=argv[w+2];
            w+=3;
        }else
        if (w+2<argc and argv[w+1]=="["s){
            llu e=w+2;
            while (e+1<=argc and argv[e]!="]"s){
                ++e;
            }
            if (argv[e]!="]"s){
                cerr<<"args error"<<endl;
                throw exception();
            }
            vector<universal> args;
            for (llu q=w+2;q<e;++q){
                args.push_back(vars.at(argv[q]));
            }
            funs.at(argv[w])(args);
            w=e+1;
        }else
        if (w+4<argc and argv[w+1]=="="s and argv[w+3]=="["s){
            llu e=w+4;
            while (e+1<=argc and argv[e]!="]"s){
                ++e;
            }
            if (argv[e]!="]"s){
                cerr<<"args error"<<endl;
                throw exception();
            }
            vector<universal> args;
            for (llu q=w+4;q<e;++q){
                args.push_back(vars.at(argv[q]));
            }
            vars[argv[w]]=funs.at(argv[w+2])(args);
            w=e+1;
        }else
        if (w+2<argc and argv[w+1]=="="s){
            vars[argv[w]]=vars.at(argv[w+2]);
            w=w+3;
        }else{
            cerr<<"args error"<<endl;
            throw exception();
        }
    }
}