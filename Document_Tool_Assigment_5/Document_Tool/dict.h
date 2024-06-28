// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Node{
        public:
        string val;
        int bc;
        int pg;
        int para;
        int sno;
        Node* left;
        Node* right;
        int wcount;
        Node(){
            val="";
            left=NULL;
            right=NULL;
        }
        Node(int book_code, int page, int paragraph, int sentence_no, string str,int c=1){
            bc=book_code;
            pg=page;
            para=paragraph;
            sno=sentence_no;
            val=str;
            wcount=c;
            left=NULL;
            right=NULL;
        }
        Node(Node* n){
            bc=n->bc;
            pg=n->pg;
            para=n->para;
            sno=n->sno;
            val=n->val;
            wcount=n->wcount;
            left=NULL;
            right=NULL;
        }
    };

class Dict {
private:
    

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    void print();
    int count;
    int size;
    int checkk;
    Node** elements;
    vector<int> products;
    Node* insert(string s,int a,int b,int c,int d,Node* curr);
    int hashfunc(string s);
    void resize();
    Node* ins(Node** v,Node* curr,Node* c);
    void helper(Node** v,Node* curr,int& i); 
    //  
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};