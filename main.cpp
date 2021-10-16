#include <iostream>
#include "ArgumentManager.h"
#include "LinkedList.h"
#include "Stack.h"
#include <fstream>
#include <string>
using namespace std;

struct PartialNode{

    string data;
    PartialNode* next;

    PartialNode (){
        next=nullptr;
    }
};

int charChecker(char op){

    switch (op){
        
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 1;
        case '/':
            return 1;
        default:
            return -1;
    
    }
}

void converter(ListNode* eqNode, string action){

    PartialNode* tmp = new PartialNode;//need this stupid func.

    
}

string cleanString(string dirty){

    string clean;

    for (int i = 0; i < dirty.length(); ++i){
        
        if(dirty.at(i) != ' '){

            clean += dirty.at(i);

        }
    }

    return clean;
}

void getInput(ifstream& ifs, LinkedList& dll){

    string line;

    while(getline(ifs,line)){

        if (line == ""){

            continue;
        }

        string type = line.substr(0, line.find(':'));
        string equation = line.substr(line.find(':') + 1, line.length() - line.find(':') + 1);
        equation = cleanString(equation);
        dll.addToEnd(equation, type);
    }
}

int main(int argc, char *argv[]){

    ArgumentManager am(argc, argv);
    string inputFileName = am.get("input");
    ifstream ifs(inputFileName.c_str());
    Stack<ListNode, LinkedList> test;
    LinkedList dll;

    getInput(ifs, dll);

    dll.print(dll.getHead());
    return 0;
}