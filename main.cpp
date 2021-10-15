#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){

    ArgumentManager am(argc, argv);
    string inputFileName = am.get("input");

    return 0;
}