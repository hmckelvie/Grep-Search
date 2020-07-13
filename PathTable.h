/*
Hailey McKelvie
Comp15 proj2
PathTable.cpp
12/3/19

	PathTable holds all files, so when given a corresponding index,
	it prints the Path of the word.
*/

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#ifndef _PathTable_H_
#define _PathTable_H_

class PathTable{
public:
    PathTable();
    int add(string filePath);
    void printPath(int index, ofstream &out);
    void printLine(int index, int lineNum, ofstream &out);
private:
    vector<string> files;
};
#endif
