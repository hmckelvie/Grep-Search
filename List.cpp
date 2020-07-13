/*
Hailey McKelvie
Comp15 proj2
List.cpp
12/3/19


	The List class stores the instances at which the word exists, including
the line number, the int that corresponds to the file, all in a struct. 
The List class will find whether the word occurs and insert in a node. There is
a vector of the cases of the word. each of the cases (string) is stored in the
vector so then the struct for each instance stored the int index that
corresponds to the case for that word. Additionally, there is a vector
of the instance structs, for storage and searching.
*/
#include "List.h"

using namespace std;

//constructor
List::List()
{
	words.clear();
	words.resize(1);
	cases.clear();
	words.resize(1);
}

// deleteList
// param: none
// returns: void
// deletes the list
void List::deleteList()
{
	while(not words.empty()){
		words.pop_back();
	}
}

// getLength
// param: none
// returns: int
// returns the length of the list
int List::getLength()
{
	return words.size();
}

// insertWord
// param: string toAdd, int line, int pathToWord
// returns: int, the num of word inserted
// inserts the word into the list
int List::insertWord(string toAdd, int line, int pathToWord)
{
	return insertInNode(toAdd, line, pathToWord);
}

bool List::alreadyExists(int index, int line, int pathToWord)
{
	for(int i = 0; i < (int)words.size(); i++){
		if(words.at(i).caseIndex == index and words.at(i).lineNum == line
		and words.at(i).path == pathToWord)
			return true; 
	}
	return false;
}

// insertInNode
// param: string toAdd, int line, int pathToWord
// returns: int, the num of word inserted
// inserts the word into a node
int List::insertInNode(string toAdd, int line, int pathToWord)
{
	int index = getWordCase(toAdd);
	instance newAdd;
	newAdd.caseIndex = index;
	newAdd.lineNum = line;
	newAdd.path = pathToWord;
	words.push_back(newAdd);
	return 1;
}

int List::getWordCase(string toAdd)
{
	for(int i = 0; i < (int)cases.size(); i++){
		if(cases.at(i) == toAdd)
			return i;
	}
	cases.push_back(toAdd);
	return (int)cases.size() - 1;
}

// find
// param: ofstream &out, string toFind, PathTable *paths
// returns: bool, if found
// finds the word in the List
bool List::find(ofstream &out, string toFind, PathTable *paths)
{
	bool exists = false;
	int lastWord = 0;
	int lastLine = 0;
	int lastPath = 0;
	for(int i = 0; i < (int) words.size(); i++)
	{
		if(cases.at(words.at(i).caseIndex) == toFind and not
			(words.at(i).caseIndex == lastWord and words.at(i).lineNum
			== lastLine and words.at(i).path == lastPath)){
			paths -> printPath(words.at(i).path, out);
			out << words.at(i).lineNum << ":";
			paths -> printLine(words.at(i).path, words.at(i).lineNum, out);
			exists = true;
			lastWord = words.at(i).caseIndex;
		  	lastLine = words.at(i).lineNum;
		  	lastPath = words.at(i).path;
		}
	}
	return exists;
}

// find
// param: ofstream &out, string toFind, PathTable *paths
// returns: bool, if found
// finds the case insensitive word in the List
bool List::findInsensitive(ofstream &out, PathTable *paths)
{
	bool exists = false;
	int lastWord = 0;
	int lastLine = 0;
	int lastPath = 0;
	for(int i = 0; i < (int) words.size(); i++)
	{
		if(not (words.at(i).caseIndex == lastWord and words.at(i).lineNum ==
		 lastLine and words.at(i).path == lastPath)) {
			paths -> printPath(words.at(i).path, out);
			out << words.at(i).lineNum << ":";
			paths -> printLine(words.at(i).path, words.at(i).lineNum, out);
			exists = true;
			lastWord = words.at(i).caseIndex;
		  	lastLine = words.at(i).lineNum;
		  	lastPath = words.at(i).path;
		}
	}
	return exists;
}
