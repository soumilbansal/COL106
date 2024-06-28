/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
//#include <iostream>
using namespace std;

typedef basic_string<unsigned char> ustring;

ustring mystring(UnlimitedInt* i){
    int* a=i->get_array();
    int size=i->get_size();

    ustring s;
    for(int i=0;i<size;i++){
        unsigned char b=a[i]+'0';
        s=b+s;
    }
    return s;
}
UnlimitedInt::UnlimitedInt(){

}
UnlimitedInt::~UnlimitedInt(){
    if(unlimited_int!=NULL){
        delete[] unlimited_int;
        unlimited_int=NULL;
    }
}
string UnlimitedInt::to_string(){
    string s;
    for(int i=0;i<size;i++){
        char a=unlimited_int[i]+'0';
        s=a+s;
    }
    if(sign==-1){
        s='-'+s;
    }
    return s;
}
// FINDING THE GCD OF TWO INT..
// UnlimitedInt* gcd(UnlimitedInt* i1,UnlimitedInt* i2){
//     int n1=i1->get_size();
//     int n2=i2->get_size();
//     UnlimitedInt* i3;
//     UnlimitedInt* i4;
//     if(n1>n2){
//         i4=i1->mod(i1,i2);
//         if(i4->get_size()==1 && i4->get_array()[0]==0){
//             return i2;
//         }
//         i3=i1->sub(i1,i2);
//         return gcd(i2,i3);
//     }
//     else if(n1<n2){
//         i4=i2->mod(i2,i1);
//         if(i4->get_size()==1 && i4->get_array()[0]==0){
//             return i1;
//         }
//         i3=i2->sub(i2,i1);
//         return gcd(i1,i3);
//     }
//     else{
//         int* a=i1->get_array();
//         int* b=i2->get_array();
//         int ind=n1-1;
//         bool big=false;
//         while(ind>-1){
//                 if(a[ind]>b[ind]){
//                     big=true;
//                     break;
//                 }
//                 if(a[ind]<b[ind]){
//                     big=false;
//                     break;
//                 }
//                 ind--;
//         }
//         if(ind==-1){
//             return i1;
//         }
//         if(big){
//             i4=i1->mod(i1,i2);
//             if(i4->get_size()==1 && i4->get_array()[0]==0){
//                 return i2;
//             }
//             i3=i1->sub(i1,i2);
//             return gcd(i2,i3);
//         }
//         else{
//             i4=i2->mod(i2,i1);
//             if(i4->get_size()==1 && i4->get_array()[0]==0){
//                 return i1;
//             }
//             i3=i2->sub(i2,i1);
//             return gcd(i1,i3);
//         }
//     }
//     return NULL;
// }

// END OF GCD..

UnlimitedInt::UnlimitedInt(string s){
    int n=s.length();
    if(s[0]=='-'){
        sign=-1;
        size=n-1;
        capacity=size;
        int* mem=new int[capacity];
        unlimited_int=mem;
        for(int i=1;i<n;i++){
            unlimited_int[i-1]=s[n-i]-'0';
        }
    }
    else{
        sign=1;
        size=n;
        capacity=size;
        int* mem=new int[capacity];
        unlimited_int=mem;
        for(int i=0;i<n;i++){
            unlimited_int[i]=s[n-1-i]-'0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int i){
    if(i==0){
        size=1;
        unlimited_int=new int[1];
        unlimited_int[0]=0;
        sign=0;
    }
}
UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    sign=sgn;
    size=sz;
    unlimited_int=ulimited_int;
    capacity=cap;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_size(){
    return size;
}
int UnlimitedInt::get_capacity(){
    return capacity;
}

// LET US ADD.

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int n1=i1->get_size();
    int n2=i2->get_size();
    int s1=i1->get_sign();
    int s2=i2->get_sign();
    int* a=i1->get_array();
    int* b=i2->get_array();
    int max=n1>n2? n1 : n2;
    int* arr=new int[max+1];
    int j=0;
    int add;
    int carry=0;
    if(s1==s2){
        while(j<n1 && j<n2){
            add=a[j]+b[j]+carry;
            if(add>9){
                carry=1;
                add-=10;
            }
            else{
                carry=0;
            }
            arr[j]=add;
            j++;
        }
        while(j<n1){
            add=a[j]+carry;
            if(add>9){
                carry=1;
                add-=10;
            }
            else{
                carry=0;
            }
            arr[j]=add;
            j++;
        }
        while(j<n2){
            add=b[j]+carry;
            if(add>9){
                carry=1;
                add-=10;
            }
            else{
                carry=0;
            }
            arr[j]=add;
            j++;
        }
        if(carry!=0){
            arr[j]=carry;
        }
        else{
            j--;
        }
        UnlimitedInt* obj=new UnlimitedInt(arr,max+1,s1,j+1);
        return obj;
    }
    else{
        if(n1==n2){

            int ind=n1-1;
            bool big=false;
            while(ind>-1){
                if(a[ind]>b[ind]){
                    big=true;
                    break;
                }
                if(a[ind]<b[ind]){
                    big=false;
                    break;
                }
                ind--;
            }
            if(ind==-1){
                UnlimitedInt *obj=new UnlimitedInt("0");
                return obj;
            }
            while(j<=ind){
                if(big){
                    add=a[j]-b[j]+carry;
                }
                else{
                    add=b[j]-a[j]+carry;
                }
                if(add<0){
                    add+=10;
                    carry=-1;
                }
                else{
                    carry=0;
                }
                arr[j]=add;
                j++;
            }
            while(arr[j-1]==0){
                j--;
            }
            if(!big){
                s1=s2;
            }
            if(j==1 && arr[0]==0){
                return new UnlimitedInt("0");
            }
            UnlimitedInt* obj=new UnlimitedInt(arr,max+1,s1,j);
            return obj;
        }
        else if(n1<n2){
                while(j<n1){
                    add=b[j]-a[j]+carry;
                    if(add<0){
                        add+=10;
                        carry=-1;
                    }
                    else{
                        carry=0;
                    }
                    arr[j]=add;
                    j++;
                }
                while(j<n2){
                    add=b[j]+carry;
                    if(add<0){
                        carry=-1;
                        add+=10;
                    }
                    else{
                        carry=0;
                    }
                    arr[j]=add;
                    j++;
                }
                if(arr[j-1]==0){
                    j--;
                }
            UnlimitedInt* obj=new UnlimitedInt(arr,max+1,-s1,j);
            return obj;
            
        }
        else{
                while(j<n2){
                    add=a[j]-b[j]+carry;
                    if(add<0){
                        add+=10;
                        carry=-1;
                    }
                    else{
                        carry=0;
                    }
                    arr[j]=add;
                    j++;
                }
                while(j<n1){
                    add=a[j]+carry;
                    if(add<0){
                        carry=-1;
                        add+=10;
                    }
                    else{
                        carry=0;
                    }
                    arr[j]=add;
                    j++;
                }
            if(arr[j-1]==0){
                j--;
            }
            UnlimitedInt* obj=new UnlimitedInt(arr,max+1,-s2,j);
            return obj;
        }
    }

    return NULL;
}

// END OF ADD.

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* i3=new UnlimitedInt(i2->get_array(),i2->get_capacity(),-(i2->get_sign()),i2->get_size());
    return add(i1,i3);
}
void remov(string& s){
    int n=s.length()-1;
    int j=0;
    int count=0;
    while(j<n && s[j]=='0'){
        count++;
        j++;
    }
    if(count){
        s.erase(0,count);
    }
}
UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int n2=i2->get_size();
    int n1=i1->get_size();
    int s1=i1->get_sign();
    int s2=i2->get_sign();
    ustring str1=mystring(i1);
    ustring str2=mystring(i2);
    int pos=n1+n2-1,add,carry=0;
    string s;
    while(pos>0){
        add=carry;
        for(int i=n2-1;i>-1;i--){
            int j=pos-1-i;
            if(j<0 || j>n1-1){
                continue;
            }
            add+=(str1[j]-'0')*(str2[i]-'0');
        }
        char added=((add%10)+'0');
        s=added+s;
        carry=add/10;
        pos--;
    }
    if(carry!=0){
        char b=carry+'0';
        s=b+s;
    }
    remov(s);
    if(s1!=s2){
        s='-'+s;
    }
    UnlimitedInt* obj=new UnlimitedInt(s);
    return obj;

    
}

void subt(ustring&s1, ustring&s2,int i){
    int n=s2.length()-1;
    int carry=0, add=0;
    int j=0;
    while(n>-1){
        add=((s1[i-j]-'0')-(s2[n]-'0'))+carry;
        if(add<0){
            carry=-1;
            add+=10;
        }
        else{
            carry=0;
        }
        s1[i-j]='0'+add;
        n--;
        j++;
    }
}

bool compare(ustring s1,ustring s2,int i){
    int n=s2.length();
    int j=0;
    while(j<n){
        if(s1[i-n+1]!=s2[j]){
            return s1[i-n+1]>s2[j]? false : true;
        }
        i++;
        j++;
    }
    return false;
}

bool check(ustring s){
    int n=s.length()-1;
    while(n>-1){
        if(s[n]!='0'){
            return true;
        }
        n--;
    }
    return false;
}
void adder(string& s){
    int pos=s.length()-1;
    int carry=1;
    while(carry!=0 && pos>-1){
        if(s[pos]=='9'){
            s[pos]='0';
            continue;
        }
        s[pos]=s[pos]+1;
        carry=0;
        pos--;
    }
    if(carry!=0){
        s='1'+s;
    }
}
void remover(ustring& s){
    int n=s.length()-1;
    int j=0;
    int count=0;
    while(j<n && s[j]=='0'){
        count++;
        j++;
    }
    if(count){
        s.erase(0,count);
    }
}
// void print(ustring s){
//     int n=s.length();
//     int j=0;
//     while(j<n){
//         cout<<s[j];
//         j++;
//     }
//     cout<<endl;
// }

UnlimitedInt* UnlimitedInt::UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    int n2=i2->get_size();
    int n1=i1->get_size();
    int s1=i1->get_sign();
    int s2=i2->get_sign();
    if(n2==1 && i2->get_array()[0]==0){
        UnlimitedInt* added=new UnlimitedInt(0);
        return added;
    }
    if(n1<n2){
        if(s1==s2 || (n1==1 && i1->get_array()[0]==0)){
            UnlimitedInt* obj=new UnlimitedInt("0");
            return obj;
        }
        UnlimitedInt* obj=new UnlimitedInt("-1");
        return obj;
    }

    ustring str1=mystring(i1);
    ustring str2=mystring(i2);
    string quo="";
    int carry=0;
    int j=0;
    while(j<=n1-n2){
        int fac=0;
        while(str1[j]-'0'>str2[0]-'0'){
            subt(str1,str2,j+n2-1);
            fac++;
        }
        if(str1[j]==str2[0]){
            if(compare(str1,str2,j+n2-1)){
                char add=fac+'0';
                quo=quo+add;
                if(j==n1-n2){
                    break;
                }
                carry=10*(str1[j]-'0');
                str1[j+1]+=carry;
                str1[j]='0';
                j++;
                continue;
            }
            else{
                subt(str1,str2,j+n2-1);
                fac++;
            }
        }
        char add=fac+'0';
        quo=quo+add;
        if(j==n1-n2){
            break;
        }
        carry=10*(str1[j]-'0');
        str1[j+1]+=carry;
        str1[j]='0';
        j++;
    }
    if(quo[0]=='0'&& quo!="0"){
        quo.erase(0,1);
    }
    if(s1!=s2){
        if(check(str1)){
            adder(quo);
        }
        quo='-'+quo;
    }
    UnlimitedInt* obj=new UnlimitedInt(quo);
    return obj;

}


/*bool bigg(string s1,string s2){
    
}

void minuss(string& s1, string& s2){
    int n=s2.length()-1;
    int carry=0, add=0;
    int j=0;
    while(n>-1){
        add=(s1[n]-s2[n])+carry;
        if(add<0){
            carry=-1;
            add+=10;
        }
        else{
            carry=0;
        }
        s1[n]='0'+add;
        n--;
    }
}

bool checkk(string s){
    int n=s.length()-1;
    while(n>-1){
        if(s[n]!='0'){
            return true;
        }
        n--;
    }
    return false;
}
void adderr(string& s){
    int pos=s.length()-1;
    int carry=1;
    while(carry!=0 && pos>-1){
        if(s[pos]=='9'){
            s[pos]='0';
            continue;
        }
        s[pos]=s[pos]+1;
        carry=0;
        pos--;
    }
    if(carry!=0){
        s='1'+s;
    }
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1,UnlimitedInt* i2){
    int n2=i2->get_size();
    int n1=i1->get_size();
    int s1=i1->get_sign();
    int s2=i2->get_sign();
    if(n2==1 && i2->get_array()[0]==0){
        UnlimitedInt* added=new UnlimitedInt(0);
        return added;
    }
    if(n1<n2){
        if(s1==s2 || (n1==1 && i1->get_array()[0]==0)){
            UnlimitedInt* obj=new UnlimitedInt("0");
            return obj;
        }
        UnlimitedInt* obj=new UnlimitedInt("-1");
        return obj;
    }
    string str1=i1->to_string();
    string str2=i2->to_string();
    string temp="";
    int i;
    for(i=0;i<n2;i++){
        temp+=str1[i];
    }
    string quo;
    while(n1>=n2){
        int fac=0;
        while(temp[0]>str2[0]){
            minuss(temp,str2);
            fac++;
        }
        if(quo[0]==str2[0]){
            if(bigg(temp,str2)){
                minuss(temp,str2);
                fac++;
            }
        }
        char m='0'+fac;
        quo+=m;
        n1--;
        temp+=str1[i];
        i++;
    }

    if(quo[0]=='0' && quo!="0"){
        quo.erase(0,1);
    }
    if(s1!=s2){
        if(checkk(str1)){
            adderr(quo);
        }
        quo='-'+quo;
    }
    UnlimitedInt* lessgo=new UnlimitedInt(quo);
    return lessgo;
}
*/




string create(ustring s){
    int n =s.length();
    int j=0;
    string str;
    while(j<n){
        int val=s[j]-'0';
        char added=val+'0';
        str=str+added;
        j++;
    }
    return str;
}
UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    // int n2=i2->get_size();
    // int n1=i1->get_size();
    // int s1=i1->get_sign();
    // int s2=i2->get_sign();
    // if(n1<n2){
    //     UnlimitedInt* obj=new UnlimitedInt(i1->to_string());
    //     return obj;
    // }

    // ustring str1=mystring(i1);
    // ustring str2=mystring(i2);
    // string quo="";
    // int carry=0;
    // int j=0;
    // while(j<=n1-n2){
    //     int fac=0;
    //     while(str1[j]>str2[0]){
    //         subt(str1,str2,j+n2-1);
    //         fac++;
    //     }
    //     if(str1[j]==str2[0]){
    //         if(compare(str1,str2,j+n2-1)){
    //             char add=fac+'0';
    //             quo=quo+add;
    //             if(j==n1-n2){
    //                 break;
    //             }
    //             carry=10*(str1[j]-'0');
    //             str1[j+1]+=carry;
    //             str1[j]='0';
    //             j++;
    //             continue;
    //         }
    //         else{
    //             subt(str1,str2,j+n2-1);
    //             fac++;
    //         }
    //     }
    //     char add=fac+'0';
    //     quo=quo+add;
    //     if(j==n1-n2){
    //         break;
    //     }
    //     carry=10*(str1[j]-'0');
    //     str1[j+1]+=carry;
    //     str1[j]='0';
    //     j++;
    // }
    // remover(str1);
    // string t=create(str1);
    // if(s1==s2){
    //     UnlimitedInt* obj=new UnlimitedInt(t);
    //     return obj;
    // }
    // if(s1==1){
    //     UnlimitedInt* obj=new UnlimitedInt(t);
    //     return obj;
    // }
    // t='-'+t;
    // UnlimitedInt* obj=new UnlimitedInt(t);
    // return obj;
    return new UnlimitedInt(sub(i1,mul(i2,div(i1,i2)))->to_string());
}

// int main(){
//      UnlimitedInt obj1("-900");
//      cout<<obj1.to_string()<<"  "<<obj1.get_size()<<endl;
//      UnlimitedInt obj2("-91");
//      cout<<obj2.to_string()<<"  "<<obj2.get_size()<<endl;
//      UnlimitedInt* obj3=obj1.mod(&obj1,&obj2);
//       cout<<obj3->to_string()<<endl;
    //  UnlimitedInt* obj4=obj3->mul(&obj2,obj3);
    //  cout<<obj4->to_string()<<endl;
    // UnlimitedInt* obj5=obj5->sub(&obj1,obj4);
    //  cout<<obj5->to_string()<<endl;
    //  cout<<obj5->get_size()<<endl;
//     return 0;
// }