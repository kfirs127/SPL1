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
    for(int i = 0 ; i<matrix.size() ; i++){
        vector <int> toAdd;
        for(int j = 0 ; j<matrix[0].size() ; j++){
            toAdd.push_back( matrix[i][j]);
        }
        edges.push_back(toAdd);
    }
    for(int i = 0 ; i<matrix.size() ; i++){
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

    vector<int> neighbors = edges[rootlabel];
    if(neighbors.empty()) return getTree(session,rootlabel);
    Tree* tree = getTree(session,rootlabel);
    queue<Tree*> nodes = queue<Tree*>();
    bool IN[edges.size()];
    for(int elem : IN){
        IN[elem] = false;
    }
    nodes.push(tree);
    IN[rootlabel] = true;
    Tree * temp;
    while(!nodes.empty()) {
        temp=nodes.front();
        nodes.pop();
        neighbors = edgesOf(temp->GetNode());
        for (int neighbor : neighbors) {
            Tree *neighborTree;
            if (!IN[neighbor]) {
                neighborTree = getTree(session, neighbor);
                neighborTree->SetDepth(tree->GetDepth() + 1);
                nodes.push(neighborTree);
                tree->addChild(neighborTree);
                IN[neighbor] = true;
            }
        }
    }
    return tree;
}

std::vector<std::vector<int>> Graph::GetEdges() {
    return edges;
}

std::vector<int> Graph::edgesOf(int node) {
    vector<int> toReturn = vector<int>();
    for(int check : edges[node]){
           toReturn.push_back(check);
    }
    return toReturn;
}
Tree * Graph::getTree(const Session &session, int source) {
    TreeType type = session.getTreeType();
    if(type == Cycle)
        return   new CycleTree(source,session.GetCountCycle()) ;
    else if(type == MaxRank){
        return   new MaxRankTree(source);
    }
    return new RootTree(source);
}

std::vector<std::vector<int>> * Graph::getPointerEdges() {
    return &edges;
}