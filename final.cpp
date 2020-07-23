#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 10
typedef struct node {
    string data;
    struct node *next;
}ht_prototype;


typedef struct Node{
    string setname;
    ht_prototype h_t[MAX];
}set_collection;

/* For a given string, computes its hash value.
   Unique value for every string */
ll find_hash_value(const string &s){

    const int p = 31;
    const int m = 1e9+9;
    ll h_val = 0;
    ll p_pow = 1;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        h_val = (h_val + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return h_val;
}

/* Initialises the entire hash table with starting value of -1 for each string */
void init(ht_prototype h_t[]){

    cout <<"comes inside init func" << endl;
    for(int i=0;i<MAX;i++){
        h_t[i].data="";
        h_t[i].next = NULL;
    }

}

void initset(set_collection sets[]){
    for(int i=0;i<100;i++){
        sets[i].setname = "-1";
    }
}

/*1.Computes the hash value of string using find_hash_value function
  2.Checks if for given h_val index if there is any node:- a.If no node then creates one
                                                           b.If chaining found then searches in chain for string val:-
                                                                                                                      if found then terminates
                                                                                                                      else creates new node at then end */

void insert(string s,ht_prototype h_t[]){


        ll h_val = find_hash_value(s);
        h_val%=MAX;

        if(h_t[h_val].data==""){ //if no string attached for given h_val yet
            h_t[h_val].data = s;
            cout <<"Element inserted\n";
            return;
        }


        ht_prototype *ptr = &h_t[h_val]; //ptr pointing to first node of chain of h_t[h_val]
        bool flag = false;

        while(ptr->next!=NULL && !flag){
            if(ptr->data==s){
                flag = true;
            }
            ptr=ptr->next;
        }

        if(ptr->data==s){
            flag = true;
        }

        if(flag){
            cout <<"Already exists\n";
        }
        else
        {
            ht_prototype *nptr;
            nptr = (ht_prototype*)malloc(sizeof(ht_prototype));
            nptr->data= s;
            nptr->next=NULL;
            ptr->next=nptr;
            cout <<"Element inserted\n";
        }

}


/*Computes h_val for given string first
    If h_val index of h_t is uninitialised then returns false
    Else checks in chain for occurrence of s and returns true if found or false if not */

bool is_element_of(string s, ht_prototype *h_t){

    ll h_val = find_hash_value(s);
    h_val%=MAX;

     if(h_t[h_val].data=="-1"){ //if no string attached for given h_val yet
           return false;
        }

    ht_prototype *ptr = &h_t[h_val];

    while(ptr){
            if(ptr->data==s){ //if found
                return true;
            }
            ptr=ptr->next;
    }
    return false; //after going through chain if still not found
}

bool is_empty(ht_prototype *h_t){

    for(int i=0;i<MAX;i++){
        if(h_t[i].data!="-1") //not empty
            return false;

    }
    return true; //if after traversing all h_val indices no node found means empty
}


/* Goes through every index of hash table.
        If no node found, then continue
        If node found, then traverses the chain and adds to size the number of nodes in that chain */
ll siz(ht_prototype *h_t){

    ll siz=0;

    for(int i=0;i<MAX;i++){
        if(h_t[i].data==""){
            continue;
        }
        else
        {
            ht_prototype *ptr = &h_t[i];
            while(ptr!=NULL){
                siz++;
                ptr=ptr->next;
            }
        }
    }

    return siz;
}

/* Goes through hash_table and prints every node as and when they appear*/

void enumerate(ht_prototype *h_t){

    for(int i=0;i<MAX;i++){
        if(h_t[i].data=="-1"){
            cout <<"Func(" << i << ") --> ";
            continue;
        }

        else
        {
            ht_prototype *ptr = &h_t[i];
            cout <<"Func(" << i << ") --> ";
            while(ptr!=NULL){
               cout << ptr->data << " ";
                ptr=ptr->next;
            }
            cout << endl;
        }
    }
}



void build(string arr[],int n, ht_prototype *h_t){

    for(int i=0;i<n;i++){
        insert(arr[i], h_t);
    }
}

void create(ht_prototype h_t[]){
    cout <<"comes inside create func\n";
    init(h_t);
    cout <<"New set successfully created \n";
}


void add(string s, ht_prototype *h_t){
    insert(s,h_t);
}

void remov(string s , ht_prototype *h_t){

    ll h_val = find_hash_value(s);
    h_val%=MAX;

    ht_prototype *pre;
    ht_prototype *ptr;

    pre = NULL;
    ptr = &h_t[h_val];

    if(ptr->data ==s){ //if first node is the string
        ht_prototype *nptr = ptr->next;
        if(nptr==NULL) {//so only one node in this chain
                ptr->data = "-1";
        }
        else //if first is to be deleted and we've second node onwards to make second as first and delete first by freeing
        {
            nptr=&h_t[h_val];
            free(ptr);
        }
    }
    else
    {
        bool flag= false;
        pre = ptr;
        ptr=ptr->next;
        while(ptr!=NULL && !flag){

            if(ptr->data==s){
                flag = true;
                if(ptr->next==NULL){
                    pre->next=NULL;
                    free(ptr);
                }
                else
                {
                    pre->next = ptr->next;
                    ptr->next=NULL;
                    free(ptr);
                }
            }

            pre=ptr;
            ptr=ptr->next;
        }

        if(!flag){
            cout <<"Does not exist\n";
        }
    }
}


void un(ht_prototype *s, ht_prototype *t, ht_prototype *ans){
        cout <<"Comes inside union func\n";
        for(int i=0;i<MAX;i++){

            if(s[i].data!=""){
                ht_prototype *ptr = &s[i];
                while(ptr!=NULL){
                    insert(ptr->data,ans);
                    ptr=ptr->next;
                }
            }
            if(t[i].data!=""){
                 ht_prototype *ptr = &t[i];
                while(ptr!=NULL){
                    insert(ptr->data,ans);
                    ptr=ptr->next;
                }
            }
        }
}


void intersection(ht_prototype *s, ht_prototype *t, ht_prototype ans[]){

    for(int i=0;i<MAX;i++){
        if(s[i].data=="" && t[i].data==""){
            continue;
        }

        ht_prototype *ptr;
        ptr = &s[i];
        while(ptr!=NULL){
            if(is_element_of(ptr->data,t)){
                insert(ptr->data,ans);
            }
            ptr=ptr->next;
        }
    }
}

/*Set of all elements of S that are not elements of T */
void difference(ht_prototype *s, ht_prototype *t, ht_prototype *ans){

            for(int i=0;i<MAX;i++){
                if(s[i].data==""){
                    continue;
                }

                ht_prototype *ptr = &s[i];

                while(ptr){
                    if( !is_element_of(ptr->data,t) ){ //if an element in S is not present in T then insert
                        insert(ptr->data,ans);
                    }
                    ptr=ptr->next;
                }
            }
}


bool subset(ht_prototype *s, ht_prototype *t){

    for(int i=0;i<MAX;i++){
        if(s[i].data==""){
            continue;
        }

        ht_prototype *ptr = &s[i];

        while(ptr){
            if( !(is_element_of(ptr->data,t)) ){ //if element of S not found in T then return false
                return false;
            }
            ptr= ptr->next;
        }
    }
    return true; // when all elements of S are found in T
}



int main()
{
    cout <<"//////// Implementation of Set using Hash Table //////////////// \n";
    int choice=0;
    set_collection sets[100];


    while(choice!=-1){
        cout <<"Enter from following choices\n";
        cout <<"1.To create a new empty set\n";
        cout <<"2.To insert elements in set\n";
        cout <<"3.To build a set\n";
        cout <<"4.To remove elements in set\n";
        cout <<"5.To print elements of set\n";
        cout <<"6.To print size of set\n";
        cout <<"7.To find union of two sets\n";
        cout <<"8.To find intersection of two sets\n";
        cout <<"9.To find difference of two sets\n";
        cout <<"10.To find if one is subset of another\n";

        cin >> choice;
        cout <<"choice is "  << choice << endl;
        string s; string t; int i=0; bool flag; int indexs=-1,indext=-1;
        switch(choice){
            case 1: cout <<"Enter name of new set\n";
                    cin >> s;
                     i=0;
                    for(;i<100;i++){
                        if(sets[i].setname=="") break;
                    }

                    sets[i].setname =s;
                    create(sets[i].h_t);
                    cout <<"New set created with name " << s << endl;
                    break;

            case 2: cout <<"Enter set name where you want to insert new elements\n";
                    cout <<"comes inside case 2\n";
                    cin >> s;
                     i=0;
                     flag=false;
                    for(;i<100;i++){
                        if(sets[i].setname==s) { flag = true; break;}
                    }

                    if(flag){

                        string str;
                        cout <<"Enter the new string name to be inserted\n";
                        cin >> str;
                        insert(str,sets[i].h_t);
                    }
                    else
                    {
                        cout <<"No set found with given name\n";
                    }

                    break;

            case 3:  cout <<"Enter set name where you want to insert new elements\n";
                    cin >> s;
                    i=0;
                     flag=false;
                    for(;i<100;i++){
                        if(sets[i].setname==s) { flag = true; break;}
                    }
                    if(flag){
                        int num;
                        cout <<"Enter how many elements you wish to put in set\n";
                        cin >> num;
                        string str[num];
                        cout <<"Enter the elements one by one\n";
                        for(int i=0;i<num;i++){
                            cin >> str[i];
                        }

                        build(str,num,sets[i].h_t);
                    }
                    else{
                         cout <<"No set found with given name\n";
                    }

                    break;

              case 4: cout <<"Enter set name where you want to remove  elements\n";
                    cin >> s;
                     i=0;
                     flag=false;
                    for(;i<100;i++){
                        if(sets[i].setname==s) { flag = true; break;}
                    }

                    if(flag){
                        string str;
                        cout <<"Enter the element name to be removed\n";
                        cin >> str;
                        remov(str,sets[i].h_t);
                    }
                    else
                    {
                        cout <<"No set found with given name\n";
                    }

                    break;

            case 5: cout <<"Enter set name which you want to print\n";
                    cin >> s;
                     i=0;
                     flag=false;
                    for(;i<100;i++){
                        if(sets[i].setname==s) { flag = true; break;}
                    }
                    if(flag){
                        enumerate(sets[i].h_t);
                    }
                    else
                    {
                        cout <<"No set found with given name";
                    }

                    break;

            case 6: cout <<"Enter set name whose size you want\n";
                    cin >> s;
                     i=0;
                     flag=false;
                    for(;i<100;i++){
                        if(sets[i].setname==s) { flag = true; break;}
                    }
                    if(flag){
                        cout << "Size is " << siz(sets[i].h_t) << endl;
                    }
                    else
                    {
                        cout <<"No set found with given name";
                    }

                    break;

            case 7: cout <<"Enter 1st set name\n"; cin >> s;
                    cout <<"Enter 2nd set name\n"; cin >> t;
                    indexs=-1,indext=-1;
                    for(int i=0;i<100;i++){
                        if(sets[i].setname==s){
                            indexs=i;
                        }
                        if(sets[i].setname==t){
                            indext=i;
                        }

                        if(indexs!=-1 && indext!=-1) break;
                    }

                    if(indexs==-1 && indext==-1){
                        cout <<"Both sets not found\n";
                    }
                    else if(indexs==-1 && indext!=-1){
                        cout <<"First setname not found\n";
                    }
                    else if(indext==-1 && indexs!=-1){
                        cout <<"Second set name not found\n";
                    }
                    else //when both sets are found
                    {
                        ht_prototype ans[MAX];
                        //create new set to store ans
                        init(ans);

                        un(sets[indexs].h_t,sets[indext].h_t,ans);
                        cout <<"Union has been completed\n";
                        cout <<"Printing union set\n";
                        enumerate(ans);
                    }

                    break;
            case 8: cout <<"Enter 1st set name\n"; cin >> s;
                    cout <<"Enter 2nd set name\n"; cin >> t;
                     indexs=-1,indext=-1;
                    for(int i=0;i<100;i++){
                        if(sets[i].setname==s){
                            indexs=i;
                        }
                        if(sets[i].setname==t){
                            indext=i;
                        }

                        if(indexs!=-1 && indext!=-1) break;
                    }

                    if(indexs==-1 && indext==-1){
                        cout <<"Both sets not found\n";
                    }
                    else if(indexs==-1 && indext!=-1){
                        cout <<"First setname not found\n";
                    }
                    else if(indext==-1 && indexs!=-1){
                        cout <<"Second set name not found\n";
                    }
                    else //when both sets are found
                    {
                        ht_prototype ans[MAX];
                        //create new set to store ans
                        init(ans);
                        intersection(sets[indexs].h_t,sets[indext].h_t,ans);
                         cout <<"Intersection has been completed\n";
                        cout <<"Printing intersection set\n";
                        enumerate(ans);
                    }
                    break;
            case 9: cout <<"Enter 1st set name\n"; cin >> s;
                    cout <<"Enter 2nd set name\n"; cin >> t;
                     indexs=-1,indext=-1;
                    for(int i=0;i<100;i++){
                        if(sets[i].setname==s){
                            indexs=i;
                        }
                        if(sets[i].setname==t){
                            indext=i;
                        }

                        if(indexs!=-1 && indext!=-1) break;
                    }

                    if(indexs==-1 && indext==-1){
                        cout <<"Both sets not found\n";
                    }
                    else if(indexs==-1 && indext!=-1){
                        cout <<"First setname not found\n";
                    }
                    else if(indext==-1 && indexs!=-1){
                        cout <<"Second set name not found\n";
                    }
                    else //when both sets are found
                    {
                        ht_prototype ans[MAX];
                        //create new set to store ans
                        init(ans);
                        difference(sets[indexs].h_t,sets[indext].h_t,ans);
                         cout <<"Difference has been completed\n";
                        cout <<"Printing difference set\n";
                        enumerate(ans);
                    }
                    break;
            case 10:cout <<"Enter 1st set name\n"; cin >> s;
                    cout <<"Enter 2nd set name\n"; cin >> t;
                     indexs=-1,indext=-1;
                    for(int i=0;i<100;i++){
                        if(sets[i].setname==s){
                            indexs=i;
                        }
                        if(sets[i].setname==t){
                            indext=i;
                        }

                        if(indexs!=-1 && indext!=-1) break;
                    }

                    if(indexs==-1 && indext==-1){
                        cout <<"Both sets not found\n";
                    }
                    else if(indexs==-1 && indext!=-1){
                        cout <<"First setname not found\n";
                    }
                    else if(indext==-1 && indexs!=-1){
                        cout <<"Second set name not found\n";
                    }
                    else //when both sets are found
                    {
                        ht_prototype ans[MAX];
                        //create new set to store ans
                        init(ans);
                        if(subset(sets[indexs].h_t,sets[indext].h_t)){
                            cout << s <<"is a subset of " << t << endl;
                        }
                        else
                        {
                            cout << s << "is not a subset of " << t << endl;
                        }
                    }
                    break;
        }
    }
}


