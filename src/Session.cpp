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
            infected.push(agent->nodeAgent());
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
        for(Agent * age :agents)
        {
            cout<< age->nodeAgent() <<" ";
        }
        cout<<endl;
        vector<Agent *> currAgents = agents;
        cout<< " num of agents is: "<<currAgents.size()<<endl;
        for(Agent * age :currAgents)
        {
            cout<< age->nodeAgent() <<" ";
        }
        cout<<endl;
        int x=currAgents.size();
        for(int i=0;i<x;i++){
                cout << currAgents[i]->nodeAgent()<<" start act " << endl;
        currAgents[i]->act(*this);

                  cout  << currAgents[i]->nodeAgent()<< " finish act " << endl;
            for(Agent * age :currAgents)
            {
                cout<< age->nodeAgent() <<" ";
            }
            cout<<endl;
        }
        countCycle++;
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
void Session::updateInfected(int infected) {

        addAgent(Virus(infected));
        g.infectNode(infected);
        cout<< " node "<< infected<< " added to agents list " <<endl;
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
    cout<< node <<" is infected: " <<isInfected <<endl ;
    return isInfected;
}

bool Session::toContinue() {
  //  bool ret=false;
    if(infections.size() == g.getSize()) return false;
    for(Agent* a : agents)
    {
        if(a->nodeAgent()!=-1) {
            vector<int> neighbors = g.edgesOf(a->nodeAgent());
            for (int nei: neighbors) {
                if (!Iinfected(nei)) {
                    return true;

                }
            }
        }
    }
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

bool Session::hasAgent(int i) {
    for(Agent* a: agents )
    {
        if(a->nodeAgent()==i)
            return true;
    }
    return false;
}
