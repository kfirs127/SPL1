#include "../include/Tree.h"//
// Created by barda on 09/11/2020.

(MaxRankTree)->MaxRankTree(int rootLabel,):Tree(rootLabel) {...}

//destructor
MaxRankTree::~MaxRankTree()
{
    delete(this.node);
   Tree::clean();
}