#include "../include/Tree.h"//
// Created by barda on 09/11/2020.

(MaxRankTree)->MaxRankTree(int rootLabel,):Tree(rootLabel) {...}

//destructor
MaxRankTree::~MaxRankTree()
{
    this.clean();
}

//copy operator
virtual MaxRankTree& CycleTree::operator=(const MaxRankTree& other)
{
    if(this==&other){

        return *this;
    }
    this.clean();
    node=other.node;
    for(int i=0;i<other.children.size();i++) {
        delete children.at(i);
    }
    children.push_back(other.children.at(i).clone());
}

virtual CycleTree* clone(const CycleTree& other )
{
    CycleTree* tree=new CycleTree(other.node);
    for(auto& child: other.children)
    {
        tree.children.push_back(child.clone());
    }
    return tree*;
}

virtual void clean()
{
    delete(this.node);
    for(auto& child: children)
    {
        delete child;
        child=nullptr;
    }
    children.clean();
}