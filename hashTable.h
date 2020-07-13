/*
Hailey McKelvie
Comp15 Project 2
Hash Table Class
12/3/19

	Inserts words into the Hash table. Can find words via the "grep search"
	either case sensitive or case insensitive. 
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include "linkedList.h"
#include "PathTable.h"

using namespace std;

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

class hashTable{
public:
	hashTable();
	~hashTable();
    hashTable(const hashTable &source);
    hashTable &operator=(const hashTable &source);
	bool find(ofstream &out, string word, PathTable *paths);
	bool findInsen(ofstream &out, string word, PathTable *paths);
	void insert(string word, int line, int path);

private:
	vector<linkedList> table;
	vector<linkedList> toExpand;
	int tableSize;
	int totalWords;
	double const loadFactor = 0.75;
	double const expandFactor = 2.0;
	void expand();
	void deleteTable();
	void checkLoadFactor();
	int sumElem();
	void add(string lowercase, linkedList thisNode);
	void copy(int size, const hashTable &source);
	string lower(string nonLower);
};


#endif
