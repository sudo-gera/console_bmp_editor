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
#include <sstream>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include "pix.hpp"
#include "alg.hpp"
#include "bmp.hpp"
#include "b64.hpp"

using namespace std;
using namespace filesystem;

using llu=long long unsigned;
using lli=long long int;

struct universal_arg{
    string data;
    universal_arg(){}
    universal_arg(string data):data(data){}
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

void result(const string&var,auto&&val){
    bmp_write(val,var);
}

#define try_invoke_create(fun)                                                 \
auto try_invoke_##fun(const string& var,auto&...a)                             \
    ->conditional_t<1,void,decltype(fun(a...))>{                               \
    result(var,fun(a...));                                                     \
}                                                                              \
void try_invoke_##fun(auto&...a){                                              \
    cerr<<"call " #fun " with "<<sizeof...(a)-1<<" args failed"<<endl;         \
    vector<string> tmp={string(a)...};                                         \
    for (auto&w:tmp){                                                          \
        cerr<<w<<" ";                                                          \
    }                                                                          \
    cerr<<endl;                                                                \
    throw exception();                                                         \
}                                                                              \

try_invoke_create(ls)
try_invoke_create(pwd)
try_invoke_create(puts)
try_invoke_create(same)
try_invoke_create(scale)
try_invoke_create(negative)


#define universal_call(fun)                                                    \
    ([](const auto&var,const vector<universal_arg>&a){                         \
        return call([&](auto a_ptr){                                           \
            if constexpr (tuple_size_v<remove_reference_t<decltype(*a_ptr)>>){ \
                remove_cvref_t<decltype(*a_ptr)> tmp;                          \
                copy(a.begin(),a.end(),tmp.begin());                           \
                apply([&](auto&...a){                                          \
                    try_invoke_##fun(var,a...);                                \
                },tmp);                                                        \
            }else{                                                             \
                try_invoke_##fun(var);                                         \
            }                                                                  \
        },a.size());                                                           \
    })                                                                         \


std::string _popen(std::string q){
    std::string s;
    auto pipe=popen(q.c_str(), "r");
    int c;
    while ((c = fgetc(pipe)) != EOF) {
        s+=static_cast<char>(c);
    }
    pclose(pipe);
    return s;
}


// vector<string> split_args(string s){
//     auto b = popen("for _w in "+s+" ; do echo $_w | base64 ; done");
//     vector<string> bs(1);
//     for (auto w:b){
//         if (w=='\n'){
//             bs.emplace_back();
//         }else{
//             bs.back()+=w;
//         }
//     }
//     if (bs.back().empty()){
//         bs.pop_back();
//     }
//     for (auto&w:bs){
//         w=b64decode(w);
//         if (w.size()){
//             w.pop_back();
//         }
//     }
//     return bs;
// }


int main(int _argc,char**_argv){
    string executable=canonical(_argv[0]);
    vector<universal_arg> vars;
    map<string,function<void(const string&,const vector<universal_arg>&)>> funs;
    funs["same"]=universal_call(same);
    funs["scale"]=universal_call(scale);
    funs["negative"]=universal_call(negative);
    vector<string> argv(_argv+1,_argv+_argc);
    unordered_map<string,llu> available_flags{
        {"--negative",0},
        {"--scale",2},
        {"--same",0},
        {"--help",0},
        {"--print-args",0},
    };
    vector<pair<string,string>> undo;
    while (not cin.eof()){
        string in;
        if (argv.size()==0){
            cout<<">>> "<<flush;
            getline(cin,in);
            stringstream ss(_popen((executable+" --print-args "+in).c_str()));
            {
                llu tmp;
                ss>>tmp;
                argv.resize(tmp);
                for (auto&w:argv){
                    ss>>tmp;
                    w.resize(tmp);
                    for (auto&e:w){
                        ss>>tmp;
                        e=tmp;
                    }
                }
            }
            argv=decltype(argv)(argv.begin()+1,argv.end());
        }
        unordered_map<string,vector<string>> flags;
        vector<string> files;
        for (llu q=0;q<argv.size();){
            if (available_flags.count(argv[q])){
                auto b=q+1;
                auto e=b+available_flags[argv[q]];
                if (e<=argv.size()){
                    flags[argv[q]]=vector<string>(argv.begin()+b,argv.begin()+e);
                }else{
                    cerr<<"flag "<<argv[q]<<" takes "<<available_flags[argv[q]]<<" parameters"<<endl;
                    throw exception();
                }
                q=e;
            }else{
                files.push_back(argv[q]);
                q+=1;
            }
        }
        if (flags.count("--print-args")){
            cout<<argv.size()<<"\n";
            for (auto&w:argv){
                cout<<w.size()<<"\n";
                for (auto&e:w){
                    cout<<(llu)(uint8_t)(e)<<" ";
                }
                cout<<"\n";
            }
            files.resize(0);
        }
        if (flags.count("--help")){
            cout<<"usage: ./bmp input.bmp --some_flags... output.bmp"<<endl;
            cout<<"if output.bmp is missing, then output.bmp is input.bmp"<<endl;
            cout<<"available flags:"<<endl;
            cout<<"    --negative"<<endl;
            cout<<"    --scale new_height new_width"<<endl;
            cout<<"    --same"<<endl;
            cout<<"if no args are given starts interactive mode"<<endl;
            cout<<"commands for interactive mode:"<<endl;
            cout<<">>> input.bmp --some_flags... output.bmp"<<endl;
            cout<<"    same as it is written in shell args"<<endl;
            cout<<"    symbols should be escaped like in shell command"<<endl;
            cout<<">>> cd dir      (changes directory)"<<endl;
            cout<<"any other commands are transferred to shell"<<endl;
            cout<<"example"<<endl;
            cout<<">>> ls -l       (calls ls command)"<<endl;
        }
        try{
            if (files.size()>0){
                if (files[0].size()>=4 and string(files[0].end()-4,files[0].end())==".bmp"){
                    string infile = files[0];
                    string outfile = files[0];
                    if (files.size()>=2){
                        outfile=files[1];
                    }
                    if (in.size()){
                        try{
                            ifstream f(outfile);
                            if (f.good()){
                                undo.push_back({
                                    outfile,
                                    string(istreambuf_iterator<char>(f),istreambuf_iterator<char>())
                                });
                            }else{
                                undo.push_back({outfile,""});
                            }
                        }catch(...){
                            undo.push_back({outfile,""});
                        }
                    }
                    bmp_write(bmp_read(infile),outfile);
                    for (auto&w:argv){
                        if (flags.count(w)){
                            vars.push_back(outfile);
                            copy(flags[w].begin(),flags[w].end(),back_inserter(vars));
                            auto fun=string(w.begin()+2,w.end());
                            funs.at(fun)(outfile,vars);
                            vars.resize(0);
                        }
                    }
                }else
                if (files[0]=="exit"){
                    break;
                }else
                if (files[0]=="undo"){
                    if (undo.empty()){
                        cerr<<"nothing to undo"<<endl;
                    }else{
                        cout<<"undo changes for "<<undo.back().first<<endl;
                        {
                            ofstream f(undo.back().first);
                            f<<undo.back().second;
                        }
                        undo.pop_back();
                    }
                }else
                if (files[0]=="cd"){
                    if (files.size()>=2){
                        current_path(files[1]);
                    }else{
                        cerr<<"usage: cd [path]";
                    }
                }else{
                    system(in.c_str());
                }
            }
        }catch(exception&e){
            cerr<<e.what()<<endl;
        }
        if (in.size()){
            argv.resize(0);
        }else{
            break;
        }
    }
    if (cin.eof()){
        cout<<endl;
    }
}
