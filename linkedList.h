/*
Hailey McKelvie
Comp15 proj2
linkedList.h
12/3/19

	The LinkedList class handles the chaining for collisions in 
	The HashTable. Each node of the LinkedList contains a "List"
	of all instances of a case insensitive "string."
*/
#include <iostream>
#include <vector>
#include <fstream>
#include "List.h"
#include "PathTable.h"

using namespace std;

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

class linkedList{
public:
    linkedList();
    ~linkedList();
    linkedList(const linkedList &source);
    linkedList &operator=(const linkedList &source);
	int insert(string toAdd, string lowered, int line, int pathToWord);
    int getLength();
    int getNumWords();
    bool findandPrint(ofstream &out, string toFind, string lowered,
        PathTable *paths);
    string getHeadLC();
    void removeFromFront();
    void deleteList();
    void addFront(linkedList thisNode);
    bool findInsensitive(ofstream &out, string lowered, PathTable *paths);

private:
	struct Node{
        string lowerCase;
        List words;
        Node *next;
    };

    Node *front;
    int length;
    int numTotalWords;
    int insertAtFront(string toAdd, string lowered, int line,
        int pathToWord);
    int findLowerCaseNode(string toFind, string lowered, int line,
        int pathToWord);
    string lower(string nonLower);
    Node *copy(Node *head);
    void AddToFront(Node *first);
    void printLine(ofstream &out, string file, int line);
};
#endif
