/*
File:			DSA_TestSuite_Lab3.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		12.27.2020
Last Modified:	02.26.2021
Purpose:		Definitions of Lab3 Unit Tests for DList
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <iostream>
#include "DList.h"
#include "DSA_TestSuite_Lab3.h"
#include "DSA_Memory_Management.h"

#if LAB_3
void DSA_TestSuite_Lab3::DisplayNode(int _val, const Node* _next,
	const Node* _prev, const Node& _node) {
	std::cout << "\t\tExpected Values\t\tYour Values\n"
		<< "data:\t\t" << _val << "\t\t\t" << _node.data << '\n';
	std::cout << "next:\t\t" << _next << "\t" << _node.next << '\n';
	std::cout << "prev:\t\t" << _prev << "\t" << _node.prev << '\n';
}

void DSA_TestSuite_Lab3::DisplayList(const std::list<int>& _list,
	const DList<int>& _dlist) {
	std::cout << "\tExpected list\n";
	std::cout << "Forward iteration:\t";
	for (auto iter = _list.begin(); iter != _list.end(); ++iter)
		std::cout << "[" << *iter << "]->";
	std::cout << "0\n";

	std::cout << "Backward iteration:\t";
	for (auto iter = _list.rbegin(); iter != _list.rend(); ++iter)
		std::cout << "[" << *iter << "]->";
	std::cout << "0\n";
	std::cout << "Size:\t" << _list.size() << '\n';

	std::cout << "\tYour list\n";
	std::cout << "Forward iteration:\t";
	DList<int>::Node* curr;
	for (curr = _dlist.mHead; curr; curr = curr->next)
		std::cout << "[" << curr->data << "]->";
	std::cout << (!curr ? "0" : "?") << '\n';

	std::cout << "Backward iteration:\t";
	for (curr = _dlist.mTail; curr; curr = curr->prev)
		std::cout << "[" << curr->data << "]->";
	std::cout << (!curr ? "0" : "?") << '\n';

	std::cout << "Size:\t" << _dlist.mSize << '\n';
}

void DSA_TestSuite_Lab3::DisplayList(const std::list<UserDefined>& _list,
	const DList<UserDefined>& _dlist) {
	std::cout << "\tExpected list\n";
	std::cout << "Forward iteration:\t";
	for (auto iter = _list.begin(); iter != _list.end(); ++iter)
		std::cout << "[" << iter->mString << "," << iter->mValue << "]->";
	std::cout << "0\n";

	std::cout << "Backward iteration:\t";
	for (auto iter = _list.rbegin(); iter != _list.rend(); ++iter)
		std::cout << "[" << iter->mString << "," << iter->mValue << "]->";
	std::cout << "0\n";
	std::cout << "Size:\t" << _list.size() << '\n';

	std::cout << "\tYour list\n";
	std::cout << "Forward iteration:\t";
	DList<UserDefined>::Node* curr;
	for (curr = _dlist.mHead; curr; curr = curr->next)
		std::cout << "[" << curr->data.mString << ',' << curr->data.mValue << "]->";
	std::cout << (!curr ? "0" : "?") << '\n';

	std::cout << "Backward iteration:\t";
	for (curr = _dlist.mTail; curr; curr = curr->prev)
		std::cout << "[" << curr->data.mString << ',' << curr->data.mValue << "]->";
	std::cout << (!curr ? "0" : "?") << '\n';

	std::cout << "Size:\t" << _dlist.mSize << '\n';
}

#if LIST_CTOR
void DSA_TestSuite_Lab3::LinkedListDefaultConstructor() {
	std::cout << "Testing DList's default constructor\n";

	DList<int> dlist;

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	if (dlist.mHead)
		PrintMessage("head is not null");
	if (dlist.mTail)
		PrintMessage("tail is not null");
	if (dlist.mSize)
		PrintMessage("size is not zero");
	if (metrics.inUse)
		PrintMessage("No memory should be allocated to an empty list");

	// Testing for success
	if (!dlist.mHead && !dlist.mTail &&
		!dlist.mSize && !metrics.inUse)
		PrintMessage();
}
#endif	// End LIST_CTOR

#if LIST_NODE_CTOR_DEFAULT
void DSA_TestSuite_Lab3::LinkedListNodeConstructorWithDefaults() {
	std::cout << "Testing DList::Node constructor with default node parameters\n";

	int randVal = rand() % 100 + 1;
	Node node(randVal);

	if (verboseMode)
		DisplayNode(randVal, nullptr, nullptr, node);

	if (randVal != node.data)
		PrintMessage("Data in node is incorrect");
	if (node.next)
		PrintMessage("Node's next should be null");
	if (node.prev)
		PrintMessage("Node's prev should be null");

	// Testing for success
	if (randVal == node.data && !node.next && !node.prev)
		PrintMessage();
}
#endif	// End LIST_NODE_CTOR_DEFAULT

#if LIST_DTOR
void DSA_TestSuite_Lab3::LinkedListDestructor() {
	std::cout << "Testing destructor\n";

	DList<int>* list = new DList<int>;
	
	// Manually creating and linking a few nodes
	list->mHead = new Node(rand() % 10);
	list->mHead->next = new Node(rand() % 10);
	list->mHead->next->next = new Node(rand() % 10);
	list->mTail = list->mHead->next->next;
	list->mTail->prev = list->mHead->next;
	list->mTail->prev->prev = list->mHead;
	list->mHead->prev = list->mTail->next = nullptr;


	delete list;

	if (verboseMode)
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (metrics.inUse != 0)
		PrintMessage("Not all dynamic memory was freed");

	// Testing for success
	if (!metrics.inUse)
		PrintMessage();
}
#endif	// End LIST_DTOR

#if LIST_NODE_CTOR
void DSA_TestSuite_Lab3::LinkedListNodeConstructor() {
	std::cout << "Testing DList::Node constructor with valid next and prev pointers\n";

	int randVal = rand() % 100 + 1;

	Node next(0), prev(0);
	Node node(randVal, &next, &prev);

	if (verboseMode)
		DisplayNode(randVal, &next, &prev, node);

	if (randVal != node.data)
		PrintMessage("Data in node is incorrect");
	if (node.next != &next)
		PrintMessage("Node's next is not pointing to correct node");
	if (node.prev != &prev)
		PrintMessage("Node's prev is not pointing to correct node");

	// Testing for success
	if (randVal == node.data &&
		node.next == &next &&
		node.prev == &prev)
		PrintMessage();
}
#endif	// End LIST_NODE_CTOR

#if LIST_ADDHEAD_EMPTY
void DSA_TestSuite_Lab3::LinkedListAddHeadEmpty() {
	std::cout << "Testing AddHead on empty list\n";

	int randVal = rand() % 100 + 1;

	std::list<int> list;
	list.push_front(randVal);

	size_t memoryUsed = metrics.inUse;

	DList<int> dlist;
	dlist.AddHead(randVal);
	
	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("Too much memory allocated");
	if (metrics.inUse < memoryUsed + sizeof(Node))
		PrintMessage("Not enough memory allocated");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to created node");
	if (!dlist.mTail)
		PrintMessage("Tail is not pointing to created node");
	if (dlist.mHead != dlist.mTail)
		PrintMessage("Head and Tail should point to same node");
	if (dlist.mHead && dlist.mHead->data != randVal)
		PrintMessage("Node's data was not set correctly");
	if (dlist.mHead && dlist.mHead->prev)
		PrintMessage("Node's prev is not set correctly");
	if (dlist.mHead && dlist.mHead->next)
		PrintMessage("Node's next is not set correctly");
	if (dlist.mSize != 1)
		PrintMessage("Size is incorrect");

	// Testing for success
	if (dlist.mHead && dlist.mTail &&
		dlist.mHead == dlist.mTail &&
		randVal == dlist.mHead->data &&
		!dlist.mHead->prev &&
		!dlist.mHead->next &&
		1 == dlist.mSize)
		PrintMessage();
}
#endif	// End LIST_ADDHEAD_EMPTY

#if LIST_ADDHEAD
void DSA_TestSuite_Lab3::LinkedListAddHeadExisting() {
	std::cout << "Testing AddHead on non-empty list\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	
	std::list<int> list;
	for(size_t i = 0; i < randomSize; ++i)
	list.push_front(rand()% 100 + 1);

	size_t memoryUsed = metrics.inUse;

	DList<int> dlist;
	auto reviter = list.rbegin();
	for (size_t i = 0; i < randomSize; ++i, ++reviter)
		dlist.AddHead(*reviter);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse > memoryUsed + sizeof(Node) * randomSize)
		PrintMessage("Too much memory allocated");
	if (metrics.inUse < memoryUsed + sizeof(Node) * randomSize)
		PrintMessage("Not enough memory allocated");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to created node");
	if (!dlist.mTail)
		PrintMessage("Tail is not pointing to created node");
	auto foriter = list.begin();
	bool identVals = true;
	for(Node* curr = dlist.mHead; curr; curr = curr->next, ++foriter)
		if (curr->data != *foriter) {
			PrintMessage("Node's data was not set correctly or nodes are not linked correctly (forward)");
			identVals = false;
			break;
		}
	reviter = list.rbegin();
	for(Node* curr = dlist.mTail; curr; curr = curr->prev, ++reviter)
		if (curr->data != *reviter) {
			PrintMessage("Node's data was not set correctly or nodes are not linked correctly (backward)");
			identVals = false;
			break;
		}
	if (dlist.mSize != randomSize)
		PrintMessage("Size is incorrect");
	
	// Testing for success
	if (dlist.mHead && dlist.mTail &&
		identVals && randomSize == dlist.mSize)
		PrintMessage();
}
#endif	// End LIST_ADDHEAD

#if LIST_ADDTAIL_EMPTY
void DSA_TestSuite_Lab3::LinkedListAddTailEmpty() {
	std::cout << "Testing AddTail on empty list\n";

	int randVal = rand() % 100 + 1;

	std::list<int> list;
	list.push_front(randVal);

	size_t memoryUsed = metrics.inUse;

	DList<int> dlist;
	dlist.AddTail(randVal);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("Too much memory allocated");
	if (metrics.inUse < memoryUsed + sizeof(Node))
		PrintMessage("Not enough memory allocated");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to created node");
	if (!dlist.mTail)
		PrintMessage("Tail is not pointing to created node");
	if (dlist.mHead != dlist.mTail)
		PrintMessage("Head and Tail should point to same node");
	if (dlist.mHead && dlist.mHead->data != randVal)
		PrintMessage("Node's data was not set correctly");
	if (dlist.mHead && dlist.mHead->prev)
		PrintMessage("Node's prev is not set correctly");
	if (dlist.mHead && dlist.mHead->next)
		PrintMessage("Node's next is not set correctly");
	if (dlist.mSize != 1)
		PrintMessage("Size is incorrect");

	// Testing for success
	if (dlist.mHead && dlist.mTail &&
		dlist.mHead == dlist.mTail &&
		randVal == dlist.mHead->data &&
		!dlist.mHead->prev &&
		!dlist.mHead->next &&
		1 == dlist.mSize)
		PrintMessage();
}
#endif	// End LIST_ADDTAIL_EMPTY

#if LIST_ADDTAIL
void DSA_TestSuite_Lab3::LinkedListAddTailExisting() {
	std::cout << "Testing AddTail on non-empty list\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	size_t memoryUsed = metrics.inUse;

	DList<int> dlist;
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		dlist.AddTail(*foriter);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse > memoryUsed + sizeof(Node) * randomSize)
		PrintMessage("Too much memory allocated");
	if (metrics.inUse < memoryUsed + sizeof(Node) * randomSize)
		PrintMessage("Not enough memory allocated");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to created node");
	if (!dlist.mTail)
		PrintMessage("Tail is not pointing to created node");
	foriter = list.begin();
	bool identVals = true;
	for (Node* curr = dlist.mHead; curr; curr = curr->next, ++foriter)
		if (curr->data != *foriter) {
			PrintMessage("Node's data was not set correctly or nodes are not linked correctly (forward)");
			identVals = false;
			break;
		}
	auto reviter = list.rbegin();
	for (Node* curr = dlist.mTail; curr; curr = curr->prev, ++reviter)
		if (curr->data != *reviter) {
			PrintMessage("Node's data was not set correctly or nodes are not linked correctly (backward)");
			identVals = false;
			break;
		}
	if (dlist.mSize != randomSize)
		PrintMessage("Size is incorrect");

	// Testing for success
	if (dlist.mHead && dlist.mTail &&
		identVals && randomSize == dlist.mSize)
		PrintMessage();
}
#endif // End LIST_ADDTAIL

#if LIST_CLEAR
void DSA_TestSuite_Lab3::LinkedListClear() {
	size_t randomSize = size_t(rand() % 6) + 5;

	std::cout << "Testing Clear method on list with " << randomSize << " nodes\n";

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node*[randomSize];
	// Allocating the indivual nodes
	for (size_t i = 0; i < randomSize; ++i) 
		nodes[i] = new Node((int)i);
	// Creating the linked list
	nodes[0]->prev = nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;
	
	dlist.Clear();

	delete[] nodes;

	if (verboseMode) {
		std::cout << "Nodes still allocated: "
			<< (metrics.inUse / sizeof(Node)) << "\n";
	}

	if (dlist.mHead)
		PrintMessage("Head is not null");
	if (dlist.mTail)
		PrintMessage("Tail is not null");
	if (dlist.mSize)
		PrintMessage("Size was not reset to zero");
	if (metrics.inUse)
		PrintMessage("Not all nodes were deleted");
	
	// Testing for success
	if (!dlist.mHead && !dlist.mTail &&
		!dlist.mSize && !metrics.inUse)
		PrintMessage();
}
#endif // End LIST_CLEAR

#if LIST_INSERT_EMPTY
void DSA_TestSuite_Lab3::LinkedListInsertEmpty() {
	std::cout << "Testing Insert on empty list\n";

	DList<int> dlist;
	DList<int>::Iterator iter;

	iter.mCurr = dlist.mHead;

	int randomVal = rand() % 100 + 1;
	
	std::list<int> list;
	list.push_back(randomVal);

	const size_t memoryUsed = metrics.inUse;

	dlist.Insert(iter, randomVal);

	if (verboseMode)
		DisplayList(list, dlist);

	if (memoryUsed == metrics.inUse)
		PrintMessage("Node was not created");
	if ((metrics.inUse-memoryUsed) > sizeof(Node))
		PrintMessage("More than one node was created");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to a valid Node");
	else {
		if (dlist.mHead->data != randomVal)
			PrintMessage("Head's data is not set correctly");
		if (dlist.mHead->prev)
			PrintMessage("Head's prev is not set correctly");
		if (dlist.mHead->next)
			PrintMessage("Head's next is not set correctly");
	}
	if (!dlist.mTail)
		PrintMessage("Tail is not pointing to a valid Node");
	else {
		if (dlist.mTail->data != randomVal)
			PrintMessage("Tail's data is not set correctly");
		if (dlist.mTail->prev)
			PrintMessage("Tail's prev is not set correctly");
		if (dlist.mTail->next)
			PrintMessage("Tail's next is not set correctly");
	}
	if (dlist.mHead && dlist.mTail && dlist.mHead != dlist.mTail)
		PrintMessage("Head and Tail should point to same Node");
	if (iter.mCurr != dlist.mHead)
		PrintMessage("Iterator is not pointing to inserted Node");
	if (dlist.mSize != 1)
		PrintMessage("Size was not incremented");

	// Testing for sucess
	if (memoryUsed + sizeof(Node) == metrics.inUse &&
		dlist.mHead && dlist.mTail &&
		dlist.mHead == dlist.mTail &&
		dlist.mHead->data == randomVal &&
		!dlist.mHead->prev && !dlist.mHead->next &&
		1 == dlist.mSize)
		PrintMessage();
}
#endif	// End LIST_INSERT_EMPTY

#if LIST_INSERT_HEAD
void DSA_TestSuite_Lab3::LinkedListInsertHead() {
	std::cout << "Testing Insert at head on non-empty list\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomVal = rand() % 100 + 1;
	list.push_front(randomVal);

	size_t memoryUsed = metrics.inUse;

	DList<int>::Iterator iter;
	iter.mCurr = dlist.mHead;

	dlist.Insert(iter, randomVal);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse < memoryUsed + sizeof(Node))
		PrintMessage("Node was not created");
	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("More than one node was created");
	if (!dlist.mHead)
		PrintMessage("Head is not pointing to a valid Node");
	else {
		if (dlist.mHead->data != randomVal)
			PrintMessage("Head's data is not set correctly");
		if (dlist.mHead->prev)
			PrintMessage("Head's prev is not set correctly");
		if (dlist.mHead->next != nodes[0])
			PrintMessage("Head's next is not set correctly");
	}
	if (iter.mCurr != dlist.mHead)
		PrintMessage("Iterator is not pointing to inserted Node");
	if (dlist.mSize != randomSize+1)
		PrintMessage("Size was not incremented");
	bool identValues = true;
	foriter = list.begin();
	for(Node* curr = dlist.mHead; curr; curr = curr->next, ++foriter) 
		if (curr->data != *foriter) {
			identValues = false;
			break;
		}

	// Testing for success
	if (memoryUsed + sizeof(Node) == metrics.inUse &&
		dlist.mHead && randomVal == dlist.mHead->data &&
		nodes[0] == dlist.mHead->next &&
		!dlist.mHead->prev &&
		randomSize + 1 == dlist.mSize &&
		identValues)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_INSERT_HEAD

#if LIST_INSERT
void DSA_TestSuite_Lab3::LinkedListInsertMiddle() {
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % (randomSize-1) + 1;

	std::cout << "Testing Insert in front of node " << randomIndex 
		<< " on non-empty list of size " << randomSize << "\n";

	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomVal = rand() % 100 + 1;
	
	foriter = list.begin();
	for (int i = 0; i < randomIndex; ++i)
		++foriter;
	list.insert(foriter, randomVal);

	size_t memoryUsed = metrics.inUse;

	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	dlist.Insert(iter, randomVal);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse < memoryUsed + sizeof(Node))
		PrintMessage("Node was not created");
	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("More than one node was created");
	if (nodes[randomIndex]->prev->data != randomVal)
		PrintMessage("Created node was not inserted before iterator");
	if (nodes[randomIndex - 1]->next->data != randomVal)
		PrintMessage("Created node was not linked properly in list");
	if (nodes[randomIndex]->prev->prev != nodes[randomIndex - 1])
		PrintMessage("Inserted node's prev is not pointing to correct node");
	if (nodes[randomIndex]->prev->next != nodes[randomIndex])
		PrintMessage("Inserted node's next is not pointing to correct node");
	if (dlist.mSize != randomSize + 1)
		PrintMessage("Size was not incremented");

	// Testing for success
	if (memoryUsed + sizeof(Node) == metrics.inUse &&
		nodes[randomIndex]->prev->data == randomVal &&
		nodes[randomIndex-1]->next->data == randomVal &&
		nodes[randomIndex]->prev->prev == nodes[randomIndex-1] &&
		nodes[randomIndex]->prev->next == nodes[randomIndex] &&
		randomSize + 1 == dlist.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_INSERT

#if LIST_ERASE_EMPTY
void DSA_TestSuite_Lab3::LinkedListEraseEmpty() {
	std::cout << "Testing Erase on an empty list\n";

	DList<int> dlist;
	DList<int>::Iterator iter;
	iter.mCurr = dlist.mHead;

	dlist.Erase(iter);

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	if (metrics.inUse > 0)
		PrintMessage("Erase should not be dynamically allocating any memory");
	if (metrics.inUse < 0)
		PrintMessage("Erase should not be deleting anything on an empty list");
	if (dlist.mHead)
		PrintMessage("Head should be pointing to null in an empty list");
	if(dlist.mTail)
		PrintMessage("Tail should be pointing to null in an empty list");

	// Testing for success
	if (!metrics.inUse && !dlist.mHead && !dlist.mTail)
		PrintMessage();
}
#endif	// End LIST_ERASE_EMPTY

#if LIST_ERASE_HEAD
void DSA_TestSuite_Lab3::LinkedListEraseHead() {
	std::cout << "Testing Erase on head\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	foriter = list.begin();
	list.erase(foriter);

	size_t memoryUsed = metrics.inUse;

	DList<int>::Iterator iter;
	iter.mCurr = dlist.mHead;

	dlist.Erase(iter);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse < memoryUsed - sizeof(Node))
		PrintMessage("More than one Node was deleted");
	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("There should be no dynamic allocations when erasing");
	if (dlist.mHead != nodes[1])
		PrintMessage("Head was not updated to next node in list");
	if (iter.mCurr != nodes[1])
		PrintMessage("Iterator was not updated to next node in list");
	if (dlist.mHead && dlist.mHead->prev)
		PrintMessage("Head's prev was not reset to null");
	if (dlist.mSize != randomSize - 1)
		PrintMessage("Size was not decremented");

	// Testing for success
	if (memoryUsed - sizeof(Node) == metrics.inUse &&
		dlist.mHead && dlist.mHead == nodes[1] &&
		dlist.mHead->prev == nullptr &&
		randomSize-1 == dlist.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ERASE_HEAD

#if LIST_ERASE_TAIL
void DSA_TestSuite_Lab3::LinkedListEraseTail() {
	std::cout << "Testing Erase on tail\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	list.pop_back();

	size_t memoryUsed = metrics.inUse;

	DList<int>::Iterator iter;
	iter.mCurr = dlist.mTail;

	dlist.Erase(iter);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse < memoryUsed - sizeof(Node))
		PrintMessage("More than one Node was deleted");
	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("There should be no dynamic allocations when erasing");
	if (dlist.mTail != nodes[randomSize-2])
		PrintMessage("Tail was not updated to prev node in list");
	if (iter.mCurr != nullptr)
		PrintMessage("After erasing tail, iterator should point to null");
	if (dlist.mSize != randomSize - 1)
		PrintMessage("Size was not decremented");

	// Testing for success
	if (memoryUsed - sizeof(Node) == metrics.inUse &&
		dlist.mTail && dlist.mTail == nodes[randomSize-2] &&
		randomSize - 1 == dlist.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ERASE_TAIL

#if LIST_ERASE
void DSA_TestSuite_Lab3::LinkedListEraseMiddle() {
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % (randomSize - 2) + 1;

	std::cout << "Testing Erase on node " << randomIndex
		<< " on non-empty list of size " << randomSize << "\n";

	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;

	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	foriter = list.begin();
	for (int i = 0; i < randomIndex; ++i)
		++foriter;
	list.erase(foriter);

	size_t memoryUsed = metrics.inUse;

	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	dlist.Erase(iter);

	if (verboseMode)
		DisplayList(list, dlist);

	if (metrics.inUse < memoryUsed - sizeof(Node))
		PrintMessage("More than one Node was deleted");
	if (metrics.inUse > memoryUsed + sizeof(Node))
		PrintMessage("There should be no dynamic allocations when erasing");
	if (nodes[randomIndex - 1]->next != nodes[randomIndex + 1])
		PrintMessage("Node before erased node was not tied to node after erased node");
	if (nodes[randomIndex + 1]->prev != nodes[randomIndex - 1])
		PrintMessage("Node after erased node was not tied to node before erased node");
	if(iter.mCurr != nodes[randomIndex+1])
		PrintMessage("Iterator was not updated to next node in list");
	if (dlist.mSize != randomSize - 1)
		PrintMessage("Size was not decremented");

	// Testing for success
	if (memoryUsed - sizeof(Node) == metrics.inUse &&
		nodes[randomIndex-1]->next == nodes[randomIndex+1] &&
		nodes[randomIndex+1]->prev == nodes[randomIndex-1] &&
		iter.mCurr == nodes[randomIndex+1] &&
		dlist.mSize == randomSize-1)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ERASE

#if LIST_ITER_BEGIN
void DSA_TestSuite_Lab3::LinkedListIterBegin() {
	std::cout << "Testing Begin\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;
	
	DList<int>::Iterator iter = dlist.Begin();

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n";
		std::cout << "curr:\t\t" << dlist.mHead << "\t" << iter.mCurr << '\n'
			<< "curr->data:\t" << dlist.mHead->data << "\t\t\t" << iter.mCurr->data << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr != dlist.mHead)
		PrintMessage("Iterator's current should be pointing to head");

	// Testing for success
	if (iter.mCurr == dlist.mHead)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_BEGIN

#if LIST_ITER_END
void DSA_TestSuite_Lab3::LinkedListIterEnd() {
	std::cout << "Testing End\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	DList<int>::Iterator iter = dlist.End();

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n";
		std::cout << "curr:\t\t" << (void*)nullptr << "\t" << iter.mCurr << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr)
		PrintMessage("Iterator's current should be pointing to null");

	// Testing for success
	if (!iter.mCurr)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_END

#if LIST_ITER_INCREMENT_PRE
void DSA_TestSuite_Lab3::LinkedListIterPreIncrement() {
	std::cout << "Testing Iterator pre-fix increment\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomIndex = (rand() % (randomSize-2)) + 1;
	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	DList<int>::Iterator nextIter = ++iter;

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "curr:\t\t" << nodes[randomIndex + 1] << "\t" << iter.mCurr << '\n'
			<< "curr->data\t" << nodes[randomIndex + 1]->data << "\t\t\t" << iter.mCurr->data << '\n'
			<< "return:\t\t" << nodes[randomIndex + 1] << "\t" << nextIter.mCurr << '\n'
			<< "return data:\t" << nodes[randomIndex + 1]->data << "\t\t\t" << nextIter.mCurr->data << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr != nodes[randomIndex + 1])
		PrintMessage("Current was not updated to next node");
	if (nextIter.mCurr != nodes[randomIndex + 1])
		PrintMessage("Did not return iterator pointing to next node");

	// Testing for success
	if (iter.mCurr == nodes[randomIndex + 1] &&
		nextIter.mCurr == nodes[randomIndex + 1])
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_INCREMENT_PRE

#if LIST_ITER_INCREMENT_POST
void DSA_TestSuite_Lab3::LinkedListIterPostIncrement() {
	std::cout << "Testing Iterator post-fix increment\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomIndex = (rand() % (randomSize - 2)) + 1;
	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	DList<int>::Iterator nextIter = iter++;

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "curr:\t\t" << nodes[randomIndex + 1] << "\t" << iter.mCurr << '\n'
			<< "curr->data\t" << nodes[randomIndex + 1]->data << "\t\t\t" << iter.mCurr->data << '\n'
			<< "return:\t\t" << nodes[randomIndex] << "\t" << nextIter.mCurr << '\n'
			<< "return data:\t" << nodes[randomIndex]->data << "\t\t\t" << nextIter.mCurr->data << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr != nodes[randomIndex + 1])
		PrintMessage("Current was not updated to next node");
	if (nextIter.mCurr != nodes[randomIndex])
		PrintMessage("Did not return iterator pointing to next node");

	// Testing for success
	if (iter.mCurr == nodes[randomIndex + 1] &&
		nextIter.mCurr == nodes[randomIndex])
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_INCREMENT_POST

#if LIST_ITER_DECREMENT_PRE
void DSA_TestSuite_Lab3::LinkedListIterPreDecrement() {
	std::cout << "Testing Iterator pre-fix decrement\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomIndex = (rand() % (randomSize - 2)) + 1;
	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	DList<int>::Iterator nextIter = --iter;

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "curr:\t\t" << nodes[randomIndex - 1] << "\t" << iter.mCurr << '\n'
			<< "curr->data\t" << nodes[randomIndex - 1]->data << "\t\t\t" << iter.mCurr->data << '\n'
			<< "return:\t\t" << nodes[randomIndex - 1] << "\t" << nextIter.mCurr << '\n'
			<< "return data:\t" << nodes[randomIndex - 1]->data << "\t\t\t" << nextIter.mCurr->data << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr != nodes[randomIndex - 1])
		PrintMessage("Current was not updated to next node");
	if (nextIter.mCurr != nodes[randomIndex - 1])
		PrintMessage("Did not return iterator pointing to next node");

	// Testing for success
	if (iter.mCurr == nodes[randomIndex - 1] &&
		nextIter.mCurr == nodes[randomIndex - 1])
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_DECREMENT_PRE

#if LIST_ITER_DECREMENT_POST
void DSA_TestSuite_Lab3::LinkedListIterPostDecrement() {
	std::cout << "Testing Iterator post-fix decrement\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> dlist;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	dlist.mHead = nodes[0];
	dlist.mTail = nodes[randomSize - 1];
	dlist.mSize = randomSize;

	int randomIndex = (rand() % (randomSize - 2)) + 1;
	DList<int>::Iterator iter;
	iter.mCurr = nodes[randomIndex];

	DList<int>::Iterator nextIter = iter--;

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "curr:\t\t" << nodes[randomIndex - 1] << "\t" << iter.mCurr << '\n'
			<< "curr->data\t" << nodes[randomIndex - 1]->data << "\t\t\t" << iter.mCurr->data << '\n'
			<< "return:\t\t" << nodes[randomIndex] << "\t" << nextIter.mCurr << '\n'
			<< "return data:\t" << nodes[randomIndex]->data << "\t\t\t" << nextIter.mCurr->data << '\n';

		std::cout << "DList:\t\t";
		for (Node* curr = dlist.mHead; curr; curr = curr->next)
			std::cout << '[' << curr->data << "]->";
		std::cout << "0\n";
	}

	if (iter.mCurr != nodes[randomIndex - 1])
		PrintMessage("Current was not updated to next node");
	if (nextIter.mCurr != nodes[randomIndex])
		PrintMessage("Did not return iterator pointing to next node");

	// Testing for success
	if (iter.mCurr == nodes[randomIndex - 1] &&
		nextIter.mCurr == nodes[randomIndex])
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ITER_DECREMENT_POST

#if LIST_COPY_CTOR_INT
void DSA_TestSuite_Lab3::LinkedListCopyConstructorInt() {
	std::cout << "Testing copy constructor with built-in type\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);
	 
	DList<int> original;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	original.mHead = nodes[0];
	original.mTail = nodes[randomSize - 1];
	original.mSize = randomSize;

	size_t memoryUsed = metrics.inUse;

	size_t memoryOfList = sizeof(Node)*randomSize;

	DList<int> copy(original);

	if (verboseMode)
		DisplayList(list, copy);

	if ((metrics.inUse - memoryUsed) < memoryOfList)
		PrintMessage("Not enough memory was allocated");
	if ((metrics.inUse - memoryUsed) > memoryOfList)
		PrintMessage("Too much memory was allocated"); 
	bool deepCopies = true;
	bool identValues = true;
	for (Node* origCurr = original.mHead, *copyCurr = copy.mHead; origCurr && copyCurr;
		origCurr = origCurr->next, copyCurr = copyCurr->next) {
		if (origCurr == copyCurr) {
			PrintMessage("One (or more) nodes have been shallow copied");
			deepCopies = false;
			break;
		}
		if (origCurr->data != copyCurr->data) {
			PrintMessage("One (or more) nodes did not copy the value");
			identValues = false;
			break;
		}
	}
	if (original.mSize != copy.mSize)
		PrintMessage("Copied list is not the same size as original list");


	// Testing for success
	if ((metrics.inUse - memoryUsed) == memoryOfList &&
		deepCopies && identValues &&
		original.mSize == copy.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_COPY_CTOR_INT

#if LIST_COPY_CTOR_USER_DEFINED
void DSA_TestSuite_Lab3::LinkedListCopyConstructorClass() {
	std::cout << "Testing copy constructor with user-defined type\n";

	std::string randString;

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<UserDefined> list;
	for (size_t i = 0; i < randomSize; ++i) {
		for (int i = 0; i < 3; ++i)
			randString += char(rand() % 26 + 97);
		list.push_back(UserDefined(randString, rand() % 100 + 1));
		randString.clear();
	}

	size_t memoryOfList = metrics.inUse;

	DList<UserDefined> original;
	// Creating a few Nodes
	DList<UserDefined>::Node** nodes = new DList<UserDefined>::Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new DList<UserDefined>::Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	original.mHead = nodes[0];
	original.mTail = nodes[randomSize - 1];
	original.mSize = randomSize;

	size_t memoryOfDList = metrics.inUse - memoryOfList - sizeof(DList<UserDefined>::Node*)*randomSize;

	DList<UserDefined> copy(original);

	if (verboseMode)
		DisplayList(list, copy);

	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*)*randomSize) < memoryOfDList)
		PrintMessage("Not enough memory was allocated");
	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*) * randomSize) > memoryOfDList)
		PrintMessage("Too much memory was allocated");
	bool deepCopies = true;
	bool identValues = true;
	for (DList<UserDefined>::Node* origCurr = original.mHead, *copyCurr = copy.mHead; origCurr && copyCurr;
		origCurr = origCurr->next, copyCurr = copyCurr->next) {
		if (origCurr == copyCurr) {
			PrintMessage("One (or more) nodes have been shallow copied");
			deepCopies = false;
			break;
		}
		if (origCurr->data != copyCurr->data) {
			PrintMessage("One (or more) nodes did not copy the value");
			identValues = false;
			break;
		}
	}
	if (original.mSize != copy.mSize)
		PrintMessage("Copied list is not the same size as original list");


	// Testing for success
	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*) * randomSize) == memoryOfDList &&
		deepCopies && identValues &&
		original.mSize == copy.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_COPY_CTOR_USER_DEFINED

#if LIST_ASSIGNMENT_OP_INT
void DSA_TestSuite_Lab3::LinkedListAssignmentOperatorInt() {
	std::cout << "Testing assignment operator with built-in type\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<int> list;
	for (size_t i = 0; i < randomSize; ++i)
		list.push_back(rand() % 100 + 1);

	DList<int> original;
	// Creating a few Nodes
	Node** nodes = new Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	original.mHead = nodes[0];
	original.mTail = nodes[randomSize - 1];
	original.mSize = randomSize;

	size_t memoryUsed = metrics.inUse;

	size_t memoryOfList = sizeof(Node) * randomSize;

	DList<int> assign;
	assign = original;

	if (verboseMode)
		DisplayList(list, assign);

	if ((metrics.inUse - memoryUsed) < memoryOfList)
		PrintMessage("Not enough memory was allocated");
	if ((metrics.inUse - memoryUsed) > memoryOfList)
		PrintMessage("Too much memory was allocated");
	bool deepCopies = true;
	bool identValues = true;
	for (Node* origCurr = original.mHead, *copyCurr = assign.mHead; origCurr && copyCurr;
		origCurr = origCurr->next, copyCurr = copyCurr->next) {
		if (origCurr == copyCurr) {
			PrintMessage("One (or more) nodes have been shallow copied");
			deepCopies = false;
			break;
		}
		if (origCurr->data != copyCurr->data) {
			PrintMessage("One (or more) nodes did not copy the value");
			identValues = false;
			break;
		}
	}
	if (original.mSize != assign.mSize)
		PrintMessage("Copied list is not the same size as original list");


	// Testing for success
	if ((metrics.inUse - memoryUsed) == memoryOfList &&
		deepCopies && identValues &&
		original.mSize == assign.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ASSIGNMENT_OP_INT

#if LIST_ASSIGNMENT_OP_USER_DEFINED
void DSA_TestSuite_Lab3::LinkedListAssignmentOperatorClass() {
	std::cout << "Testing assignment operator with user-defined type\n";

	std::string randString;

	size_t randomSize = size_t(rand() % 6) + 5;
	std::list<UserDefined> list;
	for (size_t i = 0; i < randomSize; ++i) {
		for (int i = 0; i < 3; ++i)
			randString += char(rand() % 26 + 97);
		list.push_back(UserDefined(randString, rand() % 100 + 1));
		randString.clear();
	}

	size_t memoryOfList = metrics.inUse;

	DList<UserDefined> original;
	// Creating a few Nodes
	DList<UserDefined>::Node** nodes = new DList<UserDefined>::Node * [randomSize];
	// Allocating the indivual nodes
	auto foriter = list.begin();
	for (size_t i = 0; i < randomSize; ++i, ++foriter)
		nodes[i] = new DList<UserDefined>::Node(*foriter);
	// Creating the linked list
	nodes[0]->prev = nullptr;
	nodes[randomSize - 1]->next = nullptr;
	for (size_t i = 0; i < randomSize - 1; ++i)
		nodes[i]->next = nodes[i + 1];
	for (size_t i = randomSize - 1; i > 0; --i)
		nodes[i]->prev = nodes[i - 1];

	original.mHead = nodes[0];
	original.mTail = nodes[randomSize - 1];
	original.mSize = randomSize;

	size_t memoryOfDList = metrics.inUse - memoryOfList - sizeof(DList<UserDefined>::Node*) * randomSize;

	DList<UserDefined> assign;
	assign = original;

	if (verboseMode)
		DisplayList(list, assign);

	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*) * randomSize) < memoryOfDList)
		PrintMessage("Not enough memory was allocated");
	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*) * randomSize) > memoryOfDList)
		PrintMessage("Too much memory was allocated");
	bool deepCopies = true;
	bool identValues = true;
	for (DList<UserDefined>::Node* origCurr = original.mHead, *copyCurr = assign.mHead; origCurr && copyCurr;
		origCurr = origCurr->next, copyCurr = copyCurr->next) {
		if (origCurr == copyCurr) {
			PrintMessage("One (or more) nodes have been shallow copied");
			deepCopies = false;
			break;
		}
		if (origCurr->data != copyCurr->data) {
			PrintMessage("One (or more) nodes did not copy the value");
			identValues = false;
			break;
		}
	}
	if (original.mSize != assign.mSize)
		PrintMessage("Copied list is not the same size as original list");


	// Testing for success
	if ((metrics.inUse - memoryOfList - memoryOfDList - sizeof(DList<UserDefined>::Node*) * randomSize) == memoryOfDList &&
		deepCopies && identValues &&
		original.mSize == assign.mSize)
		PrintMessage();

	delete[] nodes;
}
#endif	// End LIST_ASSIGNMENT_OP_USER_DEFINED
#endif	// End LAB_3