#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <variant>
#include <functional>
#include "bmp_lib.hpp"
using namespace std;
    
using llu=long long unsigned;
using lli=long long int;

using universal=variant<long long,string,vector<vector<pixel>>>;

template<typename To,typename From>
void read_argument(To&to,From&from){
    if constexpr (requires{to=from;}){
        to=from;
    }else{
        cerr<<"type error"<<endl;
        cerr<<__PRETTY_FUNCTION__<<endl;
        throw exception();
    }
}

template<typename T>
llu setup_var(const vector<universal>&args,T& var,llu&index){
    visit([&](const auto&q){
        read_argument(var,q);
    },args.at(index++));
    return 0;
}

template<typename...T>
void setup_vars(const vector<universal>&args,T&...vars){
    llu index=0;
    llu data[]={setup_var(args,vars,index)...};
}

auto read(const vector<universal>&args){
    string filename;
    setup_vars(args,filename);
    return bmp_read(filename);
};
auto pwd(const vector<universal>&args){
    return system("pwd");
};
auto ls(const vector<universal>&args){
    return system("ls");
};
auto write(const vector<universal>&args){
    vector<vector<pixel>>data;
    string filename;
    setup_vars(args,data,filename);
    bmp_write(data,filename);
    return 0;
};
auto negative(const vector<universal>&args){
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
auto scale(const vector<universal>&args){
    vector<vector<pixel>>in;
    vector<vector<pixel>>out;
    llu z=0,x=0,a=0,s=0;
    setup_vars(args,in,z,x);
    if (z*x==0){
        cerr<<"size must not be zero"<<endl;
        throw exception();
    }
    a=in.size();
    s=a?in[0].size():0;
    for (llu q=0;q<z;++q){
        out.emplace_back();
        for (llu w=0;w<x;++w){
            out.back().emplace_back();
            for (llu e=0;e<4;++e){
                out.back().back()[e]=(
                    in[q*a/z                   ][w*s/x                   ][e]*((z-1-q*a%z)*(x-1-w*s%x))+
                    in[min(q*a/z+!!(q*a%z),a-1)][min(w*s/x+!!(w*s/x),s-1)][e]*((    q*a%z)*(    w*s%x))+
                    in[q*a/z                   ][min(w*s/x+!!(w*s/x),s-1)][e]*((z-1-q*a%z)*(    w*s%x))+
                    in[min(q*a/z+!!(q*a%z),a-1)][w*s/x                   ][e]*((    q*a%z)*(x-1-w*s%x))
                )/z/x;
            }
        }
    }
    return out;
};

auto size(const vector<universal>&args){
    vector<vector<pixel>>data;
    setup_vars(args,data);
    cout<<data.size()<<" "<<(data.size()?data[0].size():0)<<endl;
    return nullptr;
};

template<typename T>
auto print_value(const T&val){
    if constexpr (requires{cout<<val;}){
        cout<<val;
    }else{
        cerr<<__PRETTY_FUNCTION__<<endl;
    }
}

auto puts(const vector<universal>&args){
    for (auto&w:args){
        visit([](auto&q){print_value(q);},w);
        cout<<" ";
    }
    cout<<endl;
    return 0;
};


int main(int _argc,char**_argv){
    map<string,universal> vars;
    map<string,function<universal(vector<universal>)>> funs;
    funs["ls"]=[](auto...a){return ls(a...);};
    funs["pwd"]=[](auto...a){return pwd(a...);};
    funs["puts"]=[](auto...a){return puts(a...);};
    funs["read"]=[](auto...a){return read(a...);};
    funs["size"]=[](auto...a){return size(a...);};
    funs["write"]=[](auto...a){return write(a...);};
    funs["scale"]=[](auto...a){return scale(a...);};
    funs["negative"]=[](auto...a){return negative(a...);};
    vector<string> argv(_argv,_argv+_argc);
    int c=EOF;
    for (auto&w:argv){
        if (w=="--interactive"){
            c=0;
            w="";
        }
        if (w=="--help"){
            cerr<<"*some useful help message*"<<endl;
            exit(0);
        }
    }
    argv.resize(copy_if(argv.begin(),argv.end(),argv.begin(),[](auto&q){return q.size();})-argv.begin());
    llu argu=1;
    while (c!=EOF or argu<argv.size()){
        if (c!=EOF){
            printf(">>> ");
            stringstream ss;
            while ((c=getchar(),c!='\n' and c!=EOF)){
                ss<<char(c);
            }
            if (c==EOF){
                printf("\n");
            }
            string s;
            while (ss>>s){
                argv.push_back(s);
            }
        }
        try{
            for (;argu<argv.size();){
                if (argu+2<argv.size() and argv[argu]=="str"s){
                    vars[argv[argu+1]]=argv[argu+2];
                    argu+=3;
                }else
                if (argu+2<argv.size() and argv[argu]=="int"s){
                    vars[argv[argu+1]]=stoll(argv[argu+2]);
                    argu+=3;
                }else
                if (argu+2<argv.size() and argv[argu+1]=="["s){
                    llu e=argu+2;
                    while (e+1<argv.size() and argv[e]!="]"s){
                        ++e;
                    }
                    if (argv[e]!="]"s){
                        cerr<<"args error"<<endl;
                        throw exception();
                    }
                    vector<universal> args;
                    for (llu q=argu+2;q<e;++q){
                        args.push_back(vars.at(argv[q]));
                    }
                    funs.at(argv[argu])(args);
                    argu=e+1;
                }else
                if (argu+4<argv.size() and argv[argu+1]=="="s and argv[argu+3]=="["s){
                    llu e=argu+4;
                    while (e+1<argv.size() and argv[e]!="]"s){
                        ++e;
                    }
                    if (argv[e]!="]"s){
                        cerr<<"args error"<<endl;
                        throw exception();
                    }
                    vector<universal> args;
                    for (llu q=argu+4;q<e;++q){
                        args.push_back(vars.at(argv[q]));
                    }
                    vars[argv[argu]]=funs.at(argv[argu+2])(args);
                    argu=e+1;
                }else
                if (argu+2<argv.size() and argv[argu+1]=="="s){
                    vars[argv[argu]]=vars.at(argv[argu+2]);
                    argu=argu+3;
                }else{
                    cerr<<"args error"<<endl;
                    throw exception();
                }
            }
        }catch(exception&e){
            cerr<<e.what()<<endl;
            argu=argv.size();
        }
    }
}