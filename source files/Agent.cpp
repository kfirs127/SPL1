#include "Agent.h"
#include "Session.h"
#include "Tree.h"
#include <vector>
#include <iostream>

using namespace std;

// Agents
Agent::Agent(){}

Agent::Agent(const Agent &other){}

void Agent::act(Session &session){}

Agent * Agent::clone() const{}


// contactTracer
ContactTracer::ContactTracer(){}

void ContactTracer::act(Session &session) {}

Agent * ContactTracer::clone() const {
    return new ContactTracer(*this);
}


// Virus
Virus::Virus(int nodeInd):nodeInd(nodeInd){}

void Virus::act(Session &session){
    vector<vector<int>> edges = session.getEdges();
    int root = session.dequeueInfected();
    if(root != -1){
        Tree *t = Tree::createTree(session , root);
        int toRemove = t->traceTree();
        for(int elem : edges[toRemove]){
            elem = 0;
        }
        for(int i = 0 ; i < edges.size() ; i++){
            edges[i][toRemove] = 0;
        }
        delete t;
    }
}

Agent * Virus::clone() const {
    return new Virus(*this);
}