#include "Graph.h"
#include "Tree.h"
#include "Session.h"
#include <vector>
#include <queue>
#include "iostream"
#include <fstream>

using namespace std;

Graph::Graph(){}
Graph::Graph(std::vector<std::vector<int>> matrix) {
    for(int i = 0 ; i < matrix.size() ; i++){
        vector <int> toAdd;
        for(int j = 0 ; j < matrix[i].size() ; j++){
            toAdd.push_back(matrix[i][j]);
        }
        edges.push_back(toAdd);
        Inodes.push_back(false);
    }
}

void Graph::infectNode(int nodeInd){
    Inodes[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd){
    return Inodes[nodeInd];
}

Tree * Graph::BFS(const Session &session, int rootlabel){
   // cout<<"start BFS" << endl;
    vector<int> neighbors = edgesOf(rootlabel);
    if(neighbors.empty()) return getTree(session,rootlabel);
    Tree* tree = getTree(session,rootlabel);
    queue<Tree*> nodes = queue<Tree*>();
    vector<bool> IN ;
    for(int j = 0 ; j < edges.size() ; j++){
        IN.push_back( false);
    }
    nodes.push(tree);
    IN[tree->GetNode()]=true;
    Tree * temp;
    while(!nodes.empty()) {
        temp=nodes.front();
        nodes.pop();
     //   cout<< "tree node: " << temp->GetNode() << endl;
        neighbors = edgesOf(temp->GetNode());
        for (int neighbor : neighbors) {
            Tree *neighborTree;
          //  cout<<IN[neighbor] <<" for: "<<neighbor<<endl;
            if (!IN[neighbor]) {
             //   cout<< neighbor<<" "<<endl;
                neighborTree = getTree(session, neighbor);
              //  cout<<neighborTree->GetNode() <<" size beginnig "<<neighborTree->GetChildren().size()<<endl;
                neighborTree->SetDepth(tree->GetDepth() + 1);
                nodes.push(neighborTree);
                IN[neighborTree->GetNode()]=true;
                temp->addChild(neighborTree);
             //   cout<< temp->GetNode() <<" new size "<<temp->GetChildren().size()<<endl;
            }
        }
     //   cout<<endl;
    }
    return tree;
}

std::vector<std::vector<int>> Graph::GetEdges() {
    return edges;
}

std::vector<int> Graph::edgesOf(int node) {
    vector<int> toReturn;
    for(int i = 0 ; i < edges.size() ; i++){
        if(edges[node][i] == 1&&edges[i][node] == 1) {
            toReturn.push_back(i);
        }
    }
    return toReturn;
}
Tree * Graph::getTree(const Session &session, int source) {
    TreeType type = session.getTreeType();
    if(type == Cycle)
        return new CycleTree(source,session.GetCountCycle()) ;
    else if(type == MaxRank){
        return new MaxRankTree(source);
    }
    return new RootTree(source);
}

std::vector<std::vector<int>> * Graph::getPointerEdges() {
    return &edges;
}

int Graph::getSize() {
    return edges.size();
}

void Graph::SetInodes(int node) {
    Inodes[node] = false;
}