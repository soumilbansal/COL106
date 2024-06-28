// Do NOT add any other includes
#include "search.h"
//#include "Node.cpp"
SearchEngine::SearchEngine(){
    //
    // products.resize(20);
    // products[0]=1;
    // for(int i=1;i<20;i++){
    //     products[i]=(products[i-1]+(products[i-1]<<4))%(16384);
    // } 
    //
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    for(int i=0;i<sentence.length();i++){
        if(sentence[i]>64 && sentence[i]<91){
            sentence[i]+=32;
        }
    }
    vec.push_back(sentence);
    vector<int> v;
    v.push_back(book_code);
    v.push_back(page);
    v.push_back(paragraph);
    v.push_back(sentence_no);
    info.push_back(v); 
  //  cout<<sentence<<endl;
    return;
}
int SearchEngine::hashfunct(string& s){
    int c=0;
    for(int i=0;i<s.length();i++){
        c= c+((int)(s[i]-31))*(products[i]);
        c=c%(16384);
    }
    return c;
}
Node* SearchEngine::search(string pattern, int& n_matches){
    n_matches=0;
    int arr[96];
    int m=pattern.length();
    for(int t=0;t<96;t++){
        arr[t]=-1;
    }
    for(int i=0;i<pattern.length();i++){
        if(pattern[i]>64 && pattern[i]<91){
            pattern[i]+=32;
        }
        arr[(int)(pattern[i]-32)]=i;
    }
        Node* tem=new Node();
        Node* cur=tem;
        for(int i=0;i<vec.size();i++){
            string big=vec[i];
            int n=big.length();
            int j=0;
            while(j<=n-m){
                int s=m-1;
                while(s>-1 && pattern[s]==big[s+j]){
                    s--;
                }
                if(s<0){
                    tem->offset=j;
                    tem->book_code=info[i][0];
                    tem->page=info[i][1];
                    tem->paragraph=info[i][2];
                    tem->sentence_no=info[i][3];
                    tem->right=new Node();
                    tem->right->left=tem;
                    tem=tem->right;
                    n_matches++;
                    j+=m-arr[(int)(big[j+m]-32)];
                }
                else{
                    j+=max(1,s-arr[(int)(big[s+j]-32)]);
                }
            }
        }
        tem=tem->left;
        delete tem->right;
        tem->right=NULL;
        return cur;
    
    // else{
    // int check=hashfunct(pattern);
    // int m=pattern.length();
    // if(m>products.size()){
    //     while(products.size()!=m){
    //         int last=products.back();
    //         products.push_back((last+(last<<4))%(16384));
    //     }
    // }
    // Node* temp=new Node();
    // Node* start=temp;
    // for(int i=0;i<vec.size();i++){
    //     string curr=vec[i];
    //     int window=0;
    //     if(curr.length()< m){
    //         continue;
    //     }
    //     for(int j=0;j<m;j++){
    //         window=window+((int)(curr[j]-31))*products[j];
    //         window=window%16384;
    //     }

    //     if(check==window){
    //         int k;
    //         for(k=0;k<m;k++){
    //             if(pattern[k]!=curr[k]){
    //                 break;
    //             }
    //         }
    //         if(k==m){
    //             temp->right=new Node(info[i][0],info[i][1],info[i][2],info[i][3],0);
    //             temp->right->left=temp;
    //             temp=temp->right;
    //             n_matches++;
    //         }
    //     }
    //     for(int j=m;j<curr.length();j++){
    //         int b=((int)(curr[j]-31))*products[m-1];
    //         int a=((window-((int)(curr[j-m]-31))+16384)%(16384))/17;
    //         window= (a+b)%(16384);
    //       //  cout<<window<<" ";
    //         if(check==window){
    //             if(m>2){
    //                 if((pattern[0]!=curr[j-(m-1)])||(pattern[m-1]!=curr[j])){
    //                     continue;
    //                 }
    //             }
    //             temp->right=new Node(info[i][0],info[i][1],info[i][2],info[i][3],j-(m-1));
    //             temp->right->left=temp;
    //             temp=temp->right;
    //             n_matches++;
    //         }
    //     }
    //    // cout<<endl;
    // }
    // if(start->right){
    // start=start->right;
    // delete start->left;
    // return start;
    // }
    // delete start;
    // return NULL;
    // }
}
void print(Node* c){
    if(c){
        cout<<c->offset<<" ";
        print(c->right);
    }
    else{
        cout<<endl;
    }
}
void printv(vector<int> v){
    for(int i=0;i<4;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

// int main(){
//     SearchEngine se;
//     string sent1="me inpfmrme";
//     string sent2=" me is your dad meehehe pome' in";
//     se.insert_sentence(1,1,1,1,sent1);
//     se.insert_sentence(2,2,2,2,sent2);
//     int match=0;
//     string f="me";
//   //  cout<<"to be found is "<<se.hashfunct(f)<<endl;
//     print(se.search(f,match));
//     cout<<match<<endl;
//     return 0;
// }