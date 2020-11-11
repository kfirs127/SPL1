#include "../include/Tree.h"//
// Created by barda on 09/11/2020.
//
(CycleTree)->CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle){...}

//destructor

CycleTree::~CycleTree()
{
    this.clean();
}
//copy operator
virtual CycleTree& CycleTree::operator=(const CycleTree& other)
{
    if(this==&other){

        return *this;
    }
    this.clean();
    node=other.node;
    currCycle=other.currCycle;
    for(int i=0;i<other.children.size();i++) {
        delete children.at(i);
    }
    children.push_back(other.children.at(i).clone());
}
virtual CycleTree* clone(const CycleTree& other )
{
    CycleTree* tree=new CycleTree(other.node,other.currCycle);
    for(auto& child: other.children)
    {
        tree.children.push_back(child.clone());
    }
    return tree*;
}
virtual void clean()
{
    delete(this.node);
    delete(this.currCycle);
    for(auto& child: children)
    {
        delete child;
        child=nullptr;
    }
    children.clean();
}