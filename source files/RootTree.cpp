#include "../include/Tree.h"
#include <iostream>
using namespace std;

//constructor
RootTree::RootTree(int rootLabel):Tree(rootLabel){}

int RootTree::traceTree() {
    return this->GetNode();
}

Tree * RootTree::clone() const{
    RootTree* tree=new RootTree(this->GetNode());
    for(auto& child: this->GetChildren())
    {
        tree->addChild(child->clone());
    }
    return tree;
}

void CycleTree::clean() const {
    for(auto& child: this->GetChildren())
    {
        delete child;
        child=nullptr;
    }
}
