#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    ~Tree();
    Tree(Tree&& other);
    Tree(const Tree& other);
    void addChild(const Tree& child);
    void addChild(Tree* child);
    const Tree& getChild(int place);
    virtual Tree* clone()const=0;
    virtual void clean()const =0;
    Tree& operator=(const Tree& other);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int GetNode() const;
    std::vector<Tree*> GetChildren() const;
    int GetDepth() const;
    void SetDepth(int newDepth);
private:
    int node;
    std::vector<Tree*> children;
    int depth;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
    virtual void clean() const;
    int getSon(int currCyc);
private:
    int currCycle;
    int root;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
    virtual void clean() const;
private:
    int root;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
    virtual void clean() const;
};

#endif