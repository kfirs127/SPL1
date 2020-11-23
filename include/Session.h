#ifndef UNTITLED_SESSION_H
#define UNTITLED_SESSION_H

#endif //UNTITLED_SESSION_H
#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"
#include <vector>
#include <string>
#include <queue>

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session();
    Session(const  Session &other);
    const Session& operator=(const Session &other);
    Session(Session&& other);
    const Session& operator=(Session&& other);

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int Vnode);
    int dequeueInfected();
    TreeType getTreeType() const;

    std::vector<std::vector<int>> getEdges();
    std::queue<int> getInfected();
    Graph getGraph() const;
    int GetCountCycle()const;
    bool isInfected(int node);
    bool toContinue();
    void updateInfected();
    void addInfected(int inf);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*>agents;
    std::queue<int> infected;
    int countCycle;
    std::vector<int> toAdd;
};

#endif