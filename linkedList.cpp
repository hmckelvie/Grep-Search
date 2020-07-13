/*
Hailey McKelvie
Comp15 proj2
linkedList.cpp
12/3/19


	The linkedList class stores nodes which contain an instance of a List,
a pointer to the next node, and the lowercase version of that word. The
linkedList inserts a word, either by creating a new node or by putting it
in an already existing node. The linked List searches for a word through
traversing the linkedList and calling List when the lowercase Node is found.
Additionally, the linkedList contains the big three. 

*/
#include "linkedList.h"

//default constructor
linkedList::linkedList()
{
	front = nullptr;
	length = 0;
	numTotalWords = 0;
}

//destructor
linkedList::~linkedList()
{
	deleteList();
}

// deleteList
// param: none
// returns: void
// deletes the linkedList
void linkedList::deleteList()
{
	Node *temp;
	Node *current = front;
	while(current != nullptr)
	{
		temp = current -> next;
		delete current;
		current = temp;
	}
	front = nullptr;
	length = 0;
	numTotalWords = 0;
}

// getHeadLC
// param: none
// returns: string
// get the head lowercase word
string linkedList::getHeadLC()
{
	return front -> lowerCase; 
}

// addFront
// param: linkedList thisNode
// returns: void
// adds the head of the linkedList node to front
void linkedList::addFront(linkedList thisNode)
{
	AddToFront(thisNode.front);
}

//copy constructor
linkedList::linkedList(const linkedList &source)
{
	length = source.length;
    numTotalWords = source.numTotalWords;
	front = copy(source.front);
}

//assignment overload operator
linkedList &linkedList::operator=(const linkedList &source)
{
	if(this == &source)
        return *this;
    else{
        deleteList();
        front = copy(source.front);
        length = source.length;
        numTotalWords = source.numTotalWords;
        return *this;
    }
}

// copy
// param: Node *head
// returns: Node *
// copies over the linkedList
linkedList::Node * linkedList::copy(Node *head)
{
	if(head == nullptr)
		return nullptr;
	else{
		Node *copies = new Node;
		copies -> lowerCase = head -> lowerCase;
		copies -> words = head -> words;
		copies-> next = copy(head -> next);
		return copies;
	}
}

// getLength
// param: none
// returns: int
// returns the length of linkedList
int linkedList::getLength()
{
	return length;
}

// getNumWords
// param: none
// returns: int
// returns the number of words in the linkedList
int linkedList::getNumWords()
{
	return numTotalWords;
}

// insert
// param: string toAdd, string lowered, int line, int pathToWord
// returns: int
// inserts the word into the linked list
int linkedList::insert(string toAdd, string lowered, int line, int
	 pathToWord)
{
	int exists = findLowerCaseNode(toAdd, lowered, line, pathToWord);
	if(exists == 2)
		return insertAtFront(toAdd, lowered, line, pathToWord);
	else
		return exists;
}

// AddToFront
// param: Node *first
// returns: void
// adds the node to the fron of the linked list
void linkedList::AddToFront(Node *first)
{

	Node *temp = new Node;
	temp -> words = first -> words;
	temp -> lowerCase = first -> lowerCase;
	numTotalWords = numTotalWords + first-> words.getLength();
	length++;
	temp -> next = front;
	front = temp;
}

// insertAtFront
// param: string toAdd, string lowered, int line, int pathToWord
// returns: int, the number of words added
// inserts the word to the front of the list
int linkedList::insertAtFront(string toAdd, string lowered, int line, 
	int pathToWord)
{
	Node *temp = new Node;
	temp -> lowerCase = lowered;
	List w;
	w.insertWord(toAdd, line, pathToWord);
	temp -> words = w;
	temp -> next = front;
	front = temp;
	length++;
	numTotalWords = numTotalWords + w.getLength();
	return 1;
}

// findLowerCaseNode
// param: string toAdd, string lowered, int line, int pathToWord
// returns: int, the number of words added, 2 if not added
// finds if the node for that word already exists
int linkedList::findLowerCaseNode(string toFind, string lowered, int line,
	int pathToWord)
{
	Node *temp = front;
	int exists; 
	while(temp != nullptr){
		if(temp -> lowerCase == lowered){
			exists = temp -> words.insertWord(toFind, line, pathToWord);
			if(exists == 1)
				numTotalWords++;
			return exists;
		}
		temp = temp -> next;
	}
	return 2;
}

// insertAtFront
// param: ofstream &out, string toFind, string lowered, PathTable *paths
// returns: bool, if found 
// finds case sensitive if there 
bool linkedList::findandPrint(ofstream &out, string toFind, string lowered,
 PathTable *paths)
{
	Node *temp = front;
	bool found = false;
	while(temp != nullptr){
		if(temp -> lowerCase == lowered)
			return temp -> words.find(out, toFind, paths);
		temp = temp -> next;
	}
	return found;
}

// insertAtFront
// param: ofstream &out, string toFind, string lowered, PathTable *paths
// returns: bool, if found 
// finds case insensitive if there 
bool linkedList::findInsensitive(ofstream &out, string lowered, PathTable 
	*paths)
{
	Node *temp = front;
	bool found = false;
	while(temp != nullptr){
		if(temp -> lowerCase == lowered)
			return temp -> words.findInsensitive(out, paths);
		temp = temp -> next;
	}
	return found;
}

// lower
// param: string nonLower
// returns: string
// makes the string lowercase
string linkedList::lower(string nonLower)
{
	string lowered = "";
	for(int i = 0; i < (int)nonLower.length(); i++)
		lowered = lowered + (char)tolower(nonLower.at(i));
	return lowered;
}

// removeFromFront
// param: none
// returns: void
// removes node from front
void linkedList::removeFromFront()
{
	Node *temp = front -> next;
	numTotalWords = numTotalWords - front -> words.getLength();
	delete front;
	front = temp;
	length--;

}
