#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Graph BFS(Graph G , int sorce);
    std::vector<std::vector<int>> GetEdges();

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> Inodes;  // will represent the infected nodes.
};

#endif