/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){
    par=NULL;
    right=NULL;
    left=NULL;
}

HeapNode::HeapNode(int _val){
    val= _val;
    par=NULL;
    right=NULL;
    left=NULL;
}

HeapNode::~HeapNode(){

}