#include "../include/Tree.h"
#include <iostream>

using namespace std;

//constructor
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle){}

int CycleTree::traceTree() {
    return getSon(this->currCycle);
}

/*int CycleTree::getSon(int currCyc){
    if(currCyc==0)
        return this->GetNode();
    else{
        return this->GetChildren().at(0);
    }
}*/

Tree * CycleTree::clone() const{
    CycleTree* tree=new CycleTree(this->GetNode() ,this->currCycle);
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
        child = nullptr;
    }
}
