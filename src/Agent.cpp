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
      cout <<" start ContactTracer act " << endl;
    vector<vector<int>>* edges = session.getPointerEdges();
    int root = session.dequeueInfected();
    cout<< " contact tracer chose " <<root<< " as root"<<endl;
    cout<<" next infected on the list is "<< session.getInfected().front()<<endl;
                                         
    if(root != -1){
        Tree *t = Tree::createTree(session , root);
        cout<<"num of son of "<<t->GetNode()<<" is: " <<t->GetChildren().size()<<endl;
        int toRemove = t->traceTree();
        cout<<" remove node "<<toRemove<< " from the graph "<<endl;
        for(int i = 0 ; i < edges->size() ; i++){
            (*edges)[toRemove][i] = 0;
        }
        for(int i = 0 ; i < edges->size() ; i++) {
            (*edges)[i][toRemove] = 0;
        }
        cout<<" removed edges of node " <<toRemove <<endl;
        delete t;
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
    if(!session.Iinfected(nodeInd)){
        session.enqueueInfected(nodeInd);
        session.AddInfected(nodeInd);
    }
    vector<vector<int>> edges = session.getEdges();
  //  cout<<" num of neighbors of "<< nodeInd<< " is "<< session.getGraph().edgesOf(nodeInd).size() <<endl;
    for (int i = 0; i < edges[nodeInd].size() ; i++) {
        if(edges[nodeInd][i] == 1 && !session.hasAgent(i)) {
            cout <<" node "<<nodeInd<< " infected "<<i<<endl;
            session.updateInfected(i);
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