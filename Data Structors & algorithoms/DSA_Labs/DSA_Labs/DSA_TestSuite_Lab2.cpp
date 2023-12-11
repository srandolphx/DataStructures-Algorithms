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
#include "DSA_TestSuite_Lab2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#if LAB_2

// Creating a large array for some of the unit tests
IntWrapper* CreateLargeArray() {
	IntWrapper* largeArr = new IntWrapper[10000];
	int i = 0;
	std::ifstream ifl("numbers.txt");
	while (true) {
		ifl >> largeArr[i++].mValue;
		if (ifl.eof())
			break;
	}
	ifl.close();
	return largeArr;
}

#if LAB2_PALINDROME_NUMBER
void DSA_TestSuite_Lab2::CheckForPalindrome() {
	std::cout << "Testing to see if numbers are palindromes\n";

	int palindromeNumbers[8] = { 6, 55, 494, 7117, 45654, 123321, 7654567, 44566544 };
	int nonPalindromeNumbers[7] = { 12, 983, 6423, 29811, 239582, 5820183, 14826038 };
	bool success = true;

if (verboseMode)
	std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	// Test palindromes
	for (int i = 0; i < 8; ++i)
		if (IsPalindromeNumber(palindromeNumbers[i]) == false) {
			std::ostringstream oss;
			oss << palindromeNumbers[i] << " is not registering as a palindrome number";
			PrintMessage(oss.str().c_str());
			success = false;
		}

	// Testing non-palindromes
	for (int i = 0; i < 7; ++i)
		if (IsPalindromeNumber(nonPalindromeNumbers[i]) == true) {
			std::ostringstream oss;
			oss << nonPalindromeNumbers[i] << " is registering as a palindrome number";
			PrintMessage(oss.str().c_str());
			success = false;
		}


	// Success
	if (success)
		PrintMessage();
}
#endif	// End LAB2_PALINDROME_NUMBER

#if LAB2_VECTOR_FILL_FILE
void DSA_TestSuite_Lab2::VectorFillFromFile() {
	std::cout << "Testing filling vector from a file\n";

	IntWrapper* nums = CreateLargeArray();
	bool identValues = true;
	DSA_Lab2 vec;

	// Fill in vector from file
	vec.Fill("numbers.bin");

	if (verboseMode) {
		std::cout << "Only displaying partial array due to size (first 15 elements)\n";
		std::cout << "Expected array: ";
		for (size_t i = 0; i < 15; ++i)
			std::cout << nums[i] << ' ';
		std::cout << "\n";
		std::cout << "mValues vector: ";
		for (size_t i = 0; i < 15; ++i)
			std::cout << vec.mValues[i] << ' ';
		std::cout << "\n";
	}

	if (!vec.mValues.size())
		PrintMessage("No values were not added to vector");
	if (vec.mValues.size() && vec.mValues[0] == 10000)
		PrintMessage("File header was not read.  The first four bytes of the file stores the number of values in the file.");
	if (vec.mValues.size() != 10000)
		PrintMessage("Not all values were added to vector");
	for (size_t i = 0; i < vec.mValues.size(); ++i) {
		if (vec.mValues[i] != nums[i]) {
			PrintMessage("One (or more) values were not read/added to vector correctly");
			identValues = false;
			break;
		}
	}


	// Testing for success
	if (vec.mValues.size() == 10000 &&
		identValues)
		PrintMessage();

	// Cleanup
	delete[] nums;
}
#endif	// End LAB2_VECTOR_FILL_FILE

#if LAB2_VECTOR_FILL_ARRAY
void DSA_TestSuite_Lab2::VectorFillFromArray() {
	std::cout << "Testing filling vector from an array\n";

	DSA_Lab2 vec;
	
	size_t randomSize = size_t(rand() % 6) + 5;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i)
		randomVals[i] = rand() % 100 + 1;

	// Fill in vector from file
	vec.Fill(randomVals, randomSize);

	bool identValues = true;
	for (size_t i = 0; i < vec.mValues.size(); ++i) {
if (vec.mValues[i] != randomVals[i]) {

	identValues = false;
	break;
}
	}

	if (verboseMode) {
		std::cout << "Expected array: ";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << randomVals[i] << ' ';
		std::cout << "\n";
		std::cout << "mValues vector: ";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << vec.mValues[i] << ' ';
		std::cout << "\n";
	}

	if (!vec.mValues.size())
		PrintMessage("Values were not added to vector");
	if (vec.mValues.size() != randomSize)
		PrintMessage("Not all values were added to vector");
	if (!identValues)
		PrintMessage("One (or more) values were not read/added to vector correctly");


	// Testing for sucess
	if (vec.mValues.size() == randomSize &&
		identValues)
		PrintMessage();

	// Cleanup
	delete[] randomVals;
}
#endif	// End LAB2_VECTOR_FILL_ARRAY

#if LAB2_VECTOR_CLEAR
void DSA_TestSuite_Lab2::VectorClear() {
	std::cout << "Testing Clear method\n";

	DSA_Lab2 vec;

	// Adding a random number of elements into the vector
	size_t randomSize = size_t(rand() % 6) + 5;
	for (size_t i = 0; i < randomSize; ++i)
		vec.mValues.push_back(1);

	vec.Clear();

	if (verboseMode) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "size:\t\t" << 0 << "\t\t\t" << vec.mValues.size() << '\n'
			<< "capacity\t" << 0 << "\t\t\t" << vec.mValues.capacity() << '\n';
	}

	if (vec.mValues.size() != 0)
		PrintMessage("Vector was not fully cleared");
	if (vec.mValues.capacity() != 0)
		PrintMessage("Vector capacity was not reset");

	// Testing for success
	if (0 == vec.mValues.size() &&
		0 == vec.mValues.capacity())
		PrintMessage();
}
#endif	// End LAB2_VECTOR_CLEAR

#if LAB2_VECTOR_SORT_ASCENDING
void DSA_TestSuite_Lab2::VectorSortAscending() {
	std::cout << "Testing Sort in ascending order\n";

	DSA_Lab2 vec;

	size_t randomSize = size_t(rand() % 6) + 5;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i) {
		randomVals[i] = rand() % 100 + 1;
		vec.mValues.push_back(randomVals[i]);
	}

	vec.Sort(true);

	// Sort it
	for (size_t i = 0; i < randomSize - 1; ++i)
		for (size_t j = i + 1; j < randomSize; ++j)
			if (randomVals[j] < randomVals[i])
				std::swap(randomVals[j], randomVals[i]);

	if (verboseMode) {
		std::cout << "Expected Array:\t";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << randomVals[i] << ' ';
		std::cout << '\n';
		std::cout << "Your Array:\t";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << vec.mValues[i] << ' ';
		std::cout << '\n';
	}

	std::ifstream ifl("DSA_Lab2.h");
	std::string currLine;
	bool usesStdSort = false;
	while (true) {
		std::getline(ifl, currLine);
		if (currLine.find("int operator[]") != std::string::npos)
			break;

		if (currLine.find("sort(") != std::string::npos) {
			usesStdSort = true;
			break;
		}
	}
	ifl.close();
	if (!usesStdSort)
		PrintMessage("Does not use std::sort");

	bool sortedAscending = true;
	for (size_t i = 0; i < randomSize; ++i) {
		if (randomVals[i] != vec.mValues[i]) {
			sortedAscending = false;
			break;
		}
	}
	if (!sortedAscending)
		PrintMessage("Array is not sorted in ascending order");

	delete[] randomVals;

	// Testing for success
	if (usesStdSort &&
		sortedAscending)
		PrintMessage();

}
#endif	// End LAB2_VECTOR_SORT_ASCENDING

#if LAB2_VECTOR_SORT_DESCENDING
void DSA_TestSuite_Lab2::VectorSortDescending() {
	std::cout << "Testing Sort in descending order\n";

	DSA_Lab2 vec;

	size_t randomSize = size_t(rand() % 6) + 5;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i) {
		randomVals[i] = rand() % 100 + 1;
		vec.mValues.push_back(randomVals[i]);
	}

	vec.Sort(false);

	// Sort it
	for (size_t i = 0; i < randomSize - 1; ++i)
		for (size_t j = i + 1; j < randomSize; ++j)
			if (randomVals[j] > randomVals[i])
				std::swap(randomVals[j], randomVals[i]);

	if (verboseMode) {
		std::cout << "Expected Array:\t";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << randomVals[i] << ' ';
		std::cout << '\n';
		std::cout << "Your Array:\t";
		for (size_t i = 0; i < randomSize; ++i)
			std::cout << vec.mValues[i] << ' ';
		std::cout << '\n';
	}

	std::ifstream ifl("DSA_Lab2.h");
	std::string currLine;
	bool usesStdSort = false;
	while (true) {
		std::getline(ifl, currLine);
		if (currLine.find("int operator[]") != std::string::npos)
			break;

		if (currLine.find("sort(") != std::string::npos) {
			usesStdSort = true;
			break;
		}
	}
	ifl.close();
	if (!usesStdSort)
		PrintMessage("Does not use std::sort");

	bool sortedAscending = true;
	for (size_t i = 0; i < randomSize; ++i) {
		if (randomVals[i] != vec.mValues[i]) {
			sortedAscending = false;
			break;
		}
	}
	if (!sortedAscending)
		PrintMessage("Array is not sorted in descending order");

	delete[] randomVals;

	// Testing for success
	if (usesStdSort &&
		sortedAscending)
		PrintMessage();
}
#endif	// LAB2_VECTOR_SORT_DESCENDING

#if LAB2_VECTOR_BRACKETS
void DSA_TestSuite_Lab2::VectorIndexing() {
	DSA_Lab2 vec;
	
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % randomSize;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i) {
		randomVals[i] = rand() % 100 + 1;
		vec.mValues.push_back(randomVals[i]);
	}
	
	std::cout << "Testing [] indexing (using random index " << randomIndex << ")\n";

	if (verboseMode) {
		std::cout << "Expected return:\t" << randomVals[randomIndex] << '\n'
			<< "Your return:\t\t" << vec[randomIndex] << '\n';
	}

	std::ifstream ifl("DSA_Lab2.h");
	std::string currLine;
	bool usesBrackets = false;
	while (true) {
		std::getline(ifl, currLine);
		if (currLine.find("bool Contains") != std::string::npos)
			break;

		if (currLine.find("[_index]") != std::string::npos) {
			usesBrackets = true;
			break;
		}
	}
	ifl.close();
	if(!usesBrackets)
		PrintMessage("Does not use [] to return value at specified index");

	if (randomVals[randomIndex] != vec[randomIndex])
		PrintMessage("operator[] does not return correct value");

	// Testing for success
	if (usesBrackets &&
		randomVals[randomIndex] == vec[randomIndex])
		PrintMessage();

	delete[] randomVals;

}
#endif	LAB2_VECTOR_BRACKETS

#if LAB2_VECTOR_CONTAINS_TRUE
void DSA_TestSuite_Lab2::VectorContainsTrue() {
	DSA_Lab2 vec;

	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % randomSize;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i) {
		randomVals[i] = rand() % 100 + 1;
		vec.mValues.push_back(randomVals[i]);
	}

	std::cout << "Testing Contains for a value that is present (" << randomVals[randomIndex] 
		<< " is at index " << randomIndex << ")\n";

	if (verboseMode)
		std::cout << "No additional information to display for this test\n";

	bool contains = vec.Contains(randomVals[randomIndex]);

	delete[] randomVals;

	if (!contains)
		PrintMessage("Contains returned false when value was in vector");

	// Testing for success
	if (contains)
		PrintMessage();

}
#endif	// End LAB2_VECTOR_CONTAINS_TRUE

#if LAB2_VECTOR_CONTAINS_FALSE
void DSA_TestSuite_Lab2::VectorContainsFalse() {
	DSA_Lab2 vec;

	size_t randomSize = size_t(rand() % 6) + 5;
	int randomIndex = rand() % randomSize;
	unsigned int* randomVals = new unsigned int[randomSize];
	for (size_t i = 0; i < randomSize; ++i) {
		randomVals[i] = rand() % 100 + 1;
		vec.mValues.push_back(randomVals[i]);
	}
	int randomVal = rand()%100 + 101;

	std::cout << "Testing Contains for a value that is not present (" << randomVal << ")\n";

	if (verboseMode)
		std::cout << "No additional information to display for this test\n";

	bool contains = vec.Contains(randomVal);

	delete[] randomVals;

	if (contains)
		PrintMessage("Contains returned true when value was not in vector");

	// Testing for success
	if (!contains)
		PrintMessage();
}
#endif	// End LAB2_VECTOR_CONTAINS_FALSE

#if LAB2_VECTOR_MOVE_PALINDROME
void DSA_TestSuite_Lab2::VectorMovePalindrome() {
	std::cout << "Testing creating vector of palindromes\n";
	
	IntWrapper* nums = CreateLargeArray();

	const int palindromes[23] = {	190091,	245542,	39293,	276672,	473374,
											369963, 502205, 643346, 24942,	787787,
											45454,	69096,	39593,	572275,	602206,
											88588,	84148,	222222,	929929,	785587,
											281182,	3223,	40004
	};
	
	DSA_Lab2 vec;

	// Fill in the vector
	for (int i = 0; i < 10000; ++i)
		vec.mValues.push_back(nums[i]);

	vec.MovePalindromes();

	if (verboseMode)
		std::cout << "No additional information to display for this test\n";


	if (vec.mValues.size() != 9977) {
		PrintMessage("Palindrome values were not erased from mValues vector");
	}
	if (vec.mPalindromes.size() != 23) {
		PrintMessage("Palindrome values were not added to mPalindromes vector");
		}

	bool success = true;
	for (size_t i = 0; i < vec.mPalindromes.size(); ++i) {
		if (vec.mPalindromes[i] != palindromes[i]) {
			std::ostringstream oss;
			oss << "Palindrome number (" << palindromes[i] << ") was not found in mPalindromes vector";
			PrintMessage(oss.str().c_str());
			success = false;
			break;
		}
	}

	if (vec.mValues.size() == 9977 &&
		vec.mPalindromes.size() == 23 &&
		success)
		PrintMessage();

	// Clean up
	delete[] nums;
}
#endif	// End LAB2_VECTOR_MOVE_PALINDROME
#endif	// End LAB_2