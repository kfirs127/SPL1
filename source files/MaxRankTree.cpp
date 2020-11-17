#include "../include/Tree.h"
#include <iostream>
using namespace std;

//constructor
MaxRankTree::MaxRankTree(int rootLabel):Tree((rootLabel)){}

Tree * MaxRankTree::clone() const {
    MaxRankTree* tree=new MaxRankTree(this->GetNode());
    for(auto& child: this->GetChildren())
    {
        tree->addChild(child->clone());
    }
    return tree;
}

int MaxRankTree::traceTree() {
    int x = this->GetChildren().size();
    for(Tree* child : this->GetChildren())
    {
        if(child->traceTree() >x)
            x = child->traceTree();
    }
    return x;

}

void MaxRankTree::clean() const{
   for(int i = 0 ; i < GetChildren().size()  ; i++){
       delete GetChildren().at(i);
   }
}
