/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
    address=-2;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
    address=-2;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* temp=left;
    left=temp->right;
    temp->right=this;
    temp->right->par=temp;
    if(left!=NULL){
        left->par=this;
    }
    temp->right->height--;
    return temp;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* temp=right;
    right=temp->left;
    temp->left=this;
    temp->left->par=temp;
    if(right!=NULL){
        right->par=this;
    }
    temp->left->height--;
    return temp;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* temp=left->right;
    left->right=temp->left;
    temp->left=left;
    left=temp->right;
    temp->right=this;
    temp->height++;
    this->height--;
    temp->left->height--;
    if(temp->left->right!=NULL){
        temp->left->right->par=temp->left;
    }
    this->par=temp;
    if(this->left!=NULL){
        this->left->par=this;
    }
    temp->left->par=temp;
    return temp;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* temp=right->left;
    right->left=temp->right;
    temp->right=right;
    right=temp->left;
    temp->left=this;
    temp->height++;
    this->height--;
    temp->right->height--;
    if(temp->right->left!=NULL){
        temp->right->left->par=temp->right;
    }
    this->par=temp;
    if(this->right!=NULL){
        this->right->par=this;
    }
    temp->right->par=temp;
    return temp;
}

SymNode::~SymNode(){
}