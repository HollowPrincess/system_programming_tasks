#include <sstream>
#include <ostream>
#include <string>
using namespace std;


//организовать рекурсию
template<class ... Args>
void message(::ostream& localOut, ::string regularTemplate, Args&& ... args){
    int argsCounter=0;
    int specSymCounter=0;
    Args *argPtr = args;

    int argsNumber = sizeof...(args);
    for (::string::iterator iter=regularTemplate.begin(); iter!=regularTemplate.end(); ++iter){
        if (*iter=='%'){
            specSymCounter++;
        };
    };
    
    if (specSymCounter!=argsNumber){
        localOut<<"Number of arguments and number of places are not equal";        
    }
    else{
        for (::string::iterator iter=regularTemplate.begin(); iter!=regularTemplate.end(); ++iter){
            if (*iter!='%'){
                localOut << *iter;
            }else{
                //localOut << ...args[argsCounter];
                localOut << *argPtr;
                argPtr++;

                //argsCounter++;
            };
        };
    };
}

int main(){
    return 0;
}