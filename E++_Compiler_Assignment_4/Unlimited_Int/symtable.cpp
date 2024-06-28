/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//#include "entry.cpp"
SymbolTable::SymbolTable(){
    root=NULL;
    size=0;
}
void destruct(SymEntry* n){
    if(n->left!=NULL){
        destruct(n->left);
    }
    if(n->right!=NULL){
        destruct(n->right);
    }
    n->~SymEntry();
    n=NULL;
}
SymbolTable::~SymbolTable(){
    if(root!=NULL){
        destruct(root);
    }
}


// bool comp(string s1,string s2){
//     int n1=s1.length();
//     int n2=s2.length();
//     int j=0;
//     while(j<n1 && j<n2){
//         if(s1[j]!=s2[j]){
//             return (s1[j]-'0')>(s2[j]-'0')? true : false;
//         }
//         j++;
//     }
//     return n1<n2? true : false;
// }
SymEntry* inserter(SymEntry* n1, SymEntry* n2){
    if(n1==NULL){
        return n2;
    }
    if(n1->key < n2->key){
        n1->right=inserter(n1->right,n2);
    }
    else if(n1->key > n2->key){
        n1->left=inserter(n1->left, n2);
    }
    return n1;
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* added=new SymEntry(k,v);
    size++;
    root= inserter(root, added);

}

SymEntry* del(SymEntry* n,string k){
    if (n == NULL)
        return n;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (n->key > k) {
        n->left = del(n->left, k);
        return n;
    }
    else if (n->key < k) {
        n->right = del(n->right, k);
        return n;
    }

    if (n->left == nullptr) {
        SymEntry* temp = n->right;
        delete n;
        return temp;
    }
    else if (n->right == nullptr) {
        SymEntry* temp =n->left;
        delete n;
        return temp;
    }

    else {
 
        SymEntry* temp = n;

        SymEntry* curr = n->right;
        while (curr->left != NULL) {
            temp = curr;
            curr = curr->left;
        }
        if (temp != n)
            temp->left = curr->right;
        else
            temp->right = curr->right;

        n->key = curr->key;

        delete curr;
        return n;
    }
}
void SymbolTable::remove(string k){
    size--;
    del(root,k);
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* curr=root;
    while(curr!=NULL){
        if(curr->key==k){
            return curr->val;
        }
        else if(curr->key<k){
            curr=curr->right;
        }
        else{
            curr=curr->left;
        }
    }
    return NULL;
}

 int SymbolTable::get_size(){
    return size;
 }

 SymEntry* SymbolTable::get_root(){
    return root;
 }

// int main(){
//     SymbolTable sym;
//     UnlimitedInt obj1("23");
//  //   cout<<obj1.to_string()<<"  "<<obj1.get_size()<<endl;
//      UnlimitedInt obj2("35");
//  //    cout<<obj2.to_string()<<"  "<<obj2.get_size()<<endl;
//     UnlimitedInt obj3("10");
//   //  cout<<obj3.to_string()<<"  "<<obj3.get_size()<<endl;
//      UnlimitedInt obj4("7");
//   //   cout<<obj4.to_string()<<"  "<<obj4.get_size()<<endl;
//      UnlimitedRational obj5(&obj1,&obj2);
//      UnlimitedRational obj6(&obj3,&obj4);
//      sym.insert("bb",&obj5);
//      sym.insert("ac",&obj6);
//      sym.insert("qd",&obj5);
//      sym.insert("ce",&obj5);
//      sym.insert("af",&obj6);
//      sym.insert("ag",&obj5);
//      sym.insert("ab",&obj5);
//      cout<<sym.get_size()<<endl;
//      sym.insert("cd",&obj5);
//      sym.insert("ae",&obj5);
//      sym.insert("hf",&obj6);
//      sym.insert("al",&obj5);

//      sym.remove("al");
//      sym.remove("ab");
//      inorder(sym.get_root());
//      cout<<endl<<sym.search("ac")->get_frac_str()<<endl;
//      cout<<sym.get_size()<<endl;
//     return 0;
// }