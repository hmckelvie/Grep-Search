/*
Hailey McKelvie
Comp15 proj2
PathTable.cpp
12/3/19
When a file is found in traversing the FSTree, store each file in a vector
in PathTable. This makes it so string that is the file path is not stored
multiple times. Each word would then correspond to the index at which its
path is sotred in the vector. The PathTable can be used to print the line on
which the word occurs and print its path. The driver function passes a pointer
to the pathtable through to the find functions. When printing the line,
it checks to see if that word is repeated in the line and only prints once.
*/

#include "PathTable.h"

//constructor
PathTable::PathTable()
{
	files.clear();
}

// add
// param: string filePath
// returns: index the file is added at
// adds the file into the vector
int PathTable:: add(string filePath)
{
	files.push_back(filePath);
	return files.size() - 1;
}

// printPath
// param: int index, ofstream &out
// returns: void
// prints the path to the outfile
void PathTable::printPath(int index, ofstream &out)
{
	out << files.at(index) <<  ":";
}

// printLine
// param: int index, ofstream &out, int lineNum
// returns: void
// prints the line to the outfile
void PathTable::printLine(int index, int lineNum, ofstream &out)
{
	int count = 1;
	string lines = "";
	ifstream opening;
	opening.open(files.at(index));
	if(opening.is_open())
	{
		while(count <= lineNum and getline(opening, lines))
		{
			if(count == lineNum)
				out<<" "<<lines<<endl;
			count++;
		}
		opening.close();
	}
}
