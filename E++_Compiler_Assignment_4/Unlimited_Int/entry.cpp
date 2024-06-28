/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
//#include "ulimitedrational.cpp"
SymEntry::SymEntry(){
    val=NULL;
}
// void inorder(SymEntry* n){
//     if(n==NULL){
//         return;
//     }
//     inorder(n->left);
//     std::cout<<n->key<<" ";
//     inorder(n->right);
// }
SymEntry::SymEntry(string k, UnlimitedRational* v){
    key=k;
    val=v;
    left=NULL;
    right=NULL;
}
SymEntry::~SymEntry(){
    if(val!=NULL){
        val->~UnlimitedRational();
        val=NULL;
    }
}
