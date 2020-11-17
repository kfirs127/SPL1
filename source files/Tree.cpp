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
    this->node = rootLabel;
    this->children = vector<Tree*>();
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
    this->node=other.node;
    for(auto& child : other.children)
    {
        children.push_back(child->clone());
    }
}
//move constructor
Tree::Tree(Tree&& other){
    this->node=other.node;
    this->children=other.children;
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

Tree * Tree::clone() const{}
void Tree::clean() const {}
int Tree::traceTree(){}
