#include <iostream>
#include "node.h"
using namespace std;

Node::Node(bool sentinel){
    is_sentinel=true;
    prev=NULL;
    next=NULL;
}   

Node::Node(int v, Node* nxt=NULL, Node* prv=NULL){
    value=v;
    is_sentinel=false;
    next=nxt;
    prev=prv;
}

bool Node::is_sentinel_node(){
    return is_sentinel;
}


int Node::get_value(){
    return value;
}
