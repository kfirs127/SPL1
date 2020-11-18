#include "../include/Tree.h"
#include "../include/Session.h"
#include <iostream>
using namespace std;

//Destructor
Tree::~Tree()
{
    clean();
}
//Constructor
Tree::Tree(int rootLabel) {
    this->node = rootLabel;
    this->children = vector<Tree*>();
}
Tree * Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    if(type == Cycle){
        return new CycleTree(rootLabel,1);
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
//copy operator
Tree& Tree::operator=(const Tree &other) {
        if(this==&other){

            return *this;
        }
        this->clean();
        this->node=other.GetNode();
        for(auto& child: other.GetChildren())
            addChild(child->clone());
}
Tree& Tree::operator=(Tree&& other)
{
    if(this==&other){

        return *this;
    }
    this->clean();
    this->node=other.GetNode();
    for(auto& child:other.GetChildren())
        addChild(child);
    for(auto & child: other.children){
        child= nullptr;
    }
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
void Tree::clean() const {

    for(auto & child: this->children){
        delete child;

    }
}
Tree * Tree::clone() const {}
int Tree::traceTree(){}