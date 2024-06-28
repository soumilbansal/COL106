#include "CubicProbing.h"
using namespace std;
CubicProbing::CubicProbing(){
    size=0;
    mod=100043;
    bankStorage1d.resize(mod);
    prime.resize(4);
    prime[0]=1;
    for(int i=1;i<4;i++){
        prime[i]=prime[i-1]*29;
    }
}
void CubicProbing::createAccount(std::string id, int count) {
    Account acc;
    acc.id=id;
    acc.balance = count;
    int pos=hash(id);
    int t=pos;
    long long i=0;
    while(bankStorage1d[pos].id!=""){
        i++;
        pos=(t+i*i*i)%mod;
    }
    bankStorage1d[pos]=acc;
    size++;
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
    int pos=hash(id);
    int t=pos;
    long long i=0;
    while(bankStorage1d[pos].id!=id){
        i++;
        pos=(t+i*i*i)%mod;
        if(i==mod){
            return -1;
        }
    }
    return bankStorage1d[pos].balance;
}

void CubicProbing::addTransaction(std::string id, int count) {
    int pos=hash(id);
    int t=pos;
    long long i=0;
    while(bankStorage1d[pos].id!=id){
        i++;
        pos=(t+i*i*i)%mod;
        if(i==mod){
            createAccount(id,count);
            return;
        }
    }
    bankStorage1d[pos].balance+= count;
}

bool CubicProbing::doesExist(std::string id) {
    int pos=hash(id);
    int t=pos;
    long long i=0;
    while(bankStorage1d[pos].id!=id){
        i++;
        pos=(t+i*i*i)%mod;
        if(i==mod){
            return false;
        }
    }
    return true;
}

bool CubicProbing::deleteAccount(std::string id) {
    int pos=hash(id);
    int t=pos;
    long long i=0;
    while(bankStorage1d[pos].id!=id){
        i++;
        pos=(t+i*i*i)%mod;
        if(i==mod){
            return false;
        }
    }
    bankStorage1d[pos].id="";
    size--;
    return true;
}
int CubicProbing::databaseSize() {
    return size; 
}

int CubicProbing::hash(std::string id) {
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
