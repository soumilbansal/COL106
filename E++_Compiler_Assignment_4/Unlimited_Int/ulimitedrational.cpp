/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
//#include "ulimitedint.cpp"

/// 
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
/// 

UnlimitedInt* gcdd(UnlimitedInt* i1,UnlimitedInt* i2){
    UnlimitedInt* i3=i1->mod(i1,i2);
    if(i3->get_size()==1 && i3->to_string()=="0"){
        return i2;
    }
    return gcdd(i2,i3);
}
UnlimitedInt* gcd(UnlimitedInt* i1,UnlimitedInt* i2){
    int n1=i1->get_size();
    int n2=i2->get_size();
    if(n1>n2){
        return gcdd(i1,i2);
    }
    else if(n2>n1){
        return gcdd(i2,i1);
    }
    string s1=i1->to_string();
    string s2=i1->to_string();
    if(s1>s2){
        return gcdd(i1,i2);
    }
    return gcdd(i2,i1);
}


UnlimitedRational::UnlimitedRational(){

}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p=num;
    q=den;
}

 UnlimitedRational::~UnlimitedRational(){ 
    if(p!=NULL){
        p->~UnlimitedInt();
        p=NULL;
    }
    if(q!=NULL){
        q->~UnlimitedInt(); 
        q=NULL;
    }
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    string s=p->to_string();
    return s;
}

string UnlimitedRational::get_q_str(){
    
    return q->to_string();
}

// FINDING GCD OF TWO INTS..
    
string UnlimitedRational::get_frac_str(){
    if(q->get_sign()==0){
        return "0/0";
    }
    string s1=p->to_string();
    string s2=q->to_string();
    return (s1+'/'+s2);
} // Return the rational as "p/q"

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=i1->get_p();
    UnlimitedInt* den1=i1->get_q();
    UnlimitedInt* num2=i2->get_p();
    UnlimitedInt* den2=i2->get_q();
    if(den1->get_sign()==0 || den2->get_sign()==0){
        UnlimitedInt* added1=new UnlimitedInt(0);
        UnlimitedInt* added2=new UnlimitedInt(0);
        UnlimitedRational* rat=new UnlimitedRational(added1,added2);
        return rat;
    }
    UnlimitedInt* add1= num1->mul(num1,den2);
    UnlimitedInt* add2= num2->mul(num2,den1);
    UnlimitedInt* num3=add1->add(add1,add2);
    UnlimitedInt* den3=den1->mul(den1,den2);
    UnlimitedInt* pos1=new UnlimitedInt(num3->get_array(),num3->get_capacity(),1,num3->get_size());
    UnlimitedInt* pos2=new UnlimitedInt(den3->get_array(),den3->get_capacity(),1,den3->get_size());
    UnlimitedInt* GCD=gcd(pos1,pos2);
    UnlimitedRational* rat;
    if(GCD->get_size()==1 && GCD->get_array()[0]==1){
        rat=new UnlimitedRational(num3,den3);
        return rat;
    }
    rat=new UnlimitedRational(num3->div(num3,GCD),den3->div(den3,GCD));
    return rat;
}
 UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
     UnlimitedInt* num1=i1->get_p();
    UnlimitedInt* den1=i1->get_q();
    UnlimitedInt* num2=i2->get_p();
    UnlimitedInt* den2=i2->get_q();
    if(den1->get_sign()==0 || den2->get_sign()==0){
        UnlimitedInt* added1=new UnlimitedInt(0);
        UnlimitedInt* added2=new UnlimitedInt(0);
        UnlimitedRational* rat=new UnlimitedRational(added1,added2);
        return rat;
    }
    UnlimitedInt* add1= num1->mul(num1,den2);
    UnlimitedInt* add2= num2->mul(num2,den1);
    UnlimitedInt* num3=add1->sub(add1,add2);
    UnlimitedInt* den3=den1->mul(den1,den2);
    UnlimitedInt* pos1=new UnlimitedInt(num3->get_array(),num3->get_capacity(),1,num3->get_size());
    UnlimitedInt* pos2=new UnlimitedInt(den3->get_array(),den3->get_capacity(),1,den3->get_size());
    UnlimitedInt* GCD=gcd(pos1,pos2);
    UnlimitedRational* rat;
    if(GCD->get_size()==1 && GCD->get_array()[0]==1){
        rat=new UnlimitedRational(num3,den3);
        return rat;
    }
    rat=new UnlimitedRational(num3->div(num3,GCD),den3->div(den3,GCD));
    return rat;
 }
 UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=i1->get_p();
    UnlimitedInt* den1=i1->get_q();
    UnlimitedInt* num2=i2->get_p();
    UnlimitedInt* den2=i2->get_q();
    if(den1->get_sign()==0 || den2->get_sign()==0){
        UnlimitedInt* added1=new UnlimitedInt(0);
        UnlimitedInt* added2=new UnlimitedInt(0);
        UnlimitedRational* rat=new UnlimitedRational(added1,added2);
        return rat;
    }
    UnlimitedInt* num3=num1->mul(num1,num2);
    UnlimitedInt* den3=den1->mul(den1,den2);
    UnlimitedInt* pos1=new UnlimitedInt(num3->get_array(),num3->get_capacity(),1,num3->get_size());
    UnlimitedInt* pos2=new UnlimitedInt(den3->get_array(),den3->get_capacity(),1,den3->get_size());
    UnlimitedInt* GCD=gcd(pos1,pos2);
    UnlimitedRational* rat;
    if(GCD->get_size()==1 && GCD->get_array()[0]==1){
        rat=new UnlimitedRational(num3,den3);
        return rat;
    }
    rat=new UnlimitedRational(num3->div(num3,GCD),den3->div(den3,GCD));
    return rat;
 }
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1=i1->get_p();
    UnlimitedInt* den1=i1->get_q();
    UnlimitedInt* num2=i2->get_p();
    UnlimitedInt* den2=i2->get_q();
    if(den1->get_sign()==0 || den2->get_sign()==0 || (num2->get_size()==1 && num2->to_string()=="0")){
        UnlimitedInt* added1=new UnlimitedInt(0);
        UnlimitedInt* added2=new UnlimitedInt(0);
        UnlimitedRational* rat=new UnlimitedRational(added1,added2);
        return rat;
    }
    UnlimitedInt* num3=num1->mul(num1,den2);
    UnlimitedInt* den3=den1->mul(den1,num2);
    UnlimitedInt* pos1=new UnlimitedInt(num3->get_array(),num3->get_capacity(),1,num3->get_size());
    UnlimitedInt* pos2=new UnlimitedInt(den3->get_array(),den3->get_capacity(),1,den3->get_size());
    UnlimitedInt* GCD=gcd(pos1,pos2);
    UnlimitedRational* rat;
    if(GCD->get_size()==1 && GCD->get_array()[0]==1){
        rat=new UnlimitedRational(num3,den3);
        return rat;
    }
    rat=new UnlimitedRational(num3->div(num3,GCD),den3->div(den3,GCD));
    return rat;
}

//  int main(){
//    UnlimitedInt* obj1=new UnlimitedInt("89848280384390820788938498394898585778038740734750357482783109840");
//    cout<<obj1->to_string()<<"  "<<obj1->get_size()<<endl;
//     UnlimitedInt* obj2=new UnlimitedInt("85734029809884782039888340849808378470347423979370880921");
//     cout<<obj2->to_string()<<"  "<<obj2->get_size()<<endl;
//     UnlimitedInt* obj3=gcd(obj1,obj2);
//     cout<<obj3->to_string()<<endl;
    //UnlimitedInt obj3("0");
  //  cout<<obj3.to_string()<<"  "<<obj3.get_size()<<endl;
    // UnlimitedInt obj4("56");
//     cout<<obj4.to_string()<<"  "<<obj4.get_size()<<endl;
  //   UnlimitedRational* obj5=new UnlimitedRational(obj1,obj2);
   //  obj5->~UnlimitedRational();
 //    UnlimitedRational obj6(&obj3,&obj4);
    //  cout<<obj5.get_frac_str()<<endl;
    //  cout<<obj6.get_frac_str()<<endl;
 //    UnlimitedRational* obj11=obj5.mul(&obj5,&obj6);
    //  UnlimitedInt* obj7=obj1.mul(&obj1,&obj3);
    //  UnlimitedInt* obj8=obj2.mul(&obj2,&obj4);
    // UnlimitedInt* obj9=obj7->add(obj7,obj8);
    // UnlimitedInt* obj10=obj2.mul(&obj2,&obj4);
    // cout<<obj7->to_string()<<endl;
    //  cout<<obj8->to_string()<<endl;
    //  UnlimitedRational* obj11=obj5.div(&obj5,&obj6);
    //   cout<<obj7->to_string()<<endl;
    //  cout<<obj8->to_string()<<endl;
//      cout<<obj9->to_string()<<endl;
//      cout<<obj10->to_string()<<endl;
    //    cout<<obj11->get_frac_str()<<endl;
    //    obj7->~UnlimitedInt();
    //    obj8->~UnlimitedInt();
    //    obj11->~UnlimitedRational();
    //    obj11->get_p()->~UnlimitedInt();
    //    obj11->get_q()->~UnlimitedInt();
    //    obj11->~UnlimitedRational();
//    return 0;
// }