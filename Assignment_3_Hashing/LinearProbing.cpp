#include "LinearProbing.h"
using namespace std;
LinearProbing::LinearProbing(){
    mod=100169;
    min=mod-1;
    bankStorage1d.resize(mod);
    size=0;
    prime.resize(4);
    prime[0]=1;
    for(int i=1;i<4;i++){
        prime[i]=prime[i-1]*29;
    }
}
void LinearProbing::createAccount(std::string id, int count) {
    Account acc;
    acc.id=id;
    acc.balance = count;
    int pos=hash(id);
    while(bankStorage1d[pos].id!="" ){
        pos=(pos+1)%mod;
    }
     if(pos<min){
         min=pos;
     }
    bankStorage1d[pos]=acc;
    size++;
}

std::vector<int> LinearProbing::getTopK(int k){
    if(k>size){
        k=size;
    }
    vector<int> money(size);
    int t=0;
    for(int i=min;i<mod;i++){
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

int LinearProbing::getBalance(std::string id){
    int pos=hash(id);
    int t=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+1)%mod;
        if(pos==t){
            return -1;
        }
    }
    return bankStorage1d[pos].balance; 
}

void LinearProbing::addTransaction(std::string id, int count) {
    int pos=hash(id);
    int t=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+1)%mod;
        if(pos==t){
            createAccount(id,count);
            return;
        }
    }
    bankStorage1d[pos].balance+=count;
}

bool LinearProbing::doesExist(std::string id) {
    int pos=hash(id);
    int t=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+1)%mod;
        if(pos==t){
            return false;
        }
    }
    return true;
}

bool LinearProbing::deleteAccount(std::string id) {
    int pos=hash(id);
    int t=pos;
    while(bankStorage1d[pos].id!=id){
        pos=(pos+1)%mod;
        if(pos==t){
            return false;
        }
    }
    bankStorage1d[pos].id="";
    size--;
    return true;
}
int LinearProbing::databaseSize() {
    return size;
}

int LinearProbing::hash(std::string id) {
    int hashval=0;
    for(int i=0;i<4;i++){
        hashval=hashval+(id[i]-'A'+1)*(prime[i]);
    }
    hashval=(hashval)%(mod);
    int mul=0;
    for(int j=4;j<11;j+=2){
        mul=mul*10 + (id[j]-'0');
    }
    hashval=(hashval+mul)%mod;
    mul=0;
    for(int j=12;j<22;j+=2){
        mul=mul*10 + (id[j]-'0');
    }
    hashval=(hashval+mul)%mod;
    return hashval;
}


/*int main(){
    LinearProbing l1;
    l1.createAccount("ABCD1234567_0123456789",120);
    l1.addTransaction("ABCE1234567_0123456789",240);
    l1.createAccount("AJCD1434567_0123456789",121);
    l1.addTransaction("AKCE1234567_0123456789",241);
    l1.createAccount("ABMD1234567_0123456789",122);
    l1.addTransaction("ABCP1234567_0123456789",242);
    l1.createAccount("TBCD1234567_0123456789",123);
    l1.addTransaction("ABYE1234567_0123456789",243);
    l1.createAccount("AUCD1234567_0123456789",124);
    l1.addTransaction("AICE1234567_0123456789",244);
    l1.createAccount("ABQD1234567_0123456789",125);
    l1.addTransaction("ABSE1234567_0123456789",245);

    l1.getTopK(7);
    cout<<l1.databaseSize()<<endl;
}*/
