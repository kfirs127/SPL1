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
    cout << "start ContactTracer :act " << endl;
    vector<vector<int>>* edges = session.getPointerEdges();
    int root = session.dequeueInfected();
    if(root != -1){
        Tree *t = Tree::createTree(session , root);
        int toRemove = t->traceTree();
        for(auto & elem : (*edges)[toRemove]){
            elem = 0;
        }
        for(int i = 0 ; i < edges->size() ; i++){
            (*edges)[i][toRemove] = 0;
        }
        delete t;
    }
    cout << "end ContactTracer :act " << endl;
    for(int i=0;i<edges->size();i++){
        for(int j=0;j<edges->size();j++){
            cout<<session.getEdges()[i][j];
        }
        cout<<endl;
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

void Virus::act(Session &session) {
    vector<vector<int>> edges = session.getEdges();
    cout << "start Virus :act " << endl;
    for (int i = 0; i < edges[nodeInd].size() ; i++) {
        if(edges[nodeInd][i] == 1 && !session.isInfected(i)) {
            session.addInfected(i);
            cout << "finish Virus :act " << endl;
            break;
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
