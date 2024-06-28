// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    size=262144;
    elements=new Node*[size];
    count=0;
    products.resize(20,0);
    products[0]=1;
    for(int i=1;i<20;i++){
        products[i]=((products[i-1]<<5)-products[i-1])&(size-1);
    }
    checkk=(size>>1) + (size>>2);
 //   products.push_back(29);
}

Dict::~Dict(){
    // Implement your function here    
}
int Dict::hashfunc(string s){
    int hashval=0;
    for(int i=0;i<s.length();i++){
        hashval+=((int)(s[i]-32)*products[i]);
        hashval=hashval&(size-1);
    }
    return hashval;
}
Node* Dict::insert(string s,int a,int b,int c,int d, Node* curr){
    if(!curr){
        count++;
        return new Node(a,b,c,d,s);
    }
    else if(curr->val==s){
        curr->wcount++;
        return curr;
    }
    else if(curr->val<s){
        curr->right=insert(s,a,b,c,d,curr->right);
    }
    else{
        curr->left=insert(s,a,b,c,d,curr->left);
    }
    return curr;
}
Node* Dict::ins(Node** v,Node* curr,Node* c){
    if(!curr){
        return new Node(c);  
    }
    else if(curr->val<c->val){
        curr->right=ins(v,curr->right,c);
    }
    else{
        curr->left=ins(v,curr->left,c);
    }
    return curr;
}
void Dict::helper(Node** v,Node* curr,int& i){
    if(!curr){
        return;
    }
    helper(v,curr->left,i);
    helper(v,curr->right,i);
    int val=hashfunc(curr->val);
    v[val]=ins(v,v[val],curr);
    i++;
  //  cout<<i<<" ";
 //   delete curr;
}
void Dict::resize(){
    size=size<<1;
    checkk=checkk<<1;
    for(int i=1;i<products.size();i++){
        products[i]=((products[i-1]<<5) - products[i-1])&(size-1);
    }
    Node** vec=new Node*[size];
    int i=0;
    int ind=0;
    while(i!=count){
        if(elements[ind]){
            
            helper(vec,elements[ind],i);
        }
        ind++;
    }
  //  cout<<"coming"<<endl;
    delete elements;
    elements=vec;
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    int n = sentence.length();
    int i=0;
    string word="";
    while(sentence[i]==' '){
        i++;
    }
    int hashval=0;
    char curr;
    while(i<n){
        curr=sentence[i];
        i++;
        if(curr>64 && curr<91){
            curr+=32;
            word+=(curr);
        }
        else if((curr>93)||(curr>46 && curr<58)||(curr>59 && curr<63)||(curr==42)||(curr==43)||(curr>34 && curr<39)){
            word+=curr;
        }
        else if(word!=""){
            if(count>checkk){
                resize();
            }
          //  print();
 //         cout<<word<<" "<<hashval<<endl;
            elements[hashval]=insert(word,book_code,page,paragraph,sentence_no,elements[hashval]);
            hashval=0;
            word="";
            continue;
        }
        hashval=(hashval+(((int)(curr-32))*products[word.length()-1]))&(size-1);
    }
    if(word!=""){
        elements[hashval]=insert(word,book_code,page,paragraph,sentence_no,elements[hashval]);
    }
    return;
}

int Dict::get_word_count(string word){
    Node* curr=elements[hashfunc(word)];
    while(curr){
        if(curr->val==word){
            return curr->wcount;
        }
        else if(curr->val<word){
            curr=curr->right;
        }
        else{
            curr=curr->left;
        }
    }
    return -1;
}
void dumper(fstream& f,Node* curr){
    if(curr){
        dumper(f,curr->left);
        dumper(f,curr->right);
        f<<curr->val<<", "<<curr->wcount<<endl;
    }
}
void Dict::dump_dictionary(string filename){
    fstream fout;
    fout.open(filename, ios::app);
    for(int i=0;i<size;i++){
        if(elements[i]){
            dumper(fout,elements[i]);
        }
    }
    fout.close();
    return;
}
void printer(Node* f){
    if(f){
        printer(f->left);
        printer(f->right);
        cout<<f->val;
     //  cout<<'*';
    }
}
void Dict::print(){
    cout<<count<<" "<<size<<"  ";
    for(int i=0;i<size;i++){
        if(elements[i]!=NULL){
            cout<<" || ";
            printer(elements[i]);
        //    cout<<endl;
        }
    }
    cout<<" ||"<<endl;
}

// int main(){
//     Dict d;
//     string sent1= "VOL.1: 1884 30 NOVEMBER, 1896 1";
//     //That's your, mind12. How can love &+ 123 1140 my678 grow? Love needs";
//     //a climate of love, love needs a climate of gratitude, thankfulness. Love needs a non-demanding atmosphere, non-expecting atmosphere. This is the second thing to remember.And the third thing is: Rather than thinking how to get love, start giving. If you give, you get. There is no other way. People are more interested in how to grab and get. Everybody is interested in getting and nobody seems to enjoy giving. People give very reluctantly—if ever they give, they give only to get, and they are almost businesslike. It is a bargain. They always go on watching to make sure they get more than they give—then it is a good bargain, good business. And the other is doing the same.Love is not a business, so stop being businesslike. Otherwise you will miss your life and love and all that is beautiful in it—because all that is beautiful is not at all businesslike. Business is the ugliest thing in the world—a necessary evil, but existence knows nothing of business. Trees bloom, it is not a business; the stars shine, it is not";
//     string sent2= "a business and you dont have to pay for it and nobody demands anything from you. A bird comes and sits at your door and sings a song, and the bird will not ask you for a certificate or some sign of appreciation. He has sung the song and then happily he flies away, leaving no traces behind.That's how love grows. Give, and don't wait to see how much you can grab. Yes, it comes, it comes a thousandfold, but it comes naturally. It comes on its own, there is no need to demand it. When you demand, it never comes. When you demand, you have killed it. So give. Start giving.In the beginning it will be hard, because your whole life you have been trained not to give but to get. In the beginning you will have to fight with your own armor. Your musculature has become hard, your heart has become frozen, you have become cold. In the beginning it will be difficult, but each step will lead to a further step, and by and by the river starts flowing.First get rid of your parents. In getting rid of your parents you get rid of society, in getting rid of your parents you get rid of civilization, education, everything because your parents represent all that. You become an individual. For the first time you are no longer part of the mass, you have an authentic individuality. You are on your own. This is what growth is. An IGC experiment in Zambia (Ashrafet al. 2016) embedded an experimentin a nationwide recruitment drive fora new healthcare position in Zambia to test whether career benefits attract talent at the expense of prosocial motivation.";
//     string sent3= "The research compared two adverts: one that promoted career incentives through job ads promoting career advancement  and the other, social incentives  with job ads listing helping the community as the main benefit.In line with common wisdom, the research found that emphasising career opportunities attracted fewer prosocial applicants. However, the trade-off only existed at low levels of talent; the marginal applicants in the career incentives advert group were more talented and equally prosocial. Workers recruited via career incentive ads conducted 29% more household visits and twice as many community mobilisation meetings over the 18-month period of the study. This also led to improved health outcomes, including a 25% reduction in the share of underweight children in areas with career incentive ads, and improved health behaviours including births at health facilities, breastfeeding, immunisations, and deworming. The findings allay the concern that offering material rewards for public sector jobs displaces applicants with desirable social preferences and ultimately worsens the quality of services provided. Similarly, Dal Bo et al. (2013) found that higher salaries for civil service jobs in Mexico attracted better qualified candidates with the same level of pro-social preferences. Impact and implications In 2018, the World Health Organization recommended, as part of a major guideline document on managing community health worker (CHW) programmes that “a career ladder should be offered to practising CHWs”, based entirely on the findings from IGCs study in Zambia. The findings also have implicationsfor policies such as maintaining the volunteer status of community-based work, or low salaries and lack of career incentives in teaching professions (Lehmann and Sanders 2007). Further work is required on how hiring career-minded individuals affects performance across different civil service jobs, particularly positions that arent new, and long-term outcomes such as employee turnover.";
//     d.insert_sentence(1,1,1,1,sent1);
//    // d.insert_sentence(2,2,2,2,sent2);
//   //  d.insert_sentence(3,3,3,3,sent3);
//     d.dump_dictionary("out.txt");
//     d.print();
//     return 0;
// }
/*
That’s your mind. How can love grow? Love needs a climate of love, love needs a climate of gratitude, thankfulness. Love needs a non-demanding atmosphere, non-expecting atmosphere. This is the second thing to remember.And the third thing is: Rather than thinking how to get love, start giving. If you give, you get. There is no other way. People are more interested in how to grab and get. Everybody is interested in getting and nobody seems to enjoy giving. People give very reluctantly—if ever they give, they give only to get, and they are almost businesslike. It is a bargain. They always go on watching to make sure they get more than they give—then it is a good bargain, good business. And the other is doing the same.Love is not a business, so stop being businesslike. Otherwise you will miss your life and love and all that is beautiful in it—because all that is beautiful is not at all businesslike. Business is the ugliest thing in the world—a necessary evil, but existence knows nothing of business. Trees bloom, it is not a business; the stars shine, it is not a business and you don’t have to pay for it and nobody demands anything from you. A bird comes and sits at your door and sings a song, and the bird will not ask you for a certificate or some sign of appreciation. He has sung the song and then happily he flies away, leaving no traces behind.That’s how love grows. Give, and don’t wait to see how much you can grab. Yes, it comes, it comes a thousandfold, but it comes naturally. It comes on its own, there is no need to demand it. When you demand, it never comes. When you demand, you have killed it. So give. Start giving.In the beginning it will be hard, because your whole life you have been trained not to give but to get. In the beginning you will have to fight with your own armor. Your musculature has become hard, your heart has become frozen, you have become cold. In the beginning it will be difficult, but each step will lead to a further step, and by and by the river starts flowing.First get rid of your parents. In getting rid of your parents you get rid of society, in getting rid of your parents you get rid of civilization, education, everything—because your parents represent all that. You become an individual. For the first time you are no longer part of the mass, you have an authentic individuality. You are on your own. This is what growth is.
An IGC experiment in Zambia (Ashrafet al. 2016) embedded an experimentin a nationwide recruitment drive fora new healthcare position in Zambia to test whether career benefits attract talent at the expense of prosocial motivation. The research compared two adverts: one that promoted career incentives – through job ads promoting career advancement – and the other, social incentives – with job ads listing ‘helping the community’ as the main benefit.In line with common wisdom, the research found that emphasising career opportunities attracted fewer prosocial applicants. However, the trade-off only existed at low levels of talent; the marginal applicants in the career incentives advert group were more talented and equally prosocial. Workers recruited via career incentive ads conducted 29% more household visits and twice as many community mobilisation meetings over the 18-month period of the study. This also led to improved health outcomes, including a 25% reduction in the share of underweight children in areas with career incentive ads, and improved health behaviours including births at health facilities, breastfeeding, immunisations, and deworming. The findings allay the concern that offering material rewards for public sector jobs displaces applicants with desirable social preferences and ultimately worsens the quality of services provided. Similarly, Dal Bo et al. (2013) found that higher salaries for civil service jobs in Mexico attracted better qualified candidates with the same level of pro-social preferences. Impact and implications In 2018, the World Health Organization recommended, as part of a major guideline document on managing community health worker (CHW) programmes that “a career ladder should be offered to practising CHWs”, based entirely on the findings from IGC’s study in Zambia. The findings also have implicationsfor policies such as maintaining the volunteer status of community-based work, or low salaries and lack of career incentives in teaching professions (Lehmann and Sanders 2007). Further work is required on how hiring career-minded individuals affects performance across different civil service jobs, particularly positions that aren’t new, and long-term outcomes such as employee turnover.*/