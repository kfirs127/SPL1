#include <iostream>
#include "include/Session.h"

using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    /* code for reading json
    #include "json.hpp";

     using json=nlohmann::json;
     using namespace std;

     ifstream i("config2.json");
     json j;
     j<<i;
     for(auto& elem:j["agents"])
     {
     }
     for(auto& elem:j["graphs"])
     {
     }
     char treeType=j["tree"];
     */
    Session sess(argv[1]);
    sess.simulate();
    return 0;
}