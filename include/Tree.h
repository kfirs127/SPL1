#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(Tree&& other);
    Tree(const Tree& other);
    void addChild(const Tree& child);
    void addChild(Tree* child);
    const Tree& getChild(int place);
    const char getType()=0;
    virtual Tree* clone()=0;
    virtual void clean()const =0;
    virtual Tree& operator=(const Tree& other)=0;





    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
private:
    int node;
    std::vector<Tree*> children;
}

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree& other);
    CycleTree(CycleTree&& other);
    virtual CycleTree& operator=(const CycleTree& other);
    virtual CycleTree& operator=( CycleTree&& other);
    virtual int traceTree();
private:
    int currCycle;
}

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree& other);
    MaxRankTree(MaxRankTree&& other);
    virtual MaxRankTree& operator=(const MaxRankTree& other);
    virtual MaxRankTree& operator=( MaxRankTree&& other);
    virtual int traceTree();
}

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    RootTree(const RootTree& other);
    RootTree(RootTree&& other);
    virtual RootTree& operator=(const RootTree& other);
    virtual RootTree& operator=( RootTree&& other);
    virtual int traceTree();
}

#endif