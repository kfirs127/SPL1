#include "../include/Tree.h"//
// Created by barda on 09/11/2020.
//
(CycleTree)->CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle){...}

//destructor

CycleTree::~CycleTree()
{

    (this)::clean();
}

virtual void clean()
{
    delete(this.node);
    delete(this.currCycle);
    for(int i=0;i<children.size();i++)
    {
        delete children.at(i);
    }
    children.clear();
}
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
    children.push(new CycleTree(other.children.at(i).clone()));
}