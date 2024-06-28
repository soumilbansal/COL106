#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int size;
    int mod;
    int travel;
    std::vector<int> prime1;
    std::vector<int> prime2;
    void merger(std::vector<int>& arr,int l,int m,int r){
        int i=l;
        int j=m+1;
        int z=0;
        int b[r-l+1];
        while(i<=m && j<=r){
            if(arr[i]<=arr[j]){
                b[z++]=arr[i++];
            }
            else{
                b[z++]=arr[j++];
            }
        }
        while(i<=m){
            b[z++]=arr[i++];
        }
        while(j<=r){
            b[z++]=arr[j++];
        }
        for(int k=0;k<r-l+1;k++){
            arr[l+k]=b[k];
        }
    }
    void mergesort(std::vector<int>& a,int l,int r ){
        if(r<=l){
            return;
        }
        int m=(l+r)/2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        merger(a,l,m,r);
    }
    
    void bubblesort(std::vector<int>& a,int n,int k){
        if(k==n){
            k=n-1;
        }
        bool order = true;
        int j=n;
        while(order && k!=0){
            order = false;
            for (int i = 0; i <j-1; i++){
                if (a[i]>a[i+1] )
                {
                    int temp=a[i];
                    a[i]=a[i+1];
                    a[i+1]=temp;
                    order = true;
                }
                
            }
            k--;
            j--;
        }
    }


    void sort(std::vector<int>& vec,int n,int k){
        if(k<=8){
            bubblesort(vec,n,k);
        }
        else{
            mergesort(vec,0,n-1);
        }
    }
};

#endif // COMP_H
