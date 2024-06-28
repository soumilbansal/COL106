#include <iostream>
#include "stack_a.h"
#include <stdexcept>
using namespace std;

int Flour(double a,double b){
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

Stack_A::Stack_A(){
        size=0;
    }

void Stack_A::push(int data){
	if(size==1024){
	    throw runtime_error("Stack Full");
	    return;
	}
        stk[size++]=data;
}

int Stack_A::pop(){
	if(size==0){
	    throw runtime_error("Empty Stack");
	    return 0;
	}
	else{
            size--;
            return stk[size];
	}
}
int Stack_A::get_element_from_top(int idx){
	if(idx<0 || idx>size-1){
	    throw runtime_error("Index out of range");
	}
	else{
             return stk[size-1-idx];
	}
}
int Stack_A::get_element_from_bottom(int idx){
	if(idx<0 || idx>size-1){
	    throw runtime_error("Index out of range");
	}
	else{
            return stk[idx];
	}
}
void Stack_A::print_stack(bool top_or_bottom){
        if(top_or_bottom){
            for(int i=size-1;i>-1;i--){
                std::cout<<stk[i]<<std::endl;
            }
        }
	else{
            for(int i=0;i<size;i++){
                std::cout<<stk[i]<<std::endl;
            }
        }
    }

int Stack_A::add(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
            int adder=pop();
            adder+=pop();
            push(adder);
    	    return adder;
	}
}
int Stack_A::subtract(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
            int a=-pop();
            a+=pop();
            push(a);
    	    return a;
	}
}

int Stack_A::multiply(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
	else{
            int a=pop();
            a*=pop();
            push(a);
    	    return a;
	}
}
int Stack_A::divide(){
        if(size<=1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            double a=pop();
            double b=pop();
 
        	if(a==0){
        	    throw runtime_error("Divide by Zero Error");
        	}
		else{
        	    return stk[size++]=Flour(b,a);       	
		}
        }
}

int* Stack_A::get_stack(){
    return stk;
} 

int Stack_A::get_size(){
    return size;
} 
