#include "Chaining.h"

using namespace std;
Chaining::Chaining(){
    mod=18269;
    bankStorage2d.resize(mod);
    size=0;
    min=mod;
    prime.resize(4);
    prime[0]=1;
    for(int i=1;i<4;i++){
        prime[i]=prime[i-1]*29;
    }
}
void Chaining::createAccount(std::string id, int count) {
    int pos=hash(id);
    if(pos<min){
        min=pos;
    }
    Account acc;
    acc.id=id; acc.balance=count;
    bankStorage2d[pos].push_back(acc);
    size++;
}

std::vector<int> Chaining::getTopK(int k){
    vector<int> alldata(size);
    vector<vector<Account> >::iterator it1=bankStorage2d.begin()+min;
    int c=0;
    while(c!=size){
        vector<Account>::iterator it2=(*it1).begin();
        while(it2!=(*it1).end()){
            alldata[c++]=(*it2).balance;
            it2++;
        }
        it1++;
    }
    if(k>size){
        k=size;
    }
    sort(alldata,size,k);
    int j=size-1;
    vector<int> ans(k);
    for(int i=0;i<k;i++){
        ans[i]=alldata[j];
        j--;
    }
    return ans;
}

int Chaining::getBalance(std::string s) {
    int pos=hash(s);
    vector<Account>::iterator it =(bankStorage2d[pos]).begin();
    while(it!=(bankStorage2d[pos]).end()){
        if((*it).id==s){
            return (*it).balance;
        }
        it++;
    }
    return -1; 
}

void Chaining::addTransaction(std::string id, int count) {
    int pos=hash(id);
    vector<Account >::iterator it =(bankStorage2d[pos]).begin();
    while(it!=(bankStorage2d[pos]).end()){
        if((*it).id==id){
            (*it).balance+=count;
            return;
        }
        it++;
    }
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    int pos=hash(id);
    vector<Account >::iterator it =(bankStorage2d[pos]).begin();
    while(it!=(bankStorage2d[pos]).end()){
        if((*it).id==id){
            return true;
        }
        it++;
    }
    return false; 
}

bool Chaining::deleteAccount(std::string id) {
    int pos=hash(id);
    vector<Account>::iterator it =(bankStorage2d[pos]).begin();
    while(it!=(bankStorage2d[pos]).end()){
        if((*it).id==id){
            (bankStorage2d[pos]).erase(it);
            size--;
            return true;
        }
        it++;
    }
    return false;
}
int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id){
    int hashval=0;
    for(int i=0;i<4;i++){
        hashval+=(id[i]-'A'+1)*(prime[i]);
    }
    hashval=(hashval)%(mod);
    int mul=0;
    for(int j=4;j<11;j+=2){
        mul=mul*10 + (id[j]-'0');
    }
    mul++;
    hashval=(hashval+mul)%mod;
    mul=0;
    for(int j=12;j<22;j+=2){
        mul=mul*10 + (id[j]-'0');
    }
    hashval=(hashval+mul)%mod;
    return hashval;
}

/*void print(vector<vector<Account> > vec){
    int n=vec.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<vec[i].size();j++){
            cout<<i<<" "<<vec[i][j].id<<"  ";
        }
    }
    cout<<endl;
}*/

/*int main(){
    Chaining l1;
    l1.createAccount("ABCD1234567_0123456789",120);
     l1.addTransaction("ABCE1234567_0123456789",240);
     l1.createAccount("AJCD1434567_0123456789",121);
     l1.addTransaction("AKCE1234567_0123456789",241);
     l1.createAccount("ABDF1234567_0123456789",122);

    l1.getTopK(1000000);
    cout<<l1.databaseSize()<<endl;
}*/



