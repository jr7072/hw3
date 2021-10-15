#include "LinkedList.h"

LinkedList::LinkedList(){

    head = tail = nullptr;
    size = 0;
}

LinkedList::~LinkedList(){

    ListNode* iter = head;
    ListNode* temp;

    while(iter != nullptr){

        temp = iter -> next;

        delete iter;

        iter = temp;
        
    }

}

void LinkedList::print(ListNode* iter){

    if(iter == nullptr){
        return;
    }
    
    cout << iter -> item << endl;
    print(iter -> next);
    
}

void LinkedList::addToBeginning(string input){
    
    ListNode* tmp;

    tmp = new ListNode;
    tmp -> item = input;

    if(head == nullptr){
        head = tail = tmp;
        size++;
        return;
    }

    tmp -> next = head;
    head -> prev = tmp;
    head = tmp;

    size++;

}

string LinkedList::values(){

    string values = "";
    ListNode* iter = head;


    for(int i = 0; i < size; ++i){

        values += iter -> item + " ";
        iter = iter -> next;
    }

    if(size == 0){
        return " ";
    }

    return values;
}

void LinkedList::addToEnd(string input){

    ListNode* tmp;

    tmp = new ListNode;

    tmp -> item = input;

    if(head == nullptr){

        head = tail = tmp;
        size++;
        return;
    }

    tail -> next = tmp;
    tmp -> prev = tail;
    tail = tmp;
    size++;
}

void LinkedList::insertAtPos(string input, int pos){

    if(pos == 0){
        this -> addToBeginning(input);
        return;
    }

    if(head == nullptr){
        return;
    }

    if(pos > size){

        return;
    }

    if (pos == size){

        this -> addToEnd(input);
        return;
    }


    ListNode* tmp;

    tmp = new ListNode;

    tmp -> item = input;

    ListNode* iter = head;
    ListNode* nu = iter -> next;

    for(int i = 0; i < pos - 1; ++i){

        iter = iter -> next;
        nu = nu -> next;
    }

    iter -> next = tmp;
    tmp -> prev = iter;
    tmp -> next = nu;
    size++;
}

void LinkedList::remove(string parser){
    
    if(head == nullptr || parser == ""){

        return;
    }

    bool remove = false;
    ListNode* temp = head;

    if(size == 1){
        
        remove = this -> parse(head -> item, parser);
        if(remove){

            temp = head;
            delete temp;
            head = tail = nullptr;
            size--;
        }

        return;
    }

    ListNode* nu;
    ListNode* pu;

    while(temp != nullptr){

        remove = this -> parse(temp -> item, parser);

        if(remove){
            if(size == 1){
                delete temp;
                head = tail = nullptr;
                size--;
                break;
            }
            else if(temp -> prev == nullptr){

                nu = temp -> next;

                delete nu -> prev;
                nu -> prev = nullptr;
                head = nu;
                temp = nu;
                size--;
                continue;
            }
            else if(temp -> next == nullptr){

                pu = temp -> prev;
                delete pu -> next;
                pu -> next = nullptr;
                tail = pu;
                temp = nullptr;
                size--;
                continue;
            }else{

                nu = temp -> next;
                pu = temp -> prev;
                delete pu -> next;
                pu -> next = nu;
                nu -> prev = pu;
                temp = nu;
                size--;
                continue;
            }
        }

        temp = temp -> next;
    }
  
}      
       

bool LinkedList::parse(string node, string parser){

    bool checker = false;
    int iterations = node.length() - parser.length();
    string slider;
    
    if(iterations < 0){
        
        return false;
    }

    for(int i = 0; i <= iterations; ++i){

        slider = node.substr(i, parser.length());

        if(parser == slider){

            checker = true;
            break;
        }
    }

    return checker;
}

ListNode* LinkedList::sortLength(ListNode* headNode){

    if(headNode == nullptr || headNode -> next == nullptr){
        return headNode;
    }


    ListNode* b = split(headNode);

    headNode = sortLength(headNode);
    b = sortLength(b);

    return sortedMerge(headNode, b, "Length");
}

ListNode* LinkedList::sortAlpha(ListNode* headNode){

    if(headNode == nullptr || headNode -> next == nullptr){
        return headNode;
    }

    ListNode* b = split(headNode);

    headNode = sortAlpha(headNode);
    b = sortAlpha(b);

    return sortedMerge(headNode, b, "Alphabetically");

}

ListNode* LinkedList::split(ListNode* headNode){

    ListNode* fast;
    ListNode* slow;

    slow = headNode;
    fast = headNode -> next;

    while(fast != nullptr){

        fast = fast -> next;

        if(fast != nullptr){

            slow = slow -> next;
            fast = fast -> next;
        }
    }

    ListNode* splited = slow -> next;
    slow -> next = nullptr;

    return splited;

}

ListNode* LinkedList::setTail(ListNode* iter){

    if(iter == nullptr){

        return nullptr;
    }

    if(iter -> next == nullptr){

        return iter;
    }

    return setTail(iter -> next);

}

ListNode* LinkedList::sortedMerge(ListNode* a, ListNode* b, string type){

    if(a == nullptr){
        return b;
    }

    if(b == nullptr){
        return a;
    }

    if(type == "Alphabetically"){

        if(a -> item <= b -> item){

            a -> next = sortedMerge(a -> next, b, type);
            tail = a -> next;
            a -> next -> prev = a;
            a -> prev = nullptr;
            return a;
            
        }else{

            b -> next = sortedMerge(a, b -> next, type);
            tail = b -> next;
            b -> next -> prev = b;
            b -> prev = nullptr;
            return b;
        }

    }else if(type == "Length"){

        if(a -> item.length() <= b -> item.length()){

            a -> next = sortedMerge(a -> next, b, type);
            a -> next -> prev = a;
            a -> prev = nullptr;
            return a;
            
        }else{

            b -> next = sortedMerge(a, b -> next, type);
            b -> next -> prev = b;
            b -> prev = nullptr;
            return b;
        }
    }

}

void LinkedList::sort(string type){


    if (type == "Alphabetically"){

        head = this -> sortAlpha(head);
        tail = this -> setTail(head);

    }else if(type == "Length"){

        head = this -> sortLength(head);
        tail = this -> setTail(head);

    }else{

        cout << "invalid input" << endl;
    }
    
}

void LinkedList::removeDoublies(){

    if(head == nullptr){
        return;
    }

    if(size == 1){
        return;
    }

    ListNode* comparer = head;
    ListNode* iter = head -> next;
    ListNode* pu;
    ListNode* nu;

    while(comparer -> next -> next != nullptr){

        while(iter != nullptr ){

            if(comparer -> item == iter -> item){

                if(iter -> next == nullptr){
                    pu = iter -> prev;
                    delete pu -> next;
                    tail = pu;
                    size--;
                    continue;
                }else{
                    nu = iter -> next;
                    pu = iter -> prev;
                    delete pu -> next;
                    pu -> next = nu;
                    nu -> prev = pu;
                    iter = nu;
                    size--;
                    continue;
                }
            }

            iter = iter -> next;
        }
        
        comparer = comparer -> next;
        iter = comparer -> next;
    }


}

void LinkedList::writeToFile(ofstream& ofs, ListNode* iter){

    if(iter == nullptr){
        return;
    }

    ofs << iter -> item << endl;
    writeToFile(ofs, iter -> next);
}

int LinkedList::getSize(){
    
    return size;
}

LinkedList& LinkedList::operator=(const LinkedList& left){

    this -> head = left.head;
    this -> tail = left.tail;
    this -> size = left.size;

    return *this;
}

ListNode* LinkedList::getHead(){

    return head;
}

ListNode* LinkedList::getTail(){

    return tail;
}