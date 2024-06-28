/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
//#include "symtable.cpp"
ExprTreeNode::ExprTreeNode(){
    val=NULL;
    evaluated_value=NULL;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type=t;
    val=NULL;
    evaluated_value=NULL;
    if(t=="VAL"){
        UnlimitedInt* v2=new UnlimitedInt("1");
        UnlimitedRational* v3=new UnlimitedRational(v,v2);
        val=v3;
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type=t;
    evaluated_value=v;
    val=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    if(val!=NULL){
        val->~UnlimitedRational();
        val=NULL;
    }
    if(evaluated_value!=NULL){
        evaluated_value->~UnlimitedRational();
        evaluated_value=NULL;
    }
}