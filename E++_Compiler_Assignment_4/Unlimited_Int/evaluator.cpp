/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

//#include "exprtreenode.cpp"

Evaluator::Evaluator(){
    symtable=new SymbolTable();
  //  expr_trees.push_back(NULL);
}
void des(ExprTreeNode* n){
    if(n->left!=NULL){
        des(n->left);
    }
    if(n->right!=NULL){
        des(n->right);
    }
    n->~ExprTreeNode();
    n=NULL;
}
Evaluator::~Evaluator(){
    symtable->~SymbolTable();
    symtable=NULL;
    for(int i=0;i<expr_trees.size();i++){
        if((expr_trees[i])!=NULL){
            des(expr_trees[i]);
        }
    }
}
ExprTreeNode* arithmetic(vector<string> c,int &i){
    string s=c[i];
    if(s=="("){
        ExprTreeNode* n=new ExprTreeNode();
        i++;
        n->left=arithmetic(c,i);
        if(c[i]==")"){
            i++;
            
        }
        if(c[i]=="+"){
            n->type="ADD";
        }
        else if(c[i]=="-"){
            n->type="SUB";
        }
        else if(c[i]=="*"){
            n->type="MUL";
        }
        else{
            n->type="DIV";
        }
        i++;
        n->right=arithmetic(c,i);
        i++;
        return n;
    }
    if(s==")"){
        i++;
        return NULL;
    }
    ExprTreeNode* n;
    if((s[0]>='0'&& s[0]<='9') || s[0]=='-'){
        UnlimitedInt* added=new UnlimitedInt(s);
        n=new ExprTreeNode("VAL",added);
    }
    else{
        n=new ExprTreeNode;
        n->type="VAR";
        n->id=s;
    }
    i++;
    return n;
}
// void printexp(ExprTreeNode* head){
//     if(head==NULL){
//         return;
//     }
//     if(head->left==NULL){
//         if(head->val){
//             cout<<head->val->get_frac_str()<<" ";
//         }
//         else{
//             cout<<head->type<<" ";
//         }
//         return;
//     }
//     cout<<"( ";
//     printexp(head->left);
//     cout<<head->type<<" ";
//     printexp(head->right);
//     cout<<")";
// }
void Evaluator::parse(vector<string> code){
    ExprTreeNode* r=new ExprTreeNode;
    r->type= "VAR";
    r->left=new ExprTreeNode;
    r->left->id=code[0];
    r->left->type="VAR";
    int b=2;
    r->right=arithmetic(code,b);
    expr_trees.push_back(r);
  //  printexp(r);
}
UnlimitedRational* evaluate(ExprTreeNode* n,SymbolTable* tab){
    if(n->type=="VAL"){
        return n->val;
    }
    else if(n->type=="VAR"){
        return tab->search(n->id);
    }
    UnlimitedRational* leftval = evaluate(n->left,tab);
    UnlimitedRational* rightval = evaluate(n->right,tab);
    string s=n->type;
    if(s=="ADD"){
        return n->evaluated_value=leftval->add(leftval,rightval);
    }
    else if(s=="SUB"){
        return n->evaluated_value=leftval->sub(leftval,rightval);
    }
    else if(s=="MUL"){
        return n->evaluated_value=leftval->mul(leftval,rightval);
    }
    return n->evaluated_value=leftval->div(leftval,rightval);
    
}
void Evaluator::eval(){
    ExprTreeNode* n=expr_trees.back();
    n->evaluated_value=evaluate(n->right,symtable);
    n->left->evaluated_value=n->evaluated_value;
//    cout<<n->left->evaluated_value->get_frac_str()<<endl;
    symtable->insert(n->left->id,n->left->evaluated_value);
}
// void print(vector<string> v){
//     int n=v.size();
//     for(int i=0;i<n;i++){
//         cout<<v[i]<<" ";
//     }
//     cout<<endl;
// }
// void getvals(vector<ExprTreeNode*> v){
//     int n=v.size();
//     for(int i=0;i<n;i++){
//         cout<<v[i]->left->id<<" "<<v[i]->left->evaluated_value->get_frac_str()<<"    ";
//     }
//     cout<<endl;
// }
// int main(){
//     Evaluator ev;
//  //   vector<string> vec;
    
// //     vector<string> vec;
// //     vec.push_back("b");
// //     vec.push_back(":=");
// //     vec.push_back("(");
// //     vec.push_back("(");
// //     vec.push_back("5");
// //     vec.push_back("+");
// //     vec.push_back("3");
// //     vec.push_back(")");
// //     vec.push_back("/");
// //     vec.push_back("2");
// //     vec.push_back(")");
// //     ev.parse(vec);
// //     cout<<endl;
// //     ev.eval();
// //      inorder(ev.symtable->get_root());
// //      cout<<endl;
// //      getvals(ev.expr_trees);
// //   //  vec.clear();
// //   //
// //   vector<string> vecc;
// //     vecc.push_back("d");
// //     vecc.push_back(":=");
// //     vecc.push_back("(");
// //     vecc.push_back("(");
// //     vecc.push_back("12");
// //     vecc.push_back("*");
// //     vecc.push_back("4");
// //     vecc.push_back(")");
// //     vecc.push_back("-");
// //     vecc.push_back("8");
// //     vecc.push_back(")");
// //     ev.parse(vecc);
// //     cout<<endl;
// //      ev.eval();
// //      inorder(ev.symtable->get_root());
// //      cout<<endl;
// //      getvals(ev.expr_trees);
// //      //
// //      //
// //      vector<string> ve;
// //     ve.push_back("a");
// //     ve.push_back(":=");
// //     ve.push_back("(");
// //     ve.push_back("4");
// //     ve.push_back("/");
// //     ve.push_back("2");
// //     ve.push_back(")");
// //     ev.parse(ve);
// //     cout<<endl;
// //     ev.eval();
// //     inorder(ev.symtable->get_root());
// //     cout<<endl;
// //     getvals(ev.expr_trees);
// //     //
// //     //
// //     vector<string> v;
// //     v.push_back("c");
// //     v.push_back(":=");
// //     v.push_back("(");
// //     v.push_back("(");
// //     v.push_back("d");
// //     v.push_back("+");
// //     v.push_back("b");
// //     v.push_back(")");
// //     v.push_back("/");
// //     v.push_back("a");
// //     v.push_back(")");
// //     ev.parse(v);
// //     cout<<endl;
// //     ev.eval();
// //     inorder(ev.symtable->get_root());
// //     cout<<endl;
// //     getvals(ev.expr_trees);

//     vector<string> vec;
//     vec.push_back("pow1");
//     vec.push_back(":=");
//     // vec.push_back("(");
//     // vec.push_back("(");
//     vec.push_back("13");
//     // vec.push_back("+");
//     // vec.push_back("3");
//     // vec.push_back(")");
//     // vec.push_back("/");
//     // vec.push_back("2");
//     // vec.push_back(")");
//     ev.parse(vec);
//     cout<<endl;
//     ev.eval();
//      inorder(ev.symtable->get_root());
//      cout<<endl;
//      getvals(ev.expr_trees);
//   //  vec.clear();
//   //
//   vector<string> vecc;
//     vecc.push_back("pow2");
//     vecc.push_back(":=");
//     vecc.push_back("(");
//     vecc.push_back("(");
//     vecc.push_back("2");
//     vecc.push_back("*");
//     vecc.push_back("42");
//     vecc.push_back(")");
//     vecc.push_back("/");
//     vecc.push_back("(");
//     vecc.push_back("pow1");
//     vecc.push_back("*");
//     vecc.push_back("pow1");
//     vecc.push_back(")");
//     vecc.push_back(")");
//     ev.parse(vecc);
//     cout<<endl;
//      ev.eval();
//      inorder(ev.symtable->get_root());
//      cout<<endl;
//      getvals(ev.expr_trees);
//      //
//      //
//      vector<string> ve;
//     ve.push_back("pow3");
//     ve.push_back(":=");
//     ve.push_back("(");
//     ve.push_back("(");
//     ve.push_back("3");
//     ve.push_back("*");
//     ve.push_back("42");
//     ve.push_back(")");
//     ve.push_back("/");
//     ve.push_back("(");
//     ve.push_back("pow2");
//     ve.push_back("*");
//     ve.push_back("pow2");
//     ve.push_back(")");
//     ve.push_back(")");
//     ev.parse(ve);
//     cout<<endl;
//     ev.eval();
//     inorder(ev.symtable->get_root());
//     cout<<endl;
//     getvals(ev.expr_trees);
//     //
//     //
//     vector<string> v;
//     v.push_back("pow4");
//     v.push_back(":=");
//     v.push_back("(");
//     v.push_back("(");
//     v.push_back("4");
//     v.push_back("*");
//     v.push_back("42");
//     v.push_back(")");
//     v.push_back("/");
//     v.push_back("(");
//     v.push_back("pow3");
//     v.push_back("*");
//     v.push_back("pow3");
//     v.push_back(")");
//     v.push_back(")");
//     ev.parse(v);
//     cout<<endl;
//     ev.eval();
//     inorder(ev.symtable->get_root());
//     cout<<endl;
//     getvals(ev.expr_trees);
//     return 0;


    // pow1:=13
    // pow2:=((2*42)/(pow1*pow1))
    // pow3:=((3*42)/(pow2*pow2))
    // pow4:=((4*42)/(pow3*pow3))
    // pow5:=((5*42)/(pow4*pow4))
//}