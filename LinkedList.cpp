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

bool LinkedList::isEmpty(){

    if(head == nullptr){

        return true;
    }

    return false;
}

void LinkedList::print(ListNode* iter, ofstream& ofs, bool start){

    if(iter == nullptr){
        if(start){

            ofs << "EMPTY" << endl;
        
        }

        return;
    }
    
    start = false;
    ofs << iter -> type << ":" << iter -> equation << endl;
    print(iter -> next, ofs, start);
    
}

void LinkedList::printBack(ListNode* topRef, ofstream& ofs, bool start){

    if(topRef == nullptr){
        
        if(start){
            
            ofs << "EMPTY" << endl;
        
        }

        return;
    }

    start = false;
    printBack(topRef -> next, ofs, start);
    ofs << topRef -> type << ":" << topRef -> equation << endl;
}

void LinkedList::addToBeginning(string input){
    
    ListNode* tmp;

    tmp = new ListNode;
    tmp -> equation  = input;

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

        values += iter -> equation  + " ";
        iter = iter -> next;
    }

    if(size == 0){
        return " ";
    }

    return values;
}

void LinkedList::addToEnd(string equation, string type){

    ListNode* tmp;

    tmp = new ListNode;

    tmp -> equation  = equation;
    tmp -> type = type;

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

        this -> addToEnd(input, "");
        return;
    }


    ListNode* tmp;

    tmp = new ListNode;

    tmp -> equation  = input;

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
        
        remove = this -> parse(head -> equation , parser);
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

        remove = this -> parse(temp -> equation , parser);

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

        if(a -> equation  <= b -> equation ){

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

        if(a -> equation .length() <= b -> equation .length()){

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

            if(comparer -> equation  == iter -> equation ){

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

    ofs << iter -> equation  << endl;
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

void LinkedList::setHead(ListNode* newHead){

    head = newHead;
}

ListNode* LinkedList::getTail(){

    return tail;
}

//new functions!!!!!!!!!!

void LinkedList::convertList(void(*converter)(ListNode*, string), ListNode* headRef, string action, int pos, int iter){

    if(headRef == nullptr){ //done
        return;
    }

    if(headRef -> type == action || action == "all" || iter == pos || ((pos <= 0) && (iter == 1))){

        string convert;
        headRef -> type == "prefix" ? convert = "postfix" : convert = "prefix";
        converter(headRef, convert);
        
    }
    
    convertList(converter, headRef -> next, action, pos, ++iter);
    
}

ListNode* LinkedList::removeList(ListNode* headRef, string action, int pos, int iter){ // neeeds to be tailfied
    
    if(headRef == nullptr){
        return headRef;
    }

    else if(headRef -> type == action || action == "all" || iter == pos){
        size--;
        return removeList(headRef -> next, action, pos, ++iter);
    }

    else {

        headRef -> next = removeList(headRef -> next, action, pos, ++iter);
        headRef -> next -> prev = headRef;
        headRef -> prev = nullptr;
        return headRef;
    }
}

ListNode* LinkedList::splice(ListNode* base, ListNode* b, int pos, bool start, int iter){

    if (base == nullptr){

        return b;
    }

    if (b == nullptr){

        return base;
    }

    if(iter == pos || (pos <= 0 && iter == 1) || pos > size){

        start = true;
    }
    
    if(start){

        if(iter == pos || pos > size){

            base -> next = splice(base -> next, b, pos, start, ++iter);
            base -> next -> prev = base;
            base -> prev = nullptr;
            return base;

        }else{

            b -> next = splice(base, b -> next, pos, start, ++iter);
            b -> next -> prev = b;
            b -> prev = nullptr;
            size++;
            return b;
        }
    }else{

        base -> next = splice(base -> next, b, pos, start, ++iter);
        return base;
    }

   
}

ListNode* LinkedList::deletePush(ListNode* headRef, Stack<ListNode, LinkedList>& reserve, string action, int pos, int iter){ // neeeds to be tailfied
    if(headRef == nullptr){
        return headRef;
    }

    else if(headRef -> type == action || action == "all" || iter == pos){
        
        ListNode* test = new ListNode;
        test -> equation = headRef -> equation;
        test -> type = headRef -> type;
        reserve.push(test);
        size--;
        return deletePush(headRef -> next, reserve, action, pos, ++iter);
    
    }   

    else {

        headRef -> next = deletePush(headRef -> next, reserve, action, pos, ++iter);
        return headRef;
    }
}
