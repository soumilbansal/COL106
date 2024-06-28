#include <iostream>
#include "list.h"
using namespace std;

List::List(){
    size=0;
    sentinel_head=new Node(true);
    sentinel_tail=new Node(true);
    sentinel_head->next=sentinel_tail;
    sentinel_tail->prev=sentinel_head;
    sentinel_head->prev=sentinel_tail;
}

List::~List(){
    Node* ptr=sentinel_head->next;
    while(!ptr->is_sentinel_node()){
	Node* temp=ptr;
	ptr=ptr->next;
	delete temp;
    }
}

void List::insert(int v){
    try{
    Node* element=new Node(v,sentinel_tail,sentinel_tail->prev);
    sentinel_tail->prev->next=element;
    sentinel_tail->prev=element;
    size++;
    }
    catch(const bad_alloc& e){
        cout<<"Out of Memory"<<endl;
    }
}

int List::delete_tail(){
        if(size==0){
            throw runtime_error("Empty Stack");
        }
	else{
        Node* temp=sentinel_tail->prev;
        sentinel_tail->prev=temp->prev;
        sentinel_tail->prev->next=sentinel_tail;
        int d=temp->get_value();
        delete temp;
        size--;
        return d;
    }
}

int List::get_size(){
    return size;
} 

Node* List::get_head(){
    return sentinel_head;
}

