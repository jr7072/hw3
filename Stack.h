#ifndef STACK_H 
#define STACK_H 
#include <iostream>
#include "LinkedList.h"
using namespace std;

template <class T, class L>
class Stack{

    private:

        T* top;
        T* bottom;
        int size;

    public:

        Stack();
        void push(T*);
        T* pop();
        int getSize();
        bool isEmpty();
        void printSize();
        void popReserve(L&, int);
        void flipReserve();
        void convertReserve(string, void(*)(), T*);
        void printTop();
        void emptyReserve(L&, int);
        void write(ofstream&, T*);

};

template <class T, class L>
Stack<T, L>::Stack(){

    top=bottom=nullptr;
    size = 0;

}

template <class T, class L>
int Stack<T, L>::getSize(){

    return size;
}

template <class T, class L>
bool Stack<T, L>::isEmpty(){

    bool empty = false
    if(top == nullptr){

        empty = true;
    }

    return empty;
}

template <class T, class L>
void Stack<T, L>::push(T* listNode){
    
    if(isEmpty()){

        top=bottom=listNode;
        size++;
    }

    listNode -> next = top;
    top = listNode;
    size++;
}

template <class T, class L>
T* Stack<T, L>::pop(){

    if(isEmpty()){
        return;
    }

    T* tmp = top;
    top = tmp -> next;
    size--;
    return tmp;
}

template <class T, class L>
void Stack<T, L>::printSize(){

    cout << size << endl;
}

template <class T, class L>
void Stack<T, L>::popReserve(L& List, int pos){//void until linked list is done. 

    if(isEmpty()){
        return;
    }

    T* popped = this -> pop();

    List.splice(popped); 
}

template <class T, class L>

void Stack<T, L>::flipReserve(){

    if (this -> isEmpty()){

        return;
    }

    if (top -> next == nullptr){

        return;
    }

    T* curr = top;
    T* prev = nullptr;

    while(curr != nullptr){

        T* tmp = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = tmp;

    }

    top = prev;
}

template <class T, class L>

void Stack<T, L>::convertReserve(string action, void(*converter)(), T* topRef){

    if(topRef == nullptr){

        break;
    }

    string typeRef = topRef -> type;
    topRef -> equation = converter(topRef, typeRef);

    typeRef == "postfix" ? typeRef = "prefix" : NULL;

    this -> convertReverse(action, converter, topRef -> next);

}

template <class T, class L>

void Stack<T, L>::printTop(){

    cout << "k" << endl;
    
}

template <class T, class L>

void Stack<T, L>::emptyReserve(L& list, int pos){//void until LinkedList is done

    list.splice(top, pos);

}

template <class T, class L>

void Stack<T, L>::write(ofstream& ofs, T* topRef){//works only for one template type

    if(topRef == nullptr){
        return;
    }

    ofs << topRef -> equation << endl;
    this -> write(ofs, top -> next);
}
#endif