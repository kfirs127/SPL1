#include "../include/Tree.h"
#include <iostream>
using namespace std;
// Created by bardam on 09/11/2020.

//constructor
RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

//destructor
RootTree::~RootTree()
{
    this->clean();
}
//copy constructor
RootTree::RootTree(const RootTree& other): Tree(other.getNode()){

    for(auto& child: other.getChildren())
    {
        addChild(child->clone());
    }
}
//move constructor
RootTree::RootTree(RootTree &&other):Tree(other.getNode()){
    for(auto& child: other.getChildren())
        addChild(child);
    other.clean();

}
//copy operator
RootTree& RootTree::operator=(const RootTree &other) {

    if(this==&other){

        return *this;
    }
    this->clean();
    this->setNode(other.getNode());
    for(auto& child: other.getChildren())
        addChild(child->clone());
}
//move operator
RootTree& RootTree::operator=( RootTree&& other)
{
    if(this==&other){

        return *this;
    }
    this->clean();
    this->setNode(other.getNode());
    for(auto& child: other.getChildren())
        addChild(child->clone());
    other.clean();
}
 int RootTree::traceTree() {
    return  this->getNode();
}
 RootTree* clone(const RootTree& other)
{
    RootTree* tree= new RootTree(other.getNode());
    for(auto& child: other.getChildren())
    {
        (tree)->addChild(child->clone());
    }
    return tree;
}

 void clean()
{
    for(auto& child: )
    {
        delete child;
        child=nullptr;
    }
}
const char getType()
{
    return 'R';
}
