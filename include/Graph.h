#ifndef GRAPH_H_
#define GRAPH_H_
#include "..\include\Session.h"
#include "..\include\Tree.h"
#include <vector>

class Graph{
public:
    Graph();
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    Tree* BFS(Session& session, int sorce);
    std::vector<std::vector<int>> GetEdges();
    std::vector<int> edgesOf(int node);

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> Inodes;  // will represent the infected nodes.
};

#endif