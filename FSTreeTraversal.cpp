/*
Hailey McKelvie
Comp15 proj2
FSTreeTraversal.cpp
12/3/19
	FSTreeTraversal contains an instance of a hashtable, which is made through
 traversing FSTree. It opens files, stores the files in the PathTable and 
then traverses each line and calls insert for every word in the file. After
building the hashTable, query commands are taken. It looks through the
commands and searches, printing to the output file for each time it is found.
*/

#include <iostream>
#include <fstream>
#include "FSTree.h"
#include "DirNode.h"
#include "hashTable.h"
#include "stringProcessing.h"
#include "PathTable.h"
#include <sstream>
using namespace std;

void findWord(ofstream &out, string word, hashTable *hashie, PathTable *paths);
void takeInput(ofstream &out, hashTable *hashie, PathTable *paths);
void build(DirNode *node, string path, hashTable *hashie, 
		PathTable *paths);
void openFile(string path, hashTable *hashie, PathTable *paths);
void hashWords(ifstream &infile, hashTable *hashie, int path);
void findCaseIn(ofstream &out, string word,hashTable *hashie,PathTable *paths);

//main
int main(int argc, char *argv[]) 
{
	if(argc == 3)
	{
		FSTree tree(argv[1]);
		hashTable tables;
		hashTable *hashie = &tables;
		if(not tree.isEmpty())
		{
			PathTable paths;
			build(tree.getRoot(), "", hashie, &paths);
			ofstream out;
			out.open(argv[2]);
			if(out.is_open()){
				takeInput(out, hashie, &paths);
				out.close();
			}
			else
				cerr<<"unable to open output file"<<endl;
		}
		
	}
	else{
		cerr<<"Usage: gerp directory output_file"<<endl;
		return EXIT_FAILURE;
	}
	return 0;
}

// takeInput
// param: ofstream &out, hashTable *hashie, PathTable *paths
// returns: void
// takes input until stopped from cin
void takeInput(ofstream &out, hashTable *hashie, PathTable *paths)
{
	string word;
	//cerr<<__func__<<__LINE__<<endl;
	while(not cin.eof())
	{
		cout<<"Query? ";
		cin>>word;
		cout<<endl;
		if(cin.eof())
			break;
		else if(word == "@q" or word == "@quit")
			break;
		else if(word == "@i" or word == "@insensitive"){
			cin>>word;
			findCaseIn(out, word, hashie, paths);
		}
		else if(word == "@f")
		{
			cin>> word;
			out.close();
			out.open(word);
			if(not out.is_open()){
				cerr<<"file could not open"<<endl;
				break;
			}
		}
		else
			findWord(out, word, hashie, paths);
	}
	cout<<"Goodbye! Thank you and have a nice day."<<endl;
}

// build
// param: DirNode *node, string path, hashTable *hashie,
// PathTable *paths
// returns: void
// builds the hash table
void build(DirNode *node, string path, hashTable *hashie, 
		PathTable *paths)
{
	if(node == nullptr or node->isEmpty())
		return;
	else{
		if(node->hasSubDir()){
			for(int i = 0; i < node->numSubDirs(); i++)
				build(node->getSubDir(i), path + node->getName()+"/", hashie,
					paths);
		}
		if(node->hasFiles()){
			for(int i = 0; i < node->numFiles(); i++)
				openFile(path + node->getName() + "/" + node->getFile(i),
				 hashie, paths);
		}
	}
}

// openFile
// param: string path, hashTable *hashie, PathTable *paths
// returns: void
// opens the file
void openFile(string path, hashTable *hashie, PathTable *paths)
{
	ifstream infile;
	infile.open(path);
	if(infile.is_open())
	{
		hashWords(infile, hashie, paths->add(path));
		infile.close();
	}
}

// hashWords
// param: ifstream &infile, hashTable *hashie, int path
// returns: void
// iterates through the file and inserts into hash table
void hashWords(ifstream &infile, hashTable *hashie, int path)
{
	int lineNum = 1;
	string line = "";
	while(getline(infile, line))
	{
		string word;
		stringstream iss(line);	
		while(iss >> word){
			hashie -> insert(stripNonAlphaNum(word), lineNum, path);
		}
		lineNum++;
	}
}

// findWord
// param: ofstream &out, string word, hashTable *hashie, PathTable *paths
// returns: void
// finds if the Word exists, and prints repsecivly 
void findWord(ofstream &out, string word, hashTable *hashie, PathTable *paths)
{
	if(not hashie -> find(out, word, paths) and word != "")
		out<<word<<" Not Found. Try with @insensitive or @i."<<endl;
}

// findCaseIn
// param: ofstream &out, string word, hashTable *hashie, PathTable *paths
// returns: void
// finds if the case insensitive word exists, and prints repsecivly 
void findCaseIn(ofstream &out, string word,hashTable *hashie, PathTable *paths)
{
	if(not hashie -> findInsen(out, word, paths))
		out<<word<<"query Not Found."<<endl;
}


