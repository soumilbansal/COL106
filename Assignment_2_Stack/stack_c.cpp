#include <iostream>
#include <stdexcept>
#include "stack_c.h"
using namespace std;


int Flooor(double a,double b){
    double c=a/b;
    int d=a/b;
    if(c==d){
        return d;
    }
    if(c>=0){
        return d;
    }
    return d-1;
}

Stack_C::Stack_C(){
    stk=new List;
}

Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int data){
    stk->insert(data);
}

int Stack_C::pop(){
    return stk->delete_tail();
}

int Stack_C::get_element_from_top(int idx){
        int size=stk->get_size();
        if(idx<0 || idx>size-1){
            throw runtime_error("Index out of range");
        }
	else{
        Node* pos=stk->get_head();
        for(int i=0;i<=size-1-idx;i++){
            pos=pos->next;
        }
        return pos->get_value();
    }
}

int Stack_C::get_element_from_bottom(int idx){
        int size=stk->get_size();
        if(idx<0 || idx>size-1){
            throw runtime_error("Index out of range");
        }
	else{
        Node* pos=stk->get_head();
        for(int i=0;i<=idx;i++){
            pos=pos->next;
        }
        return pos->get_value();
    }
}

void Stack_C::print_stack(bool top){
    int size=stk->get_size();
    if(size==0){
        return;
    }
    if(top){
        Node* pos=((stk->get_head())->prev)->prev;
        while(!pos->is_sentinel_node()){
            cout<<pos->get_value()<<endl;
            pos=pos->prev;
        }
    }
    else{
        Node* pos=(stk->get_head())->next;
        while(!pos->is_sentinel_node()){
            cout<<pos->get_value()<<endl;
            pos=pos->next;
        }
    }
}

int Stack_C::add(){
        if(stk->get_size()<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
        int a=stk->delete_tail();
        a+=stk->delete_tail();
        stk->insert(a);
        return a;
    }
}

int Stack_C::subtract(){
        if(stk->get_size()<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
        int a=-stk->delete_tail();
        a+=stk->delete_tail();
        stk->insert(a);
        return a;
    }
}

int Stack_C::multiply(){
        if(stk->get_size()<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
        int a=stk->delete_tail();
        a*= stk->delete_tail();
        stk->insert(a);
        return a;
    }
}

int Stack_C::divide(){
        if(stk->get_size()<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
        double a=stk->delete_tail();

            if(a==0){
                stk->delete_tail();
                throw runtime_error("Divide by Zero Error");
            }
	    else{
            double b=stk->delete_tail();
            int c= Flooor(b,a);
            stk->insert(c);
            return c;
        }
    }
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}
