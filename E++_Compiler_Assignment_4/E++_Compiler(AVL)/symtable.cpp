/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//#include "symnode.cpp"
//#include <iostream>
//Write your code below this line

SymbolTable::SymbolTable(){
    root=NULL;
    size=0;
}
// // // // // // // // // // // // // // // // // /// / // // // // // // / // // // // // // // // //


int heigh(SymNode* n){
    if(n==NULL){
        return -1;
    }
    return n->height;
}
int max(int a,int b){
    return a>b? a : b;
}
SymNode* helpinsert(string k,SymNode* n){
    if(n==NULL){
        return new SymNode(k);
    }
    if(n->key < k){
        n->right=helpinsert(k,n->right);
        n->right->par=n;
    }
    else if (n->key > k){
        n->left=helpinsert(k,n->left);
        n->left->par=n;
    }
    else{
        
        return n;
    }
    if( heigh(n->left) > heigh(n->right) + 1){
        if(heigh(n->left->left) > heigh(n->left->right)){
            return n->LeftLeftRotation();
        }
        return n->LeftRightRotation();
    }
    else if(heigh(n->left) < heigh(n->right) - 1){
        if(heigh(n->right->left) > heigh(n->right->right)){
            return n->RightLeftRotation();
        }
        return n->RightRightRotation();
    }
    else{
        n->height= max(heigh(n->left),heigh(n->right))+1;
    }
    return n;
}

void SymbolTable::insert(string k){
    size++;
    if(root==NULL){
        root=new SymNode(k);
    }
    else{
        root=helpinsert(k,root);
    }
}

// // // // // // // // // /// // // // /// // /// /// // // // / / / // // // // // // // /// // /// /

SymNode* success(SymNode* n){
    SymNode* curr=n->right;
    while(curr->left!=NULL){
        curr=curr->left;
    }
    return curr;
}
SymNode* mitado(SymNode* n,string k){
        if(n==NULL){
            return NULL;
        }
        if(n->key < k){
            n->right=mitado(n->right, k);
            if(n->right!=NULL){
                n->right->par=n;
            }
        }
        else if(n->key > k){
            n->left=mitado(n->left, k);
            if(n->left!=NULL){
                n->left->par=n;
            }
        }
        else{
            if(n->left!=NULL && n->right!=NULL){
                SymNode* temp=success(n);
                n->key=temp->key;
                n->address=temp->address;
                n->right= mitado(n->right,temp->key);
            }
            else if(n->left!=NULL){
                n->key=n->left->key;
                n->address=n->left->address;
                n->height--;
                n->left=NULL;
                return n;
            }
            else if(n->right!=NULL){
                n->key=n->right->key;
                n->address=n->right->address;
                n->height--;
                n->right=NULL;
                return n;
            }
            else{
                return NULL;
            }
            
        }
        n->height--;
        if(heigh(n->left) > heigh(n->right) + 1 ){
            if(heigh(n->left->left)> heigh(n->left->right)){
                return n->LeftLeftRotation();
            }
            else{
                return n->LeftRightRotation();
            }
        }
        else if(heigh(n->left) < heigh(n->right)-1){
            if(heigh(n->right->left)>heigh(n->right->right)){
                return n->RightLeftRotation();
            }
            else{
                return n->RightRightRotation();
            }
        }
        else{
            n->height=max(heigh(n->left),heigh(n->right))+1;
        }
        return n;
}
void SymbolTable::remove(string k){
    size--;
    root= mitado(root,k);
}

int SymbolTable::search(string k){
    SymNode* curr= root;
    while(curr->key != k){
        if(curr->key < k){
            curr=curr->right;
        }
        else{
            curr=curr->left;
        }
    }
    if(curr){
        return curr->address;
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* curr=root;
    while(curr->key != k){
        if(curr->key < k){
            curr=curr->right;
        }
        else{
            curr=curr->left;
        }
    }
    curr->address=idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}
SymNode* khatam(SymNode* n){
    if(n==NULL){
        return NULL;
    }
    khatam(n->left);
    khatam(n->right);
    delete n;
    return NULL;
}
SymbolTable::~SymbolTable(){
    if(root){
        root=khatam(root);
    }
}
// void inorder(SymNode* n){
//     if(n==NULL){
//         return;
//     }
//     inorder(n->left);
//     cout<<n->key<<" ";
//     if(n->left!=NULL){
//         cout<<n->left->key<<" ";
//     }
//     if(n->right!=NULL){
//         cout<<n->right->key<<" ";
//     }
//     cout<<n->height<<"  ";
//     inorder(n->right);
// }
// int main(){
//     SymbolTable* s=new SymbolTable();

// ///

//     s->insert("aa");
//     s->insert("a0");
//     s->insert("ac");
//     s->insert("ab");
//     s->insert("ba");
//     s->insert("bb");
//     s->insert("bc");
//     s->insert("bd");
//     s->insert("be");
//     delete s;
//     cout<<s->get_size()<<endl;
//    // inorder(s.get_root());
//     cout<<endl;
// ////


//     return 0;
// }