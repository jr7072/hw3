#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <fstream>
#include "Stack.h"
#include <fstream>
using namespace std;

struct ListNode{

    string equation;
    string type;
    ListNode* next;
    ListNode* prev;

    ListNode(){
        
        next = prev = nullptr;
    }
};

class LinkedList{
    
    private:

        ListNode* head;
        ListNode* tail;
        int size;

    public:
        //constuctors, getters, and destructors
        LinkedList();
        ~LinkedList();
        LinkedList& operator=(const LinkedList&);
        ListNode* getHead();
        void setHead(ListNode*);
        ListNode* getTail();
        bool isEmpty();
        int getSize();
        void print(ListNode*, ofstream&, bool start = true);
        void printBack(ListNode*, ofstream&, bool start = true);

        //functions mentioned in pdf
        //add at beginning
        void addToBeginning(string);
        string values();
        //add at end
        void addToEnd(string, string);
        //insert at position 
        void insertAtPos(string, int);
        //remove by pointer
        void remove(string);
        //remove helper function
        bool parse(string, string);
        //sort by length and alphabet;
        ListNode* sortLength(ListNode*);
        ListNode* sortAlpha(ListNode*);
        //sort helper functions
        ListNode* split(ListNode*);
        ListNode* sortedMerge(ListNode*, ListNode*, string);
        ListNode* setTail(ListNode*);
        //sort executer
        void sort(string);
        //duplicate muncher
        void removeDoublies();

        //write to file
        void writeToFile(ofstream&, ListNode*);

        //new functions

        void convertList(void(*)(ListNode*, string), ListNode*, string action="null", int pos=-1000, int iter=1);//callback functionrecursive theoretical afffffffff
        ListNode* removeList(ListNode*, string action="null", int pos=-1000, int iter=1);//recursive
        ListNode* splice(ListNode*, ListNode*, int pos, bool start = false,int iter=1);//recursive
        ListNode* deletePush(ListNode*, Stack<ListNode, LinkedList>&, string action="null", int pos=-1000, int iter=1);
};

#endif