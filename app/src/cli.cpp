#include "cli.h"

template<class T> void addint(char *src, std::string name, std::unordered_map<std::string, std::pair<cli::ARG_TYPE, std::any>> &res){
    bool negative = false;
    if(src[0]=='n'){
        ++src;
        negative = true;
    }
    T v = std::stoll(src);
    if(v == std::stoll(src))
        res[name].second = (T)(negative?-v:v);
    else
        WARN(src << " not valid for: " << name << " : evaluated to " << v);
}

void cli::parseArgs(int argc, char *argv[], std::unordered_map<std::string, std::pair<ARG_TYPE, std::any>> &res){
    std::string prev = "";
    bool prevRequiresValue = false;
    for(int i=1;i<argc;++i){
        std::string arg(argv[i]);
        if(argv[i][0] == '-'){
            if(prevRequiresValue){
                prevRequiresValue = false;
                WARN("No value given for: " + prev);
            }
            if(arg.size()>=2){
                if(argv[i][1] == '-'){
                    prev = arg.substr(2);
                    if(res[prev].first == ARG_TYPE::BOOL)
                        res[prev].second = true;
                    else
                        prevRequiresValue = true;
                }else{
                    for(char c : arg.substr(1)){
                        prev = c;
                        if(res[prev].first == ARG_TYPE::BOOL){
                            res[prev].second = true;
                            prevRequiresValue = false;
                        }else{
                            prevRequiresValue = true;
                        }
                    }
                }
            }
        }else{
            if(!prevRequiresValue){
                WARN("No value required for: " + prev);
            }else{
                prevRequiresValue = false;
                switch(res[prev].first){
                    case ARG_TYPE::INT8:{
                        try{
                            addint<int8_t>(argv[i], prev, res);
                        }catch(std::invalid_argument e){
                            WARN(prev << " requires signed 8 bit integer");
                        };
                    }break;
                    case ARG_TYPE::UINT16:{
                        try{
                            addint<uint16_t>(argv[i], prev, res);
                        }catch(std::invalid_argument e){
                            WARN(prev << " requires unsigned 16 bit integer");
                        };
                    }break;
                    case ARG_TYPE::STRING:{
                        res[prev].second = std::string(argv[i]);
                    }break;
                }
            }
        }
    }
    if(prevRequiresValue){
        WARN("No value given for: " + prev);
    }
}