/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
//#include "exprtreenode.cpp"
//#include "symtable.cpp"
//Write your code below this line

Parser::Parser(){
    symtable=new SymbolTable();

}
ExprTreeNode* arithmetic(vector<string> c,int& i){
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
        int added=stoi(s);
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
//         if(head->num){
//             cout<<head->num<<" ";
//         }
//         else{
//             cout<<head->type<<" "<<head->id<<" ";
//         }
//         return;
//     }
//     cout<<"( ";
//     printexp(head->left);
//     cout<<head->type<<" ";
//     printexp(head->right);
//     cout<<")";
// }

void Parser::parse(vector<string> expression){
    ExprTreeNode* root=new ExprTreeNode();
    root->type="=";
    root->left=new ExprTreeNode();
    string s=expression[0];
    if(s=="del"){
        root->left->type="DEL";
    }
    else if(s=="ret"){
        root->left->type="RET";
    }
    else{
        root->left->type="VAR";
        root->left->id=s;
        symtable->insert(s);
    }
    int b=2;
    root->right=arithmetic(expression, b);
    expr_trees.push_back(root);
    // printexp(root);
    // cout<<endl;
}
ExprTreeNode* deleter(ExprTreeNode* n){
    if(n==NULL){
        return NULL;
    }
    deleter(n->left);
    deleter(n->right);
    delete n;
    return NULL;
}
Parser::~Parser(){

     delete symtable;
     symtable=NULL;
     for(ExprTreeNode* n : expr_trees){
        if(n){
            n=deleter(n);
        }
     }
}

// int main(){
//     Parser p;

//     vector<string> vec;
//     vec.push_back("b");
//     vec.push_back(":=");
//     vec.push_back("(");
//     vec.push_back("(");
//     vec.push_back("5");
//     vec.push_back("+");
//     vec.push_back("3");
//     vec.push_back(")");
//     vec.push_back("/");
//     vec.push_back("2");
//     vec.push_back(")");
//     p.parse(vec);
//     printexp(p.expr_trees.back());
//     cout<<endl;

//     vector<string> vecc;
//     vecc.push_back("d");
//     vecc.push_back(":=");
//     vecc.push_back("(");
//     vecc.push_back("(");
//     vecc.push_back("12");
//     vecc.push_back("*");
//     vecc.push_back("4");
//     vecc.push_back(")");
//     vecc.push_back("-");
//     vecc.push_back("8");
//     vecc.push_back(")");
//     p.parse(vecc);
//     printexp(p.expr_trees.back());
//     cout<<endl;

//     vector<string> ve;
//     ve.push_back("e");
//     ve.push_back(":=");
//     ve.push_back("(");
//     ve.push_back("4");
//     ve.push_back("/");
//     ve.push_back("2");
//     ve.push_back(")");
//     p.parse(ve);
//     printexp(p.expr_trees.back());
//     cout<<endl;

//     vector<string> v;
//     v.push_back("f");
//     v.push_back(":=");
//     v.push_back("(");
//     v.push_back("(");
//     v.push_back("d");
//     v.push_back("+");
//     v.push_back("b");
//     v.push_back(")");
//     v.push_back("/");
//     v.push_back("a");
//     v.push_back(")");
//     p.parse(v);
//     printexp(p.expr_trees.back());
//     cout<<endl;

//     inorder(p.symtable->get_root());
//     return 0;
// }