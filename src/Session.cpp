#include "Session.h"
#include "../include/json.hpp"
#include "Agent.h"
#include "Graph.h"
#include "iostream"
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <iterator>

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g(),treeType(),agents(),infected(),countCycle(){
    std::ifstream file(path);
    json j = json::parse(file);
    std::vector< std::vector<int>> graph = j["graph"];
    g = Graph(graph);
    std::string tree =j["tree"];
    if(tree=="R")
        treeType=Root;
    if (tree=="M")
        treeType=MaxRank;
    else
        treeType=Cycle;
    Session::infected = queue<int>();
    countCycle = 0;
    for(auto& elem:j["agents"]) {
        if (elem[0] == "C") {
            Agent *agent = new ContactTracer();
            agents.push_back(agent);
        } else {
            Agent *agent = new Virus(elem[1]);
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
    countCycle = other.countCycle;
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
        countCycle = other.countCycle;
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
    countCycle = other.countCycle;
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
    countCycle = other.countCycle;
    agents = other.agents;
    for(int i = 0 ; i < agents.size() ; i++){
        other.agents[i] = nullptr;
    }
    return *this;
}


void Session::simulate() {
    cout<<"start simulate"<<endl;
    while ((countCycle>=0) || toContinue()) {
        std::vector<Agent*> tempAgents;
        tempAgents = agents;
        for (auto elem : tempAgents) {
            elem->act(*this);
        }
        countCycle++;
    }
    cout<<" simulate stage 1"<<endl;
    json j;
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < this->g.GetEdges().size() ; ++i) {
        vector<int> neighbors = g.edgesOf(i);
        edges.push_back(neighbors);
    }
    j["graph"]=edges;
    vector <int> areInfected;
    for (Agent* a : agents) {
        if (a->getType() == 'V')
            areInfected.push_back(a->nodeAgent());
    }
    j["infected"] = areInfected;

    ofstream i("./output.json");
    i<<j;
    cout<<"end simulate"<<endl;
}

void Session::addAgent(const Agent &agent){
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph& graph) {
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

Graph Session::getGraph()const{
    return g;
}

std::vector<std::vector<int>> Session::getEdges() {
    return g.GetEdges();
}

 int Session::GetCountCycle() const {
    return countCycle;
}

bool Session::isInfected(int node) {
    for(int i = 0 ; i < infected.size() ; i++){
        int temp = infected.front();
        if(temp == node) return true;
    }
    return false;
}

bool Session::toContinue() {
    for (int i = 1; i < g.GetEdges().size(); i++) {
        if (g.isInfected(i) == 1) return true;
        for (int j = 1; j < g.GetEdges().size() ; j++) {
            vector<int> neighbor = g.edgesOf(i);
            if ((neighbor[j] == 1) & (g.isInfected(j) != 0)) return true;
        }
    }
    return false;
}