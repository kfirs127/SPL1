#include "../include/Tree.h"
#include <iostream>
using namespace std;
// Created by barda on 09/11/2020.

//constructor
RootTree(int rootLabel):Tree(rootLabel) {...}

//destructor
RootTree::~RootTree()
{
    this.clean();
}
RootTree::RootTree(const RootTree& other) Tree(other.node){

    for(auto& child: other)
    {
        children.push_back(child.clone());
    }
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

virtual RootTree* clone(const RootTree& other )
{
    RootTree* tree=new RootTree(other.node);
    for(auto& child: other.children)
    {
        tree.children.push_back(child.clone());
    }
    return tree;
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
const char getType()
{
    return "R";
}
