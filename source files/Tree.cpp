#include "../include/Tree.h"
#include <iostream>
using namespace std;
// Created by barda on 08/11/2020.


//Destructor
Tree::~Tree()
{
    clean();
}
//Constructor
Tree::Tree(int rootLabel) {
    this.node=rootLabel;
}

Tree* createTree(const Session& session, int rootLabel) {

    if(session.getType()=="C")
        return (new CycleTree(rootLabel,session.getCycleNum()));
    if(session.getType()=="M")
        return (new MaxRankTree(rootLabel));
    else
        return (new RootTree((rootLabel)));


}
Tree::Tree(int rootLabel) {
        node= rootLabel;
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
            if(child.node==num)
                return child;
        }
    throw ("child not exist");
}
Tree * Tree::createTree(const Session &session, int rootLabel) {

}


