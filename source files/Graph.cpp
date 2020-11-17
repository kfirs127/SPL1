#include "Graph.h"
#include <vector>

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

Graph BFS(Graph G , int sorce){}

std::vector<std::vector<int>> Graph::GetEdges() {
    return edges;
}
