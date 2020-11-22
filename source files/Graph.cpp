#include "Graph.h"
#include "Tree.h"
#include "Session.h"
#include <vector>
#include <queue>

using namespace std;

Graph::Graph(){}

Graph::Graph(std::vector<std::vector<int>> matrix) {
    this->edges = matrix;
    for(int i = 0 ; matrix.size() ; i++){
        Inodes.push_back(false);
    }
}

void Graph::infectNode(int nodeInd){
    Inodes[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd){
    return Inodes[nodeInd];
}

Tree * Graph::BFS(Session &session, int sorce){
    vector<int> neighbors = session.getEdges()[sorce];
    if(neighbors.empty()) return Tree::createTree(session , sorce);
    Tree* tree = Tree::createTree(session , sorce);
    queue<Tree*> nodes = queue<Tree*>();
    bool IN[session.getInfected().size()];
    for(int elem : IN){
        IN[elem] = false;
    }
    nodes.push(tree);
    IN[sorce] = true;
    while(!nodes.empty()) {
        nodes.pop();
        Graph tempGraph = session.getGraph();
        neighbors = tempGraph.edgesOf(tree->GetNode());
        for (int neighbor : neighbors) {
            Tree *neighborTree;
            if (!IN[neighbor]) {
                neighborTree = Tree::createTree(session, neighbor);
                neighborTree->SetDepth(tree->GetDepth() + 1);
                nodes.push(neighborTree);
                tree->addChild(neighborTree);
                IN[neighbor] = tree;
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
       if(edges[node][check]){
           toReturn.push_back(check);
       }
    }
    return toReturn;
}