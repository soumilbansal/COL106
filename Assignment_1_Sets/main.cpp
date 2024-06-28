
#include <iostream>
using namespace std;

class object{
    public:
    int data;
    object* next;
    object* prev;
    object(int a, object* ne=NULL, object* pre= NULL){
        data=a;
        next=ne;
        prev=pre;
    }
};
// SET list;
class SET{
    public:
    int size;
    object* begin;
    object* end;
    // CONSTRUCTOR...
    SET(){
        size=0;
        begin=NULL;
        end=NULL;
    }
    
    void Size(){
        cout<<size<<endl;
    }
    
    // INSERTION...
    int Insert(int a){
        if(size==0){
            begin= new object(a);
            end=begin;
            size++;
            return size;
        }
        if(end->data<a){
            object* added= new object(a);
            end->next=added;
            added->prev=end;
            end=added;
            size++;
            return size;
        }
            object* pos= begin;
            while(pos->data < a){
                pos=pos->next;
            }
            // check uniqueness of element 
            if(pos->data==a){
                return size;
            }
                object* added= new object(a);
                if(pos==begin){
                    pos->prev=added;
                    added->next=pos;
                    begin=added;
                }
                else{
                    pos->prev->next= added;
                    added->prev=pos->prev;
                    added->next= pos;
                    pos->prev=added;
                }
                size++;
                return size;
    }
    
    // DELETION...
    int Delete(int a){
        if(size==0){
            return 0;
        }
        if(begin->data==a){
            if(size==1){
                begin=NULL;
                end=NULL;
                size--;
                return size;
            }
            begin=begin->next;
            begin->prev=NULL;
            size--;
            return size;
        }
        if(end->data<a){
            return size;
        }
        if(end->data==a){
            object* user=end;
            end=end->prev;
            end->next=NULL;
            size--;
            return size;
        }
        object* find=begin;
        while(find->data<a){
            find=find->next;
        }
        if(find->data==a){
            find->next->prev= find->prev;
            find->prev->next=find->next;
            size--;
        }
        return size;
    }
    
    // CHECK IF AN ELEMENT IS PRESENT OR NOT
    int Belongs(int a){
        if(size==0){
            return 0;
        }
        if(begin->data>a || end->data<a){
            return 0;
        }
        object* finder= begin;
        while(finder->data < a){
            finder= finder->next;
        }
        return finder->data==a? 1:0 ;
    }
    
    // UNION OF TWO SETS..
    
    int Union(object* begin2){
        object* start1= begin;
        object* start2= begin2;
        if(size==0){
            if(start2!=NULL){
                object* add=new object(start2->data);
                begin=add;
                end=add;
                size++;
                start2=start2->next;
                start1=begin;
            }
        }
        while(start2!=NULL){
            if(start1==NULL){
                while(start2!=NULL){
                    object* insert= new object(start2->data);
                    insert->prev=end;
                    end->next=insert;
                    end=insert;
                    start2=start2->next;
                    size++;
                }
                break;
            }
            else{
                if(start1->data<start2->data){
                    start1=start1->next;
                }
                else if(start1->data==start2->data){
                    start2=start2->next;
                }
                else{
                    object* insert= new object(start2->data);
                    if(start1==begin){
                        begin= insert;
                        insert->next=start1;
                        start1->prev=insert;
                    }
                    else{
                        start1->prev->next=insert;
                        insert->prev=start1->prev;
                        insert->next=start1;
                        start1->prev=insert;
                    }
                    start2=start2->next;
                    size++;
                }
            }
        }
        return size;
    }
    
    // INTERSECTION OF 2 SETS..
    
    int Intersection(object* begin2){
        object* start2= begin2;
        object* start1= begin;
        while(start2 != NULL && start1!=NULL){
            if(start1->data<start2->data){
                if(start1==begin){
                    if(start1!=end){
                        begin=start1->next;
                        begin->prev=NULL;
                        delete start1;
                        start1=begin;
                    }
                    else{
                        delete start1;
                        begin=NULL;
                        end=NULL;
                        start1=NULL;
                    }
                    size--;
                    continue;
                }
                if(start1==end){
                    end=start1->prev;
                    end->next=NULL;
                    delete start1;
                    size--;
                    start1=NULL;
                    break;
                }
                start1->next->prev=start1->prev;
                start1->prev->next=start1->next;
                start1=start1->next;
                size--;
            }
            else if(start1->data==start2->data){
                start1=start1->next;
                start2=start2->next;
            }
            else{
                start2=start2->next; 
            }
        }
        while(start1!=NULL){
            
            if(start1==end){
                if(start1==begin){
                    begin=NULL;
                    end=NULL;
                    delete start1;
                    size--;
                    return size;
                }
                end=start1->prev;
                end->next=NULL;
                delete start1;
                size--;
                break;
            }
            if(start1==begin){
                begin=NULL;
                end=NULL;
                size=0;
                return size;
            }
            start1->next->prev=start1->prev;
            start1->prev->next=start1->next;
            start1=start1->next;
            size--;
        }
        
        return size;
    }
    
    // DIFFERENCE OF TWO SETS
   int difference(object* begin2){
       if(begin2==begin){
           begin=NULL;
           end=NULL;
           return size=0;
       }
        object* start1= begin;
        object* start2= begin2;
        while(start1 != NULL && start2!=NULL){
            if(start2->data==start1->data){
                if(start1==begin){
                    if(start1==end){
                        begin=NULL;
                        end=NULL;
                        delete start1;
                        size--;
                        break;
                    }
                    else{
                        begin=start1->next;
                        begin->prev=NULL;
                        delete start1;
                        start1=begin;
                        start2=start2->next;
                        size--;
                        continue;
                    }
                    
                }
                if(start1==end){
                    end=start1->prev;
                    end->next=NULL;
                    delete start1;
                    size--;
                    break;
                }
                
                start1->next->prev=start1->prev;
                start1->prev->next=start1->next;
                start1=start1->next;
                
                size--;
            }
            else if(start1->data<start2->data){
                start1=start1->next;
            }
            else{
                start2=start2->next;
            }
        }
        return size;
    }
    
    // REMOVING COMMON ELEMENTS & ADDING DIFFERENT ONES...
    int symmetric_difference(object* begin2){
        if(begin2==begin){
            end=NULL;
            begin=NULL;
            size=0;
            return size;
        }
        object* start2=begin2;
        object* start1=begin;
        if(size==0){
            if(start2!=NULL){
                object* add=new object(start2->data);
                begin=add;
                end=add;
                size++;
                start2=start2->next;
                start1=begin;
            }
        }
        while(start2!=NULL){
            if(start1==NULL){
                    while(start2!=NULL){
                        object* add=new object(start2->data);
                        end->next= add;
                        add->prev=end;
                        end=add;
                        size++;
                        start2=start2->next;
                    }
                    return size;
            }
            if(start1->data<start2->data){
                start1=start1->next;
                continue;
            }
            else if(start1->data>start2->data){
                object* add=new object(start2->data);
                if(start1==begin){
                    begin=add;
                    add->next=start1;
                    start1->prev=add;
                    size++;
                    start2=start2->next;
                    continue;
                }
                start1->prev->next=add;
                add->prev=start1->prev;
                start1->prev=add;
                add->next=start1;
                start2=start2->next;
                size++;
                continue;
            }
            else{
                if(start1==begin){
                    if(start1==end){
                        begin=NULL;
                        end=NULL;
                        size--;
                        start2=start2->next;
                        if(start2!=NULL){
                            Insert(start2->data);
                            start2=start2->next;
                        }
                        start1=begin;
                        
                        while(start2!=NULL){
                            object* add= new object(start2->data);
                            start1->next=add;
                            add->prev=start1;
                            start1=start1->next;
                            size++;
                        }
                        end=start1;
                        return size;
                    }
                    begin=start1->next;
                    begin->prev=NULL;
                    delete start1;
                    start1=begin;
                    size--;
                    start2=start2->next;
                    continue;
                }
                else if(start1==end){
                    end=start1->prev;
                    end->next=NULL;
                    size--;
                    start1=end;
                    start2=start2->next;
                    while(start2!=NULL){
                        object* add=new object(start2->data);
                        start1->next=add;
                        add->prev=start1;
                        start1=start1->next;
                        start2=start2->next;
                        size++;
                    }
                    end=start1;
                    return size;
                }
                else{
                    start1->prev->next=start1->next;
                    start1->next->prev=start1->prev;
                    size--;
                    
                    start1=start1->next;
                    start2=start2->next;
                }
            }
        }
        return size;
    }
    //PRINTING THE SET ELEMENTS
    void print(){
        if(size!=0){
            object* start= begin;
            while(start!=end){
                cout<<start->data<<",";
                start=start->next;
            }
            cout<<end->data;
        }
        cout<<endl;
    }
};

int main() {
	// your code goes here
	SET* arr[100001];
	int command,set_num,num;
	while(cin>>command){
	    cin>>set_num;
	    if(command<=9 && command>0 && set_num>=0){
	        if(command!=6 && command!=9){
	            cin>>num;
	        }
	        // COMMANDS...
		if(command==1){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            cout<<(arr[set_num])->Insert(num)<<endl;
	            continue;
	        }
	        if(command==2){
	            if(arr[set_num]==NULL){
	                cout<<-1<<endl;
	                continue;
	            }
	            cout<<(arr[set_num])->Delete(num)<<endl;
	            continue;
	        }
	        if(command==3){
	            if(arr[set_num]==NULL){
	                cout<<-1<<endl;
	                continue;
	            }
	            cout<<arr[set_num]->Belongs(num)<<endl;
	            continue;
	        }
	        if(command==4){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            if(num!=set_num){
    	            if(arr[num]==NULL){
    	                arr[num]=new SET;
    	            }
	                cout<<arr[set_num]->Union(arr[num]->begin)<<endl;
	                continue;
	            }
	            cout<<arr[set_num]->size<<endl;
	            continue;
	        }
	        if(command==5){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            if(num!=set_num){
    	            if(arr[num]==NULL){
    	                arr[num]=new SET;
    	            }
	                cout<<arr[set_num]->Intersection(arr[num]->begin)<<endl;
	                continue;
	            }
	            cout<<arr[set_num]->size<<endl;
	            continue;
	        }
	        if(command==6){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            cout<<arr[set_num]->size<<endl;
	            continue;
	        }
	        if(command==7){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            if(arr[num]==NULL){
	                arr[num]=new SET;
	                cout<<arr[set_num]->size<<endl;
	                continue;
	            }
	            cout<<arr[set_num]->difference(arr[num]->begin)<<endl;
	            continue;
	        }
	        if(command==8){
	            if(arr[set_num]==NULL){
	                arr[set_num]=new SET;
	            }
	            if(arr[num]==NULL){
	                arr[num]=new SET;
	                cout<<arr[set_num]->size<<endl;
	                continue;
	            }
	            cout<<arr[set_num]->symmetric_difference(arr[num]->begin)<<endl;
	            continue;
	        }
	        if(command==9){
	            if(arr[set_num]!=NULL){
	                arr[set_num]->print();
	                continue;
	            }
	            cout<<endl;
	            continue;
	        }
	    }
	}
	
	return 0;
}