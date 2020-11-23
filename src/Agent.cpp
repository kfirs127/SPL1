#include "Agent.h"
#include "Session.h"
#include "Tree.h"
#include <vector>
#include <iostream>

using namespace std;

// Agents
Agent::Agent(){}

void Agent::act(Session &session){}

Agent * Agent::clone() const{}


// contactTracer
ContactTracer::ContactTracer(){}

void ContactTracer::act(Session &session) {
    vector<vector<int>> edges = session.getEdges();
    cout<<"ContactTracer :act "<<endl;
    int root = session.dequeueInfected();
    cout<<"ContactTracer on node "<< root<<endl;
    if(root != -1){
        cout<<"start traceTree on "<< root<<endl;
        Tree *t = Tree::createTree(session , root);
        int toRemove = t->traceTree();
        cout<<"the node "<< toRemove<< " will be disconnected"<<endl;
        for(int i = 0 ; i < edges[toRemove].size() ; i++){
            cout<<"delete edge "<< toRemove<< " "<< i <<endl;
            edges[toRemove][i] = 0;
        }
        for(int i = 0 ; i < edges.size() ; i++){
            edges[i][toRemove] = 0;
        }
        delete  t;
    }
}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}

int ContactTracer::nodeAgent() const {
    return -1;
}

char ContactTracer::getType() const {
    return 'C';
}

// Virus
Virus::Virus(int nodeInd):nodeInd(nodeInd){}

void Virus::act(Session &session){
    vector<vector<int>> edges = session.getEdges();
    cout<<"start Virus :act "<<endl;
    int root = session.dequeueInfected();
    cout<<"Virus : tree on node "<< root<<endl;
    if(root != -1){
        bool check = false;
        int neighbor = -1;
        for(int i = 0 ; i < edges[nodeInd].size() && !check ; i++){
            if(edges[nodeInd][i] == 1 && !session.isInfected(i)){
                cout <<"virused " <<root<<" infected "<<i <<endl;
                neighbor = i;
                check = true;
            }
        }
        if(check){
            session.addInfected(neighbor);
        }
    }
}

Agent * Virus::clone() const {
    return new Virus(*this);
}

int Virus::nodeAgent() const {
    return nodeInd;
}

char Virus::getType() const {
    return 'V';
}
