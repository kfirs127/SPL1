#include "../include/Tree.h"
// Created by barda on 08/11/2020.


//Destructor
Tree::~Tree(){

}
//Constructor
Tree::Tree(int rootLabel) {
    this->node=rootLabel;
}

Tree* createTree(const Session& session, int rootLabel)
{
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

}
Tree * Tree::createTree(const Session &session, int rootLabel) {

}
Tree::Tree(int rootLabel) {
   node= rootLabel;

}