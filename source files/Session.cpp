#include "../include/Session.h"
#include "../include/Graph.h"
#include "../include/Tree.h"
#include "../include/json.hpp"
#include "../include/Agent.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using json=nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g(),treeType(),agents(),infected(){
    ifstream file(path);
    json j;
    file >> j;
    vector<pair<string , int>> JA = j["agents"];
    g = Graph(j["graphs"]);
    treeType = j["tree"];
    Session::infected = queue<int>();
    for(auto& elem:j["agents"])
     {
        if(elem[0] == "C"){
            Agent* agent = new ContactTracer();
            agents.push_back(agent);
        }
        else{
            Agent* agent = new Virus(elem[1]);
            agents.push_back(agent);
        }
     }
}

Session::~Session() {  //destructor.
    for(int i = 0 ; i < agents.size() ; i++){
        if(agents[i]) delete agents[i];
    }
    agents.clear();
}

Session::Session(const Session &other):g(),treeType(),agents(),infected(){ // copy constructor.
    g = other.g;
    infected = other.infected;
    treeType = other.treeType;
    agents = vector<Agent *>();
    for (int i = 0; i < other.agents.size(); i++) {
        agents.push_back(other.agents[i]->clone());
    }
}

const Session& Session::operator=(const Session &other){  //assignment operator.
    if(this != &other) {
        g = other.g;
        infected = other.infected;
        treeType = other.treeType;
        agents = vector<Agent *>();
        for (int i = 0; i < other.agents.size(); i++) {
            agents[i] = other.agents[i];
        }
    }
    return *this;
}


Session::Session(Session &&other):g(),treeType(),agents(),infected(){  //move constructor.
    g = other.g;
    infected = other.infected;
    treeType = other.treeType;
    agents = other.agents;
    for(int i = 0 ; i < agents.size() ; i++){
        other.agents[i] = nullptr;
    }
}

const Session & Session::operator=(Session &&other){ // move assignment operator.
    for(int i = 0 ; i < agents.size() ; i++){
        if(agents[i]) delete agents[i];
    }
    g = other.g;
    infected = other.infected;
    treeType = other.treeType;
    agents = other.agents;
    for(int i = 0 ; i < agents.size() ; i++){
        other.agents[i] = nullptr;
    }
    return *this;
}


void Session::simulate() {
    Session session = *new Session("");
    session.setGraph(g);
    for(auto elem : agents){
        elem->act(session);
    }
}

void Session::addAgent(const Agent &agent){
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int Vnode) {
    infected.push(Vnode);
}

int Session::dequeueInfected() {
    if(infected.empty()) return -1;
    int temp = infected.front();
    infected.pop();
    return temp;
}

TreeType Session::getTreeType() const {
    return treeType;
}



std::queue<int> Session::getInfected() {
    return infected;
}

Graph Session::getGragh() {
    return g;
}