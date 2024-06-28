/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
//#include "heapnode.cpp"
//Write your code below this line

MinHeap::MinHeap(){
    size=0;
    root=NULL;
}
// void inord(HeapNode* h){
//     if(h==NULL){
//         return;
//     }
//     inord(h->left);
//     cout<<h->val<<" ";
//     inord(h->right);
// }
void swap(int& a,int& b){
    int c=a;
    a=b;
    b=c;
}
HeapNode* min(HeapNode* n){
    if(n->left==NULL){
        return n->right->val < n->val ? n->right : n;
    }
    if(n->right==NULL){
        return n->left->val < n->val ? n->left : n;
    }
    if(n->val > n->right->val){
        return n->right->val < n->left->val ? n->right : n->left;
    }
    return n->val < n->left->val? n : n->left;

}
void heapifydown(HeapNode* n){
    if(n->left==NULL && n->right==NULL){
        return;
    }
    HeapNode* nn=min(n);
    if(nn == n){
        return;
    }
    swap(nn->val,n->val);
    heapifydown(nn);

}
HeapNode* insert(HeapNode* n,int sz,int check,int num){
    if(check==0){
        return new HeapNode(num);
    }
    if(check&sz){
        n->right=insert(n->right,sz,check>>1,num);
        n->right->par=n;
        if(n->val > n->right->val){
            swap(n->val,n->right->val);
        }
    }
    else{
        n->left=insert(n->left,sz,check>>1,num);
        n->left->par=n;
        if(n->val > n->left->val){
            swap(n->val,n->left->val);
        }
    }
    return n;
}
void MinHeap::push_heap(int num){
    size++;
    if(root==NULL){
        root=new HeapNode(num);
        return;
    }
    int n=1;
    while(n<=size){
        n<<=1;
    }
    n>>=2;
    root=insert(root,size,n,num);
    // inord(root);
    // cout<<endl;
}

int MinHeap::get_min(){
    return root->val;
}
int getlast(HeapNode* n,int sz){
    int check=1;
    while(check<=sz){
        check<<=1;
    }
    check>>=2;
    while(check!=1){
        if(sz&check){
            n=n->right;
        }
        else{
            n=n->left;
        }
        check>>=1;
    }
    if(sz&1){
        int a=n->right->val;
        n->right=NULL;
        return a;
    }
    int a=n->left->val;
    n->left=NULL;
    return a;
}
void MinHeap::pop(){
    if(size==1){
        size--;
        root=NULL;
        return;
    }
    root->val=getlast(root, size);
    size--;
    heapifydown(root);
}
HeapNode* khatma(HeapNode* r){
    if(r==NULL){
        return NULL;
    }
    khatma(r->left);
    khatma(r->right);
    delete r;
    return NULL;
}
MinHeap::~MinHeap(){
    if(root){
        root=khatma(root);
    }
}

// int main(){
//     MinHeap pq;
//     pq.push_heap(0);
//     pq.push_heap(1);
//     pq.push_heap(-1);
//     pq.push_heap(2);
//     pq.push_heap(-2);
//     pq.push_heap(3);
//     pq.push_heap(-3);
//     pq.push_heap(4);
//     pq.push_heap(-4);
//     pq.push_heap(5);
//     pq.push_heap(-5);
//     pq.push_heap(6);
//     pq.push_heap(-6);
//     pq.push_heap(7);
//     pq.push_heap(-7);
//     pq.push_heap(8);
//     pq.push_heap(-8);
//     pq.push_heap(9);
//     pq.push_heap(-9);
//     pq.push_heap(10);
//     pq.push_heap(-10);
//     pq.push_heap(11);
//     pq.push_heap(-11);
//     pq.push_heap(12);
//     pq.push_heap(-12);
//     pq.push_heap(13);
//     pq.push_heap(-13);
//     pq.push_heap(14);
//     pq.push_heap(-14);
//     pq.push_heap(15);
//     pq.push_heap(-15);
//     pq.push_heap(16);
//     pq.push_heap(-16);
//     pq.push_heap(17);
//     pq.push_heap(-17);
//     pq.push_heap(18);
//     pq.push_heap(-18);
//     pq.push_heap(19);
//     pq.push_heap(-19);
//     pq.push_heap(20);
//     pq.push_heap(-20);
//     pq.push_heap(21);
//     pq.push_heap(-21);
//     pq.push_heap(22);
//     pq.push_heap(-22);
//     pq.push_heap(23);
//     pq.push_heap(-23);
//     pq.push_heap(24);
//     pq.push_heap(-24);
//     pq.push_heap(25);
//     pq.push_heap(-25);
//     pq.push_heap(26);
//     pq.push_heap(-26);
//     pq.push_heap(27);
//     pq.push_heap(-27);
//     pq.push_heap(28);
//     pq.push_heap(-28);
//     pq.push_heap(29);
//     pq.push_heap(-29);
//     pq.push_heap(30);
//     pq.push_heap(-30);
//     pq.push_heap(31);
//     pq.push_heap(-31);
//     pq.push_heap(32);
//     pq.push_heap(-32);
//     pq.push_heap(33);
//     pq.push_heap(-33);
//     pq.push_heap(34);
//     pq.push_heap(-34);
//     pq.push_heap(35);
//     pq.push_heap(-35);
//     pq.push_heap(36);
//     pq.push_heap(-36);
//     pq.push_heap(37);
//     pq.push_heap(-37);
//     pq.push_heap(38);
//     pq.push_heap(-38);
//     pq.push_heap(39);
//     pq.push_heap(-39);
//     pq.push_heap(40);
//     pq.push_heap(-40);
//     pq.push_heap(41);
//     pq.push_heap(-41);
//     pq.push_heap(42);
//     pq.push_heap(-42);
//     pq.push_heap(43);
//     pq.push_heap(-43);
//     pq.push_heap(44);
//     pq.push_heap(-44);
//     pq.push_heap(45);
//     pq.push_heap(-45);
//     pq.push_heap(46);
//     pq.push_heap(-46);
//     pq.push_heap(47);
//     pq.push_heap(-47);
//     pq.push_heap(48);
//     pq.push_heap(-48);
//     pq.push_heap(49);
//     pq.push_heap(-49);
//     pq.push_heap(50);
//     pq.push_heap(-50);
//     pq.push_heap(51);
//     pq.push_heap(-51);
//     pq.push_heap(52);
//     pq.push_heap(-52);
//     pq.push_heap(53);
//     pq.push_heap(-53);
//     pq.push_heap(54);
//     pq.push_heap(-54);
//     pq.push_heap(55);
//     pq.push_heap(-55);
//     pq.push_heap(56);
//     pq.push_heap(-56);
//     pq.push_heap(57);
//     pq.push_heap(-57);
//     pq.push_heap(58);
//     pq.push_heap(-58);
//     pq.push_heap(59);
//     pq.push_heap(-59);
//     pq.push_heap(60);
//     pq.push_heap(-60);
//     pq.push_heap(61);
//     pq.push_heap(-61);
//     pq.push_heap(62);
//     pq.push_heap(-62);
//     pq.push_heap(63);
//     pq.push_heap(-63);
//     pq.push_heap(64);
//     pq.push_heap(-64);
//     pq.push_heap(65);
//     pq.push_heap(-65);
//     pq.push_heap(66);
//     pq.push_heap(-66);
//     pq.push_heap(67);
//     pq.push_heap(-67);
//     pq.push_heap(68);
//     pq.push_heap(-68);
//     pq.push_heap(69);
//     pq.push_heap(-69);
//     pq.push_heap(70);
//     pq.push_heap(-70);
//     pq.push_heap(71);
//     pq.push_heap(-71);
//     pq.push_heap(72);
//     pq.push_heap(-72);
//     pq.push_heap(73);
//     pq.push_heap(-73);
//     pq.push_heap(74);
//     pq.push_heap(-74);
//     pq.push_heap(75);
//     pq.push_heap(-75);
//     pq.push_heap(76);
//     pq.push_heap(-76);
//     pq.push_heap(77);
//     pq.push_heap(-77);
//     pq.push_heap(78);
//     pq.push_heap(-78);
//     pq.push_heap(79);
//     pq.push_heap(-79);
//     pq.push_heap(80);
//     pq.push_heap(-80);
//     pq.push_heap(81);
//     pq.push_heap(-81);
//     pq.push_heap(82);
//     pq.push_heap(-82);
//     pq.push_heap(83);
//     pq.push_heap(-83);
//     pq.push_heap(84);
//     pq.push_heap(-84);
//     pq.push_heap(85);
//     pq.push_heap(-85);
//     pq.push_heap(86);
//     pq.push_heap(-86);
//     pq.push_heap(87);
//     pq.push_heap(-87);
//     pq.push_heap(88);
//     pq.push_heap(-88);
//     pq.push_heap(89);
//     pq.push_heap(-89);
//     pq.push_heap(90);
//     pq.push_heap(-90);
//     pq.push_heap(91);
//     pq.push_heap(-91);
//     pq.push_heap(92);
//     pq.push_heap(-92);
//     pq.push_heap(93);
//     pq.push_heap(-93);
//     pq.push_heap(94);
//     pq.push_heap(-94);
//     pq.push_heap(95);
//     pq.push_heap(-95);
//     pq.push_heap(96);
//     pq.push_heap(-96);
//     pq.push_heap(97);
//     pq.push_heap(-97);
//     pq.push_heap(98);
//     pq.push_heap(-98);
//     pq.push_heap(99);
//     pq.push_heap(-99);

//     ////

//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();
//     pq.pop();

//     ///

//     inord(pq.root);
//     // for(int i=0;i<100;i++){
//     //     cout<<"pq.pop();"<<endl;
//     // }
//     return 0;

// }