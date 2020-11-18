#include "../include/Tree.h"
#include "../include/Session.h"
#include <iostream>
using namespace std;

//Destructor
Tree::~Tree()
{
    for(int i = 0 ; i < GetChildren().size()  ; i++){
        delete GetChildren().at(i);
    }
}
//Constructor
Tree::Tree(int rootLabel) {
    node = rootLabel;
    children = vector<Tree*>();
    depth = 0;
}
Tree * Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    if(type == Cycle){
        return new CycleTree(rootLabel,0);
    }
    else if(type == MaxRank){
        return new MaxRankTree(rootLabel);
    }
    return new RootTree(rootLabel);
}
//copy constructor
Tree::Tree(const Tree& other)
{
    node=other.node;
    for(auto& child : other.children)
    {
        children.push_back(child->clone());
    }
    depth = other.depth;
}
//move constructor
Tree::Tree(Tree&& other){
    node=other.node;
    children=other.children;
    depth = other.depth;
}

int Tree::GetNode()const{
    return node;
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

void Tree::addChild(Tree *child) {
    children.push_back(child);
}

const Tree& Tree::getChild(int num)
{
    for(auto& child: children)
    {
        if(child->node==num)
            return *child;
    }
    throw ("child not exist");
}

int Tree::GetDepth() {
    return depth;
}

void Tree::SetDepth(int newDepth) {
     depth = newDepth;
}

Tree * Tree::clone() const{}
void Tree::clean() const {}
int Tree::traceTree(){}
