#include <iostream>
#include "stack_b.h"
#include <stdexcept>
using namespace std;

int Floor(double a,double b){
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

Stack_B::Stack_B(){
    capacity=1024;
    stk=new int[capacity];
    size=0;
}

    // Destructor
Stack_B::~Stack_B(){
    delete[] stk;
}

void Stack_B::push(int data){
    if(size==capacity){
        capacity*=2;
        try{
        int* temp=new int[capacity];
        for(int i=0;i<size;i++){
            *(temp+i)=*(stk+i);
        }
        delete[] stk;
        stk=temp;
        }
        catch(const bad_alloc &e){
        cout<<"Out of Memory"<<endl;
        }
    }
    stk[size++]=data;

}

int Stack_B::pop(){
    if(size==0){
        throw runtime_error("Empty Stack");
    }
    else{
    size--;
    int a=stk[size];
    if(size<= capacity/4 && capacity>=2048){
        capacity/=2;
	    try{
        int* temp=new int[capacity];
        for(int i=0;i<size;i++){
            *(temp+i)=*(stk+i);
        }
        delete[] stk;
        stk=temp;
	    }
	    catch(const bad_alloc &e){
        cout<<"Out of Memory"<<endl;
    }
    }
    return a;
    }

}

int Stack_B::get_element_from_top(int idx){

        if(idx<0 || idx>size-1){
            throw runtime_error("Index out of range");
        }
    else{
    return *(stk+size-1-idx);
    }
    
}

int Stack_B::get_element_from_bottom(int idx){
    if(idx<0 || idx>size-1){
        throw runtime_error("Index out of range");
    }
    else{
    return *(stk+idx);
    }
    
}

void Stack_B::print_stack(bool top){
    if(size==0){
        return;
    }
    if(top){
        for(int i=size-1;i>-1;i--){
            cout<<stk[i]<<endl;
        }
    }
    else{
        for(int i=0;i<size;i++){
            cout<<stk[i]<<endl;
        }
    }
}

int Stack_B::add(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
    else{
        int a=pop();
        return stk[size-1]+=a;
    }
}

int Stack_B::subtract(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
    	int a=-pop();
    	return stk[size-1]+=a;
    }
}

int Stack_B::multiply(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
    int a=pop();
    return stk[size-1]*=a;
    }

}

int Stack_B::divide(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
        double b=pop();
            if(b==0){
		pop();
                throw runtime_error("Divide by Zero Error");
            }
	else{
            double a=pop();
	    return stk[size++]=Floor(a,b);
        }
    }
}

int* Stack_B::get_stack(){
    return stk;
} // Get a pointer to the array

int Stack_B::get_size(){
    return size;
} // Get the size of the stack
