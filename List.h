/*
Hailey McKelvie
Comp15 proj2
List.h
12/3/19
	List contains all case insensitive and sensitive instances
	of a specific word and respective location. 
*/
#include <iostream>
#include <vector>
#include <fstream>
#include "PathTable.h"

using namespace std;

#ifndef _LIST_H_
#define _LIST_H_

class List{
public:
    List();
    bool find(ofstream &out, string toFind, PathTable *paths);
    bool findInsensitive(ofstream &out, PathTable *paths);
    int insertWord(string toAdd, int line, int pathToWord);
    int getLength();
    string getLC();
private:
    struct instance{
        int lineNum;
        int path;
        int caseIndex;
    };

    vector<instance> words;
    vector<string> cases;

    int binaryInsert(int low, int high, int line);
    int insertInNode(string toAdd, int line, int pathToWord);
    void deleteList();
    int getWordCase(string toAdd);
    bool alreadyExists(int index, int line, int pathToWord);
  
};
#endif
