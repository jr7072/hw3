#ifndef STACK_H 
#define STACK_H 
#include <iostream>
using namespace std;

template <class T, class L>
class Stack{

    private:

        T* top;
        T* bottom;
        int size;

    public:

        Stack();
        void push(T*);//done
        T* pop();//done
        T* getTop();//done
        void printChar();
        void setBottom(T*);//???
        int getSize();//done
        bool isEmpty();//done
        void printSize();//done
        void popReserve(L&, int);//done
        void flipReserve();//done
        void convertReserve(void(*)(T*, string));//done
        void printTop();//done
        void emptyReserve(L&, int);//done
        void write(ofstream&, T*);//done
        void print(T*);

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

    bool empty = false;
    if(top == nullptr){

        empty = true;
    }

    return empty;
}

template <class T, class L>
void Stack<T, L>::push(T* newNode){

    T* tmp = newNode;
    
    if(isEmpty()){

        top=bottom=tmp;
        size++;
        return;
    }

    tmp -> next = top;
    top = tmp;
    size++;
}

template <class T, class L>
T* Stack<T, L>::pop(){

    if(isEmpty()){
        return nullptr;
    }

    T* tmp = top;
    top = tmp -> next;
    tmp -> next = nullptr;
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
    List.setHead(List.splice(List.getHead(), popped, pos)); 
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

void Stack<T, L>::convertReserve(void(*converter)(T* node, string type)){

    if(top == nullptr){

        return;
    }

    string action = top -> type;
    string payload;

    action == "prefix" ? payload = "postfix" : payload = "prefix";

    converter(top, payload);    
}

template <class T, class L>

void Stack<T, L>::printTop(){

    cout << top -> type << ":" << top -> equation << endl;
    
}

template <class T, class L>
void Stack<T, L>::printChar(){
    cout << top -> data << endl;
}

template <class T, class L>

void Stack<T, L>::emptyReserve(L& list, int pos){//void until LinkedList is done

    while(!isEmpty()){

        T* popped = this -> pop();
        list.setHead(list.splice(list.getHead(), popped, pos));
    }
}

template <class T, class L>

void Stack<T, L>::write(ofstream& ofs, T* topRef){//works only for one template type

    if(topRef == nullptr){
        return;
    }

    ofs << topRef -> equation << endl;
    this -> write(ofs, top -> next);
}
template <class T, class L>

T* Stack<T, L>::getTop(){
    
    return top;
}

template <class T, class L>

void Stack<T, L>::setBottom(T* newTail){

    bottom = newTail;
}

template <class T, class L>

void Stack<T, L>::print(T* topRef){

    if(topRef == nullptr){
        return;
    }

    cout << topRef -> data << endl;
    print(topRef -> next);
}
#endif