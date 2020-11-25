#include "Tree.h"
#include "Session.h"
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
    depth = 0;
}
Tree * Tree::createTree(const Session& session, int rootLabel) {
    //   cout<<"start create tree" << endl;
    return session.getGraph().BFS(session , rootLabel);
}
//copy constructor
Tree::Tree(const Tree& other)
{
    this->node=other.node;
    for(auto& child : other.children)
    {
        children.push_back(child->clone());
    }
    depth = other.depth;
}
//move constructor
Tree::Tree(Tree&& other){
    this->node=other.node;
    this->children=other.children;
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
   // cout<<" added child "<<child->GetNode()<<endl;
}

int Tree::GetDepth() const{
    return depth;
}

void Tree::SetDepth(int newDepth) {
    depth = newDepth;
}
Tree * Tree::clone() const {}
int Tree::traceTree(){}

std::vector<Tree*> Tree::GetChildren() const {
    return children;
}

vector<int> Tree::RetMax(Tree *tree,std::vector<int> vec) {return vector<int>();}

//CycleTree
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle){}

CycleTree::~CycleTree() {}

int CycleTree::traceTree() {
    return getSon(this->currCycle);
}

int CycleTree::getSon(int currCyc){
    if(currCyc==0)
        return this->GetNode();
    else{
        Tree* tempTree = this->getChildren().at(0);
        for(int i = 1 ; i < currCycle ; i++){
            tempTree = tempTree->GetChildren().at(0);
        }
        return tempTree->GetNode();
    }
}

Tree * CycleTree::clone() const{
    CycleTree* tree = new CycleTree(this->GetNode() ,this->currCycle);
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

std::vector<Tree*> CycleTree::getChildren() const {
    return Tree::GetChildren();
}

//MaxRank
MaxRankTree::MaxRankTree(int rootLabel):Tree((rootLabel)){}

MaxRankTree::~MaxRankTree() {}

Tree * MaxRankTree::clone() const {
    MaxRankTree* tree = new MaxRankTree(this->GetNode());
    for(auto& child : this->GetChildren())
    {
        tree->addChild(child->clone());
    }
    return tree;
}

int MaxRankTree::traceTree() {
    cout<<"trace tree from node "<<this->GetNode()<<endl;
    int x=this->GetChildren().size();
    vector<int> vec={x, this->GetNode()};
    return RetMax(this,vec)[1];

}
vector<int> MaxRankTree::RetMax(Tree *tree,vector<int> vec) {
   // cout<<"check sizes in root "<<tree->GetNode()<<endl;
    if(tree->GetChildren().empty()) {
        return vec;
    }
    else{
        int max=tree->GetChildren().size();
     //   cout<<" curr size is "<< max<<endl;
        for(Tree* tree1: tree->GetChildren())
        //   cout<<tree1->GetNode()<< " children num is " <<tree1->GetChildren().size()<<endl;
            for(Tree* tree1 : tree->GetChildren()) {
            //   cout<<" for son: "<<tree1->GetNode()<<endl;
                if(tree1->GetChildren().size() > vec[0]) {
                    vec[0] = tree1->GetChildren().size();
                    vec[1]=tree1->GetNode();
                 //     cout<<" replace max size to "<<max<< " from son: "<<tree1->GetNode()<<endl;
                }
                vector<int>temp = RetMax(tree1,vec);
            //    cout<<tree1->GetNode()<<" max size is: "<<temp<< endl;
                if(temp[0]>vec[0]) {
                    vec[0] = temp[0];
                    vec[1]=temp[1];
             //         cout<<"max replaced to "<<max<<endl;
                }
            }
         //  cout<<"return max size "<< max<<endl;
        return vec;
    }
}

void MaxRankTree::clean() const{
    for(int i = 0 ; i < GetChildren().size()  ; i++){
        delete GetChildren().at(i);
    }
}

//RootTree
RootTree::RootTree(int rootLabel):Tree(rootLabel){}

int RootTree::traceTree() {
    return this->GetNode();
}

RootTree::~RootTree() {}
Tree * RootTree::clone() const{
    RootTree* tree = new RootTree(this->GetNode());
    for(auto& child: this->GetChildren())
    {
        tree->addChild(child->clone());
    }
    return tree;
}

void RootTree::clean() const {
    for(auto& child: this->GetChildren())
    {
        delete child;
        child=nullptr;
    }
}