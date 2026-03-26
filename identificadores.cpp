#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

class identificador {
    private: 
        regex iden("\\w{1}\\[a-z*A-Z*]");

    public:
        int verificaChar(char token){
            if(regex_match(iden, token) == 0);

        }
        
}