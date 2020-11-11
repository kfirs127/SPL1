#include "../include/Tree.h"//
// Created by barda on 09/11/2020.

//constructor
(RootTree)->RootTree(int rootLabel):Tree(rootLabel) {...}

//destructor
RootTree::~RootTree()
{
    delete(this.node);
    RootTree::clean();
}

