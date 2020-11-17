#include "../include/Tree.h"
#include "../include/Session.h"
#include <iostream>
using namespace std;
// Created by bardam on 08/11/2020.


//Destructor
Tree::~Tree()
{
    clean();
}
//Constructor
Tree::Tree(int rootLabel): node(rootLabel) {}

Tree* createTree(const Session& session, int rootLabel) {

    if((session).getTreeType()==Cycle)
        return (new CycleTree(rootLabel,session.getCycleNum()));
    if((session).getTreeType()==MaxRank)
        return (new MaxRankTree(rootLabel));
    else
        return (new RootTree((rootLabel)));

}
//copy constructor
Tree::Tree(const Tree& other)
{
    this->node=other.node;
    for(auto& child: other)
    {
        children.push_back(child.clone());
    }
}
//move constructor
Tree::Tree(Tree&& other){
    this->node=other.node;
    this->children=other.children;
    other.node= nullptr;
    other.children= nullptr;

}
int getNode()
{
    return (this)->node;
}

int Tree::traceTree() {

}
void Tree::addChild(const Tree &child) {

    Tree* clone=child.clone();
    children.push_back(clone);
}
void Tree::addChild(Tree *child) {

    children.push_back(child);
}
const Tree& Tree::getChild(int num)
{
        for(auto& child: children)
        {
            if(child->node==num)
                return child*;
        }
    throw ("child not exist");
}
Tree * Tree::createTree(const Session &session, int rootLabel) {

}
 Tree* clone(const Tree& other )
{
    RootTree* tree=new Tree(other.node);
    for(auto& child: other.children)
    {
        tree.children.push_back(child.clone());
    }
    return tree;
}


