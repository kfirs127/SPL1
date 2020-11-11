#include "../include/Tree.h"//
// Created by barda on 09/11/2020.

//constructor
(RootTree)->RootTree(int rootLabel):Tree(rootLabel) {...}

//destructor
RootTree::~RootTree()
{
    this.clean();
}

//copy operator
virtual RootTree& CycleTree::operator=(const RootTree& other)
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
    children.clear();
}

virtual RootTree& clone(const RootTree& other)
{
    RootTree& tree=new
}