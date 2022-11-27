#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <variant>
#include <functional>
#include <tuple>
#include <array>
#include <type_traits>
#include "pix.hpp"
#include "alg.hpp"
#include "bmp.hpp"
using namespace std;

using llu=long long unsigned;
using lli=long long int;

auto pwd(){
    return system("pwd");
};

auto ls(){
    return system("ls");
};

auto size(bitmap data){
    cout<<data.size()<<" "<<(data.size()?data[0].size():0)<<endl;
};

auto puts(auto&...a){
    int tmp[]={(cout<<string(a)<<" ",0)...};
    cout<<endl;
    return 0;
};

struct universal_arg{
    string data;
    operator bitmap ()const{
        return bmp_read(data);
    }
    operator string()const{
        return data;
    }
    operator lli()const{
        return stoll(data);
    }
};

template<llu b=0,llu e=8>
auto call(auto&&f,llu n,auto&&...args){
    if (not(b<=n and n<e)){
        cerr<<"args count error"<<endl;
        throw exception();
    }
    if constexpr(b+1==e){
        return f((const array<universal_arg,b>*)nullptr,args...);
    }else if (n<(b+e)/2){
        return call<b,(b+e)/2>(f,n);
    }else{
        return call<(b+e)/2,e>(f,n);
    }
}

void result(universal_arg* var,auto&&val){
    if constexpr (is_same_v<decltype(val),nullptr_t>){

    }else
    if constexpr (is_same_v<decay_t<decltype(val)>,bitmap >){
        if (var){
            bmp_write(val,var[0]);
        }
    }else{
        if (var){
            var[0]=universal_arg{to_string(val)};
        }
    }
}

#define try_invoke_create(fun)                                                 \
auto try_invoke_##fun(universal_arg* var,auto&...a)                            \
    ->conditional_t<1,void,decltype(fun(a...))>{                               \
    result(var,fun(a...));                                                     \
}                                                                              \
void try_invoke_##fun(auto&...a){                                              \
    cerr<<"call " #fun " with "<<sizeof...(a)-1<<" args failed"<<endl;         \
    throw exception();                                                         \
}                                                                              \

try_invoke_create(ls)
try_invoke_create(pwd)
try_invoke_create(puts)
try_invoke_create(same)
try_invoke_create(scale)
try_invoke_create(negative)


#define universal_call(fun)                                                    \
    ([](auto var,const vector<universal_arg>&a){                               \
        return call([&](auto a_ptr){                                           \
            if constexpr (tuple_size_v<remove_reference_t<decltype(*a_ptr)>>){ \
                apply([&](auto&...a){                                          \
                    try_invoke_##fun(var,a...);                                \
                },*(decltype(a_ptr))(a.data()));                               \
            }else{                                                             \
                try_invoke_##fun(var);                                         \
            }                                                                  \
        },a.size());                                                           \
    })                                                                         \

int main(int _argc,char**_argv){
    map<string,universal_arg> vars;
    map<string,function<void(universal_arg*,const vector<universal_arg>&)>> funs;
    funs["ls"]=universal_call(ls);
    funs["pwd"]=universal_call(pwd);
    funs["puts"]=universal_call(puts);
    funs["same"]=universal_call(same);
    funs["scale"]=universal_call(scale);
    funs["negative"]=universal_call(negative);
    vector<string> argv(_argv,_argv+_argc);
    int c=EOF;
    llu mode=0;
    for (auto&w:argv){
        if (w=="--interactive"){
            c=0;
            w="";
            mode=1;
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
                if (argu+2<argv.size() and argv[argu+1]=="["s){
                    llu e=argu+2;
                    while (e+1<argv.size() and argv[e]!="]"s){
                        ++e;
                    }
                    if (argv[e]!="]"s){
                        cerr<<"args error"<<endl;
                        throw exception();
                    }
                    vector<universal_arg> args;
                    for (llu q=argu+2;q<e;++q){
                        if (vars.count(argv[q])){
                            args.push_back({vars[argv[q]]});
                        }else{
                            args.push_back({argv[q]});
                        }
                    }
                    funs.at(argv[argu])(nullptr,args);
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
                    vector<universal_arg> args;
                    for (llu q=argu+4;q<e;++q){
                        if (vars.count(argv[q])){
                            args.push_back({vars[argv[q]]});
                        }else{
                            args.push_back({argv[q]});
                        }
                    }
                    vars[argv[argu]]={argv[argu]};
                    funs.at(argv[argu+2])(&vars[argv[argu]],args);
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
            if (mode==0){
                throw;
            }
        }
    }
}