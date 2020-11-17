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
    virtual const char getType()=0;
    virtual Tree* clone()=0;
    virtual void clean()const =0;
    virtual Tree& operator=(const Tree& other)=0;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual const int getNode() const { return this->node;}
    virtual void setNode(int x){this->node=x;}
    virtual void setChildren(std::vector<Tree*> child){this->children=child;}
    virtual const std::vector<Tree*> getChildren() const { return this->children;}
private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    ~CycleTree();
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree& other);
    CycleTree(CycleTree&& other);
    CycleTree& operator=(const CycleTree& other);
    CycleTree& operator=( CycleTree&& other);
    int traceTree();
    CycleTree* clone();
    const  int getCurrCycle()const{return currCycle;}
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    ~MaxRankTree();
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree& other);
    MaxRankTree(MaxRankTree&& other);
    MaxRankTree& operator=(const MaxRankTree& other);
    MaxRankTree& operator=( MaxRankTree&& other);
    int traceTree();
    MaxRankTree* clone();
};

class RootTree: public Tree{
public:
    ~RootTree();
    RootTree(int rootLabel);
    RootTree(const RootTree& other);
    RootTree(RootTree&& other);
    RootTree& operator=(const RootTree& other);
    RootTree& operator=( RootTree&& other);
    int traceTree();
    RootTree* clone();
};

#endif