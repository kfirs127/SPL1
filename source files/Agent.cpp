#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"
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
    int root = session.dequeueInfected();
    if(root != -1){
        Tree *t = Tree::createTree(session , root);
        int toRemove = t->traceTree();
        for(int i = 0 ; i < edges[toRemove].size() ; i++){
            edges[toRemove][i] = 0;
        }
        for(int i = 0 ; i < edges.size() ; i++){
            edges[i][toRemove] = 0;
        }
        t->clean();
    }
}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}


// Virus
Virus::Virus(int nodeInd):nodeInd(nodeInd){}

void Virus::act(Session &session){
    vector<vector<int>> edges = session.getEdges();
    int root = session.dequeueInfected();
    if(root != -1){
        bool check = false;
        int neighbor = -1;
        for(int i = 0 ; i < edges[nodeInd].size() && !check ; i++){
            if(edges[nodeInd][i] == 1 && !session.isInfected(i)){
                neighbor = i;
                check = true;
            }
        }
        if(check){
            session.enqueueInfected(neighbor);
            session.addAgent(Virus(neighbor));
        }
    }
}

Agent * Virus::clone() const {
    return new Virus(*this);
}