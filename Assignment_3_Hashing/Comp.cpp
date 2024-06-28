#include "Comp.h"
using namespace std;
Comp::Comp(){
    mod=100043;
    size=0;
    bankStorage1d.resize(mod);
    travel= 41 ; 
    prime1.resize(4);
    prime1[0]=1;
    for(int i=1;i<4;i++){
        prime1[i]=prime1[i-1]*29;
    }
    prime2.resize(10);
    prime2[0]=1;
    for(int i=1;i<10;i++){
        prime2[i]=((prime2[i-1])*10)%mod;
    }
}
void Comp::createAccount(std::string id, int count) {
    Account acc;
    acc.id=id;
    acc.balance=count;
    int pos=hash(id);
    while(bankStorage1d[pos].id!=""){
        pos=(pos+travel)%mod;
    }
    bankStorage1d[pos]=acc;
    size++;
}

std::vector<int> Comp::getTopK(int k) {
    if(k>size){
        k=size;
    }
    vector<int> money(size);
    int t=0;
    for(int i=0;i<mod;i++){
        if(bankStorage1d[i].id!=""){
            money[t]=bankStorage1d[i].balance;
            t++;
        }
        if(t==size){
            break;
        }
    }
    sort(money,size,k);
    int j=size-1;
    vector<int> ans(k);
    for(int i=0;i<k;i++){
        ans[i]=money[j];
        j--;
    }
    return ans;
}

int Comp::getBalance(std::string id) {
    int pos=hash(id);
    int k=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+travel)%mod;
        if(pos==k){
            return -1;
        }
    }
    return bankStorage1d[pos].balance;
}

void Comp::addTransaction(std::string id, int count) {
    int pos=hash(id);
    int k=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+travel)%mod;
        if(pos==k){
            createAccount(id,count);
            return;
        }
    }
    bankStorage1d[pos].balance+=count;
}

bool Comp::doesExist(std::string id) {
    int pos=hash(id);
    int k=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+travel)%mod;
        if(pos==k){
            return false;
        }
    }
    return true;
}

bool Comp::deleteAccount(std::string id) {
    int pos=hash(id);
    int k=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+travel)%mod;
        if(pos==k){
            return false;
        }
    }
    bankStorage1d[pos].id="";
    size--;
    return true;
    
}
int Comp::databaseSize() {
    return size;
}

int Comp::hash(std::string id) {
    int hashval=0;
    for(int i=0;i<4;i++){
        hashval=hashval+(id[i]-'A'+1)*(prime1[i]);
    }
    hashval=(hashval)%mod;
    for(int i=4;i<11;i++){
        hashval= hashval+ (id[i]-'0')*(prime2[i-4]);
    }
    hashval=(hashval)%mod;
    for(int i=12;i<22;i++){
        hashval=hashval + (id[i]-'0')*(prime2[i-12]);
    }
    return (hashval%mod);
}


// Feel free to add any other helper functions you need
// Good Luck!