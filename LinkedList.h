#ifndef LinkedList_H
#define LinkedList_H

#include <iostream>
#include <fstream>
#include "Stack.h"
using namespace std;

struct ListNode{

    string item;
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
        ListNode* getTail();
        int getSize();
        void print(ListNode*);
        void printBack(ListNode*);

        //functions mentioned in pdf
        //add at beginning
        void addToBeginning(string);
        string values();
        //add at end
        void addToEnd(string);
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

        void convertList();
        void removeList();
        void splice();
        void pushReserve(Stack<ListNode, LinkedList>&);
};

#endif