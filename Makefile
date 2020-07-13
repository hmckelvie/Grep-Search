
#Hailey McKelvie
#Comp15 proj2
#Makefile
#12/3/19

CXX      = clang++
CXXFLAGS = -g3  -std=c++11 -Wall -Wextra  -Wpedantic -Wshadow
LDFLAGS  = -g3


gerp: linkedList.o hashTable.o FSTreeTraversal.o stringProcessing.o List.o \
 PathTable.o
	$(CXX) $(LDFLAGS) -o gerp linkedList.o hashTable.o \
		FSTreeTraversal.o stringProcessing.o FSTree.o DirNode.o List.o \
		PathTable.o

linkedList.o: linkedList.h linkedList.cpp List.h PathTable.h
List.o: List.h List.cpp
hashTable.o: hashTable.h hashTable.cpp linkedList.h PathTable.h
FSTreeTraversal.o: DirNode.h FSTree.h FSTreeTraversal.cpp \
	stringProcessing.h hashTable.h PathTable.h
stringProcessing.o: stringProcessing.h stringProcessing.cpp
PathTable.o: PathTable.h PathTable.cpp


clean:
	rm -f *.o core* *~ gerp

provide:
	provide comp15 proj2part2 README Makefile FSTreeTraversal.cpp \
	linkedList.h linkedList.cpp List.h List.cpp PathTable.h PathTable.cpp \
	hashTable.h hashTable.cpp DirNode.h FSTree.h stringProcessing.h \
	stringProcessing.cpp FSTree.o DirNode.o 