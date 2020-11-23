#include <iostream>
#include <fstream>
#include "../include/Session.h"
#include "../include/json.hpp"

using namespace std;
using json = nlohmann::json;


int main(int argc,char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    //cout<< argv[1]<<endl;
    Session sess(argv[1]);
    sess.simulate();
    return 0;
}
/*
 char c= file.get();
    while (file)
    {
        std::cout << c;
        c = file.get();
    }
 */