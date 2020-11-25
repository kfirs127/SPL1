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
Session::Session(const std::string &path):g(),treeType(),agents(),infected(),countCycle(1){
    std::ifstream file(path);
    json j = json::parse(file);
    cout<<j<<endl;
    std::vector< std::vector<int>> graph = j["graph"];
    g = Graph(graph);
    std::string tree =j["tree"];
    if(tree=="R")
        treeType = Root;
    else if (tree == "M")
        treeType = MaxRank;
    else if(tree=="C")
        treeType = Cycle;
    Session::infected = queue<int>();
    for(auto& elem:j["agents"]) {
        if (elem[0] == "C") {
            Agent *agent = new ContactTracer();
            agents.push_back(agent);
        }
        else {
            Agent *agent = new Virus(elem[1]);
            agents.push_back(agent);
            AddInfected(agent->nodeAgent());
            if(agent->nodeAgent() != 1) infected.push(agent->nodeAgent());
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
    while (toContinue() || countCycle == 1) {
            cout << "start simulate " << countCycle << endl;
        vector<Agent *> currAgents = agents;
        for (auto agent : currAgents){
                cout << "start act " << agent->nodeAgent()<< endl;
            agent->act(*this);

                  cout << "finish act " << endl;
        }
        countCycle++;
        updateInfected();
    }
    json j;
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < g.getSize(); ++i) {
        vector<int> neighbors = g.GetEdges()[i];
        edges.push_back(neighbors);
    }
    j["graph"] = edges;
    vector<int> areInfected;
    for (Agent *agent : agents) {
        if (agent->getType() == 'V') areInfected.push_back(agent->nodeAgent());
    }
    j["infected"] = areInfected;
    ofstream i("../output.json");
    i << j;
    cout << j << endl;
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
void Session::addInfected(int inf) {
    toAdd.push(inf);
    infected.push(inf);
    g.SetInodes(inf);
}
int Session::dequeueInfected() {
    if(infected.empty()) return -1;
    int temp = infected.front();
    g.SetInodes(temp);
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
void Session::updateInfected() {
    for(int i=0;i<toAdd.size();i++)
    {
        addAgent(Virus(toAdd.front()));
        enqueueInfected(toAdd.front());
        g.infectNode(toAdd.front());
        toAdd.pop();
    }
}
std::vector<std::vector<int>> Session::getEdges() {
    return g.GetEdges();
}

int Session::GetCountCycle() const {
    return countCycle;
}

bool Session::isInfected(int node) {
    bool isInfected = false;
    for(int i = 0 ; i < infected.size() ; i++){
        int temp = infected.front();
        infected.pop();
        if(temp == node) isInfected = true;
        infected.push(temp);
    }
    return isInfected;
}

bool Session::toContinue() {
    if(infected.empty() || infections.size() == g.getSize()) return false;
  for (int i = 0; i < g.getSize() ; i++) {
        //    cout<<"enter toContinue loop node "<<i <<endl;
        if(Iinfected(i))
        {
            for(int a: getGraph().edgesOf(i)) {
                if (!Iinfected(a)) {
                    return true;
                }
            }
        }
        else{
            //     cout<<i<<" is not infected"<<endl;
            //     cout<<" start check "<<i<<" neighbors "<<endl;
            for(int a: getGraph().edgesOf(i)) {
            if (isInfected(a))
                {
                    //           cout<<j<<" is not infected"<<endl;
                    return true;
                }
            }
        }
    }
     //cout<< "if continue: " <<ret<<endl;
    return false;


}

std::vector<std::vector<int>> * Session::getPointerEdges() {
    return g.getPointerEdges();
}
bool Session::Iinfected(int node) {

    for(int a: GetInfected() )
        if(a==node)
            return true;
    return false;
}
std::vector<int> Session::GetInfected() { return this->infections;}
void Session::AddInfected(int node) { this->infections.push_back(node);
cout<< " infected list: "<<endl;
for(int a: infections)
    cout<< a;
cout<<endl;
}