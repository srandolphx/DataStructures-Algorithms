/*
File:			DSA_TestSuite_Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.30.2020
Last Modified:	02.26.2021
Purpose:		Definitions of Lab2 Unit Tests for DSA_Lab2
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include "DSA_TestSuite_GlobalFunctions.h"
#include "DSA_TestSuite_Lab4.h"
#include <iostream>
#include <vector>

#if LAB_4
#if LIST_QUEUE_ADD
void DSA_TestSuite_Lab4::ListQueueAdd() {
	std::cout << "Testing adding to a list using queue ordering\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand()%100+1) + (rand() % 100+1) / (float)100);

	DSA_Lab4 queue;

	queue.QueueOrderingAdd(&vec[0], randomSize);

	if (verboseMode) {
		std::cout << "Expected list:\t";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << "[" << vec[i] << "]->";
		std::cout << "0\n";
		std::cout << "Your list:\t";
		for (auto iter = queue.mList.begin(); iter != queue.mList.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	if(queue.mList.size() != randomSize)
		PrintMessage("Not all values were added to list\n");
	
	std::list<float>::iterator it = queue.mList.begin();
	bool queueOrdering = true;
	for (size_t i = 0; i < randomSize; ++i, ++it) {
		if (*it != vec[i]) {
			PrintMessage("One (or more) values were not added with queue ordering");
			queueOrdering = false;
			break;
		}
	}

	// Testing for success
	if (queue.mList.size() == randomSize &&
		queueOrdering)
		PrintMessage();
}
#endif	// End LIST_QUEUE_ADD

#if LIST_STACK_ADD
void DSA_TestSuite_Lab4::ListStackAdd() {
	std::cout << "Testing adding to a list using stack ordering\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	DSA_Lab4 stack;

	stack.StackOrderingAdd(&vec[0], randomSize);

	if (verboseMode) {
		std::cout << "Expected list:\t";
		for (int i = (int)randomSize-1; i >= 0; --i)
			std::cout << "[" << vec[i] << "]->";
		std::cout << "0\n";
		std::cout << "Your list:\t";
		for (auto iter = stack.mList.begin(); iter != stack.mList.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	if (stack.mList.size() != randomSize) 
		PrintMessage("Not all values were added to list\n");

	std::list<float>::iterator it = stack.mList.begin();
	bool stackOrdering = true;
	for (int i = (int)randomSize-1; i >= 0; --i, ++it) {
		float current = *it;
		if (current != vec[i]) {

			PrintMessage("One (or more) values were not added with stack ordering");
			stackOrdering = false;
			break;
		}
	}

	if(stack.mList.size() == randomSize &&
		stackOrdering)
		PrintMessage();
}
#endif	// End LIST_STACK_ADD

#if LIST_QUEUE_REMOVE
void DSA_TestSuite_Lab4::ListQueueRemove() {
	std::cout << "Testing removing from a list using queue ordering\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	DSA_Lab4 queue;

	queue.mList = std::list<float>(&vec[0], &vec[0] + randomSize);

	const float pop = queue.QueueOrderingRemove();

	if (verboseMode) {
		std::cout << "Expected return:\t" << vec[0] << '\n'
			<< "Your return:\t\t" << pop << '\n';
	}

	if (pop != vec[0])
		PrintMessage("Correct value was not returned (not queue ordering)");
	if (queue.mList.size() != randomSize - 1)
		PrintMessage("Value was not removed from the list");

	// Testing for success
	if (pop == vec[0] && queue.mList.size() == randomSize - 1)
		PrintMessage();
}
#endif	// End LIST_QUEUE_REMOVE

#if LIST_STACK_REMOVE
void DSA_TestSuite_Lab4::ListStackRemove() {
	std::cout << "Testing removing from a list using stack ordering\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	DSA_Lab4 stack;

	stack.mList = std::list<float>(&vec[0], &vec[0] + randomSize);

	const float pop = stack.StackOrderingRemove();

	if (verboseMode) {
		std::cout << "Expected return:\t" << vec[0] << '\n'
			<< "Your return:\t\t" << pop << '\n';
	}

	if (pop != vec[0])
		PrintMessage("Correct value was not returned (not stack ordering)");
	if (stack.mList.size() != randomSize - 1)
		PrintMessage("Value was not removed from list");

	// Testing for success
	if (pop == vec[0] && stack.mList.size() == randomSize - 1)
		PrintMessage();
}
#endif	// End LIST_STACK_REMOVE

#if LIST_INSERT_INDEX
void DSA_TestSuite_Lab4::ListInsertIndex() {
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % randomSize;
	
	std::cout << "Testing inserting into a list at index " << randomIndex << "\n";

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	DSA_Lab4 lst;
	lst.mList = std::list<float>(vec.begin(), vec.end());

	float randomValue = (rand() % 100 + 1) + (rand() % 100 + 1) / (float)100;

	auto iter = vec.begin();
	vec.insert(iter+randomIndex, randomValue);

	lst.Insert(randomIndex, randomValue);

	if (verboseMode) {
		std::cout << "Expected list:\t";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << "[" << vec[i] << "]->";
		std::cout << "0\n";
		std::cout << "Your list:\t";
		for (auto iter = lst.mList.begin(); iter != lst.mList.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	if (std::find(lst.mList.begin(), lst.mList.end(), randomValue) == lst.mList.end())
		PrintMessage("Value was added to list at all");
	auto listIter = lst.mList.begin();
	for (int i = 0; i < randomIndex; ++i)
		listIter++;
	if (*listIter != vec[randomIndex])
		PrintMessage("Value was not added at correct location in list");

	// Testing for success
	if (*listIter == vec[randomIndex])
		PrintMessage();
}
#endif	// End LIST_INSERT_INDEX

#if LIST_INSERT_ITER
void DSA_TestSuite_Lab4::ListInsertIterator() {
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % randomSize;

	std::cout << "Testing inserting into a list at index " << randomIndex << "\n";

	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	DSA_Lab4 lst;
	lst.mList = std::list<float>(vec.begin(), vec.end());

	float randomValue = (rand() % 100 + 1) + (rand() % 100 + 1) / (float)100;

	auto vecIter = vec.begin();
	vec.insert(vecIter + randomIndex, randomValue);

	auto listIter = lst.mList.begin();
	for (int i = 0; i < randomIndex; ++i, ++listIter);
	lst.Insert(listIter, randomValue);

	if (verboseMode) {
		std::cout << "Expected list:\t";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << "[" << vec[i] << "]->";
		std::cout << "0\n";
		std::cout << "Your list:\t";
		for (auto iter = lst.mList.begin(); iter != lst.mList.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	if (std::find(lst.mList.begin(), lst.mList.end(), randomValue) == lst.mList.end())
		PrintMessage("Value was added to list at all");
	listIter = lst.mList.begin();
	for (int i = 0; i < randomIndex; ++i)
		listIter++;
	if (*listIter != vec[randomIndex])
		PrintMessage("Value was not added at correct location in list");

	// Testing for success
	if (*listIter == vec[randomIndex])
		PrintMessage();
}
#endif	// End LIST_INSERT_ITER

#if LIST_REMOVE_DECIMAL
float randomDecimal = ((rand() % 75) + 25) / 100.0f;
bool LessDec(float _val) {
	return (_val - floorf(_val) > randomDecimal);
}

void DSA_TestSuite_Lab4::ListRemoveDecimal() {
	randomDecimal = ((rand() % 75) + 25) / 100.0f;
	std::cout << "Testing removing values with decimal > " << randomDecimal << "\n";

	size_t randomSize = size_t(rand() % 6) + 5;
	std::vector<float> vec;
	for (size_t i = 0; i < randomSize; ++i)
		vec.push_back((rand() % 100 + 1) + (rand() % 100 + 1) / (float)100);

	size_t origSize = vec.size();

	DSA_Lab4 lst;
	lst.mList = std::list<float>(&vec[0], &vec[0] + randomSize);

	if (verboseMode) {
		std::cout << "Your List Before:\t";
		for (auto iter = vec.begin(); iter != vec.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	vec.erase(std::remove_if(vec.begin(), vec.end(), LessDec), vec.end());
	int removed = lst.RemoveDecimalGreater(randomDecimal);

	if (verboseMode) {
		std::cout << "Expected List After:\t";
		for (auto iter = vec.begin(); iter != vec.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
		std::cout << "Your List After:\t";
		for (auto iter = lst.mList.begin(); iter != lst.mList.end(); ++iter)
			std::cout << "[" << *iter << "]->";
		std::cout << "0\n";
	}

	if (lst.mList.size() != vec.size())
		PrintMessage("Not all values were removed");
	if (removed != origSize - vec.size())
		PrintMessage("Method did not return number of values removed");

	bool valuesRemoved = true;

	size_t i = 0;
	for(auto iter = lst.mList.begin(); iter != lst.mList.end(); ++iter, ++i)
		if (*iter != vec[i]) {
			PrintMessage("Lists are not the same (value was not removed?)");
			valuesRemoved = false;
			break;
		}

	// Testing for success
	if (lst.mList.size() == vec.size() &&
		removed == origSize - vec.size() &&
		valuesRemoved)
		PrintMessage();
}
#endif	// End LIST_REMOVE_DECIMAL
#endif	// End LAB_4