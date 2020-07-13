/*
Hailey McKelvie
Comp15 Project 2
Hash Table Class
12/3/19

The hashtable class contains a vector of linkedLists which represents the 
table. The hashTable inserts a word through using the c++ hashing function mod
the size of the table. At that index in the vector, the table inserts to the 
linked list existing there. The hashtable is initialized with each index of 
the vector containing an empty linked list. When inserting, the loadFactor is
checked. If the number of the elements divided by the size of the hash table
is greater than the load factor, which in this case 0.75. If the table exceeds
the load factor, the table will expand by a factor of 2. Expansion is done
through copying the origional hash table over into a vector of the same size
called toExpand. Then, the origional table is cleared and initialized ot 2
times the size. Everything from toExpand is rehashed into the new table and
toExpand is cleared. The hashtable searches through hashing the lowercase
version of the word to find where it would be stored, then it calls the find
for that linked list.

*/

#include "hashTable.h"

//default constructor
hashTable::hashTable()
{
	tableSize = 5000000;
	linkedList temp;
	for(int i = 0; i < tableSize; i++)
		table.push_back(temp);
	for(int i = 0; i < tableSize; i++)
		toExpand.push_back(temp);
	totalWords = 0;
}

//destructor
hashTable::~hashTable()
{
	deleteTable();
}

// insert
// param: string word, int line, int path
// returns: void
// inserts word into the hash table
void hashTable::insert(string word, int line, int path)
{
	string toHash = lower(word);
	int hashIndex = (hash<string>{}(toHash)) % tableSize;
	if((table.at(hashIndex)).insert(word, toHash, line, path) == 1){
		totalWords++;
		checkLoadFactor();
	}
	
}

// find
// param: ofstream &out, string word, PathTable *paths
// returns: bool, if found
// finds if the word exists, and prints repsectivly 
bool hashTable::find(ofstream &out, string word, PathTable *paths)
{
	string toHash = lower(word);
	int hashIndex = (hash<string>{}(toHash)) % tableSize;
	return (table.at(hashIndex)).findandPrint(out, word, toHash, paths);
}

// findInsen
// param: ofstream &out, string word, PathTable *paths
// returns: bool
// finds the insensitive version of the word and prints respectivly
bool hashTable::findInsen(ofstream &out, string word, PathTable *paths)
{
	string toHash = lower(word);
	int hashIndex = hash<string>{}(toHash) % tableSize;
	return (table.at(hashIndex).findInsensitive(out, toHash, paths));
}

// checkLoadFactor
// param: none
// returns: void
// checks to see if should expand
void hashTable::checkLoadFactor()
{
	if((double)(sumElem()/tableSize) >= loadFactor)
		expand();
}

// sumElem
// param: none
// returns: int, num of elements
// returns the number of words stored
int hashTable::sumElem()
{
	return totalWords;
}

// expand
// param: none
// returns: void
// expands the hash table by a factor of 2
void hashTable::expand()
{
	//cerr<<"expand"<<endl;
	tableSize = tableSize * expandFactor;
	toExpand = table;
	deleteTable();
	for(int i = 0; i < (tableSize / 2); i++){
		int length = (toExpand.at(i)).getLength();
		for(int j = 0; j < length; j++){
			add(toExpand.at(i).getHeadLC(), toExpand.at(i));
			(toExpand.at(i)).removeFromFront();
		}
	}
}

// add
// param: string lowercase, linkedList thisNode
// returns: void
// after expansion, rehashing into the new hashTable
void hashTable::add(string lowercase, linkedList thisNode)
{
	int hashIndex = (hash<string>{}(lowercase)) % tableSize;
	(table.at(hashIndex)).addFront(thisNode);
}

// deleteTable
// param: none
// returns: void
// clears the hash table
void hashTable::deleteTable()
{
	for(int i = 0; i < (tableSize / expandFactor); i++)
		(table.at(i)).deleteList();
	linkedList temp;
	for(int i = 0; i < tableSize; i++)
		table.push_back(temp);
}

// copy
// param: int size, hashTable &source
// returns: void
// copies over the hashTable
void hashTable::copy(int size, const hashTable &source)
{
	for(int i = 0; i < size; i++)
		table.at(i) = source.table.at(i);
	tableSize = source.tableSize;
    totalWords = source.totalWords;
}

//copy constructor
hashTable::hashTable(const hashTable &source)
{
	copy(source.tableSize, source);
    tableSize = source.tableSize;
    totalWords = source.totalWords;
}

//overload operator
hashTable &hashTable::operator=(const hashTable &source)
{
	if(this == &source)
            return *this;
    else{
        deleteTable();
        copy(source.tableSize, source);
        tableSize = source.tableSize;
        totalWords = source.totalWords;
        return *this;
    }
}

// lower
// param: string nonLower
// returns: string
// makes a string lowercase
string hashTable::lower(string nonLower)
{
	string lowered = "";
	for(int i = 0; i < (int)nonLower.length(); i++)
		lowered = lowered + (char)tolower(nonLower.at(i));
	return lowered;
}


