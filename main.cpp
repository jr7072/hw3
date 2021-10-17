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

    Stack<PartialNode, LinkedList> cs;
    string equation = eqNode -> equation;
    string holder = "";
    int charFlag;
    string op;
    string conversion = "";

    if(action == "prefix"){

        for(int i = 0; i < equation.length(); ++i){

            charFlag = charChecker(equation.at(i));
            if(i == equation.length() - 1){
                
                stringstream fs;
                int ogSize = cs.getSize();

                for(int j = 0; j < ogSize; ++j){
                
                    PartialNode* popPartial = new PartialNode;
                    popPartial = cs.pop();
                    conversion.insert(0, popPartial -> data);

                }
                
                fs << equation.at(i);
                fs >> op;
                conversion.insert(0, op);
                eqNode -> equation = conversion;
                eqNode -> type = action;


            }else if(charFlag == -1){

                PartialNode* charN = new PartialNode;
                charN -> data = equation.at(i);
                cs.push(charN);

            }else{

                stringstream ss;
                
                for(int k = 0; k < 2; ++k){
                    PartialNode* popNode = new PartialNode;
                    popNode = cs.pop();
                    holder.insert(0, popNode -> data);
                }

                ss << equation.at(i);
                ss >> op;
                holder.insert(0, op);
                PartialNode* partial = new PartialNode;
                partial -> data = holder;
                cs.push(partial);
                holder = "";
            }
        }
    }else{

        for(int i = equation.length() - 1; i >= 0; --i){

            charFlag = charChecker(equation.at(i));

            if(i == 0){
                
                stringstream fs;
                int ogSize = cs.getSize();

                for(int j = 0; j < ogSize; ++j){
                
                    PartialNode* popPartial = new PartialNode;
                    popPartial = cs.pop();
                    conversion += popPartial -> data;

                }
                
                fs << equation.at(i);
                fs >> op;
                conversion += op;
                eqNode -> equation = conversion;
                eqNode -> type = action;


            }else if(charFlag == -1){

                PartialNode* charN = new PartialNode;
                charN -> data = equation.at(i);
                cs.push(charN);

            }else{

                stringstream ss;
                
                for(int k = 0; k < 2; ++k){
                    PartialNode* popNode = new PartialNode;
                    popNode = cs.pop();
                    holder += popNode -> data;
                }

                ss << equation.at(i);
                ss >> op;
                holder += op;
                PartialNode* partial = new PartialNode;
                partial -> data = holder;
                cs.push(partial);
                holder = "";
            }
            
        }

    }

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

bool arguments(string line){

    bool isThere = false;

    for(int i = 0; i < line.length(); ++i){

        if(line.at(i) == '(' ){

            isThere = true;
        }
    }

    return isThere;
}

void executeCommands(LinkedList& dll, Stack<ListNode, LinkedList>& reserve, ifstream& cfs){

    string line;
    string function;
    string argument;
    bool thereIsArguments = false;

    while(getline(cfs, line)){

        if(line == ""){

            continue;
        }

        thereIsArguments = arguments(line);

        if(thereIsArguments){

            function = line.substr(0, line.find(' '));
            argument = line.substr(line.find('(') + 1, line.length() - (line.find('(') + 2));

        }else{

            function = line;
        }

        if(function == "printList"){

            dll.print(dll.getHead());
            cout << endl;

        }

        else if(function == "printListBackwards"){
            
            dll.printBack(dll.getHead());
            cout << endl;

        }
        else if(function == "convertList"){

            if(isdigit(argument[0])){
                
                int digit = stoi(argument);
                dll.convertList(converter, dll.getHead(), "null", digit);
                cout << endl;

            }else{

                dll.convertList(converter, dll.getHead(), argument);
                cout << endl;
            }
        }
        else if(function == "removeList"){
            
            if(isdigit(argument[0])){
                
                int digit = stoi(argument);
                dll.setHead(dll.removeList(dll.getHead(), "null", digit));
                cout << endl;

            }else{

                dll.setHead(dll.removeList(dll.getHead(), argument));
                cout << endl;
            }
            
        }
        else if(function == "pushReserve"){

            
            if(isdigit(argument[0])){
                
                int digit = stoi(argument);
                dll.setHead(dll.deletePush(dll.getHead(), reserve, "null", digit));
                cout << endl;


            }else{

                dll.setHead(dll.deletePush(dll.getHead(), reserve, argument));
                cout << endl;
            }

            
        }
        else if(function == "popReserve"){
            
            int digit = stoi(argument);

            reserve.popReserve(dll, digit);
            cout << endl;
            
        }
        else if(function == "flipReserve"){

            reserve.flipReserve();\
            cout << endl;
        
        }
        else if(function == "printReserveSize"){

            reserve.printSize();
            cout << endl;

        }
        else if(function == "convertReserve"){

            reserve.convertReserve(converter);
            cout << endl;
            
        }
        else if(function == "printReserveTop"){

            reserve.printTop();
            cout << endl;
            
        }
        else if(function == "emptyReserve"){

            int digit = stoi(argument);

            reserve.emptyReserve(dll, digit);
            cout << endl;
            
        }

    }


}

int main(int argc, char *argv[]){

    ArgumentManager am(argc, argv);
    string inputFileName = am.get("input");
    ifstream ifs(inputFileName.c_str());
    string commandFileName = am.get("command");
    ifstream cfs(commandFileName.c_str());
    Stack<ListNode, LinkedList> reserve;
    LinkedList dll;

    getInput(ifs, dll);
    executeCommands(dll, reserve, cfs);


    //dll.setHead(dll.deletePush(dll.getHead(), reserve, "postfix"));

    return 0;
}