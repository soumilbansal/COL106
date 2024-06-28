/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//#include "parser.cpp"
//#include "minheap.cpp"
//Write your code below this line

EPPCompiler::EPPCompiler(){

}

// HeapNode* create(int k,int lim){
//     if(k>lim){
//         return NULL;
//     }
//     HeapNode* n=new HeapNode(k);
//     n->left=create(2*k+1,lim);
//     n->right=create(2*k+2, lim);
// }
EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file= out_file;
    memory_size= mem_limit;
    //mem_loc.resize(mem_limit);
    for(int i=0;i<mem_limit;i++){
        least_mem_loc.push_heap(i);
    }

}
void convert(vector<string>& v,ExprTreeNode* n, SymbolTable* s){
    if(n->type=="VAL"){
        string s= to_string(n->num);
        v.push_back("PUSH "+s);
        return;
    }
    if(n->type=="VAR"){
        int addra=s->search(n->id);
        string s=to_string(addra);
        v.push_back("PUSH mem[" + s + "]");
        return;
    }
    convert(v,n->right,s);
    convert(v,n->left,s);
    v.push_back(n->type);
}
void EPPCompiler::compile(vector<vector<string> > code){
    int n=code.size();
    for(int i=0;i<n;i++){
        targ.parse(code[i]);
        write_to_file(generate_targ_commands());
        
    }
    //inorder(targ.symtable->get_root());
    
}
int find(vector<int>& v){
    int i=0;
    while(true){
        if(v[i]==0){
            break;
        }
        i++;
    }
    v[i]=1;
    return i;
}
vector<string> EPPCompiler::generate_targ_commands(){
    // inorder(targ.symtable->get_root());
    // cout<<endl;
    ExprTreeNode* n=targ.expr_trees.back();
    vector<string> ans;
    if(n->left->type=="DEL"){
        int addra=targ.symtable->search(n->right->id);
        targ.symtable->remove(n->right->id);
        least_mem_loc.push_heap(addra);
        ans.push_back("DEL = mem["+ to_string(addra)+"]");
        return ans;
    }
    convert(ans,n->right,targ.symtable);
    if(n->left->type=="VAR"){
        int addr=targ.symtable->search(n->left->id);
        if(addr==-2){
            addr=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(n->left->id,addr);
        }
        ans.push_back("mem["+to_string(addr)+"] = POP");
    }
    else{
        ans.push_back("RET = POP");
    }
    return ans;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream fout;
    fout.open(output_file, ios::app);
    string command;
    int n=commands.size();
    for(int i=0;i<n;i++){
        command=commands[i];
        fout<< command << endl;
    }
    fout.close();
}

EPPCompiler::~EPPCompiler(){
    
}

// int main(){
//         EPPCompiler* c=new EPPCompiler("out.txt",100);
//         vector<vector<string> > badav;
//         vector<string> vec;
//         vec.push_back("b");
//         vec.push_back(":=");
//         vec.push_back("(");
//         vec.push_back("(");
//         vec.push_back("5");
//         vec.push_back("+");
//         vec.push_back("3");
//         vec.push_back(")");
//         vec.push_back("/");
//         vec.push_back("2");
//         vec.push_back(")");
//         vector<string> vecc;
//         vecc.push_back("d");
//         vecc.push_back(":=");
//         vecc.push_back("(");
//         vecc.push_back("(");
//         vecc.push_back("12");
//         vecc.push_back("*");
//         vecc.push_back("4");
//         vecc.push_back(")");
//         vecc.push_back("-");
//         vecc.push_back("8");
//         vecc.push_back(")");
//         vector<string> ve;
//         ve.push_back("e");
//         ve.push_back(":=");
//         ve.push_back("(");
//         ve.push_back("4");
//         ve.push_back("/");
//         ve.push_back("2");
//         ve.push_back(")");
//         vector<string> v;
//         v.push_back("c");
//         v.push_back(":=");
//         v.push_back("(");
//         v.push_back("(");
//         v.push_back("d");
//         v.push_back("+");
//         v.push_back("b");
//         v.push_back(")");
//         v.push_back("/");
//         v.push_back("e");
//         v.push_back(")");
//         vector<string> vv;
//         vv.push_back("g");
//         vv.push_back(":=");
//         vv.push_back("6");
//         vector<string> vc;
//         vc.push_back("da");
//         vc.push_back(":=");
//         vc.push_back("(");
//         vc.push_back("(");
//         vc.push_back("b");
//         vc.push_back("+");
//         vc.push_back("e");
//         vc.push_back(")");
//         vc.push_back("*");
//         vc.push_back("c");
//         vc.push_back(")");
//         vector<string> vr;
//         vr.push_back("ad");
//         vr.push_back(":=");
//         vr.push_back("9");
//         vector<string> r;
//         r.push_back("a");
//         r.push_back(":=");
//         r.push_back("1");
//         vector<string> rc;
//         rc.push_back("del");
//         rc.push_back(":=");
//         rc.push_back("d");
//         vector<string> rv;
//         rv.push_back("d");
//         rv.push_back(":=");
//         rv.push_back("134");
//         vector<string> cc;
//         cc.push_back("del");
//         cc.push_back(":=");
//         cc.push_back("da");
//         badav.push_back(vec);
//         badav.push_back(vecc);
//         badav.push_back(ve);
//         badav.push_back(v);
//         badav.push_back(vv);
//         badav.push_back(vc);
//         badav.push_back(vr);
//         badav.push_back(r);
//         badav.push_back(rc);
//         badav.push_back(rv);
//         badav.push_back(cc);
//         c->compile(badav);
//         c->~EPPCompiler();
//     return 0;
// }