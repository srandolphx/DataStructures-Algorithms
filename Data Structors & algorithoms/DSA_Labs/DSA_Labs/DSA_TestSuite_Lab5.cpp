/*
File:			DSA_TestSuite_Lab5.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		01.07.2021
Last Modified:	02.26.2021
Purpose:		Definitions of Lab5 Unit Tests for Dictionary
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <iostream>
#include "DSA_TestSuite_Lab5.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

#define SIZEOFEMPTYLIST 64
#define SIZEOFLISTNODE	24
const int numPrimeBuckets = 6;
const size_t primeBuckets[numPrimeBuckets] = { 11, 13, 17, 19, 23, 29 };
int randomBuckets = -1;

#if LAB_5
unsigned int DSA_TestSuite_Lab5::BadHash(const float& _f) {
	return unsigned int(_f * 10) % primeBuckets[randomBuckets];
}

float RandomFloat() {
	return (rand() % 100) + float(rand() % 10) / 100;
}

// Populates dictionary with random values in a few buckets using a simple hash function
DSA_TestSuite_Lab5::DictionaryWithValues DSA_TestSuite_Lab5::GenerateDictionary() {
	DictionaryWithValues dictWithValues;
	dictWithValues.size = primeBuckets[randomBuckets];
	dictWithValues.values = new float[dictWithValues.size];
	dictWithValues.dict = new myDict(dictWithValues.size, BadHash);

	// Generating random values and storing in dict
	int currBucket = 0;
	for (size_t i = 0; i < dictWithValues.size; ++i) {
		dictWithValues.values[i] = RandomFloat();
		currBucket = int(dictWithValues.values[i] * 10) % primeBuckets[randomBuckets];

		dictWithValues.dict->mTable[currBucket].push_back(
			myPair(dictWithValues.values[i], dictWithValues.values[i]*2));
	}

	return dictWithValues;
}

void DSA_TestSuite_Lab5::DisplayDictionary(const myDict& _dict) {
	std::cout << "numBuckets:\t" << _dict.mNumBuckets << '\n'
		<< "hashFunc:\t" << _dict.mHashFunc << '\n'
		<< "buckets contents:\n";
	for (size_t i = 0; i < _dict.mNumBuckets; ++i) {
		std::cout << i << ":\t";
		if (_dict.mTable[i].size() > 0) {
			for (auto iter = _dict.mTable[i].begin(); iter != _dict.mTable[i].end(); ++iter)
				std::cout << "[" << iter->key << "," << iter->value << "]\t";
		}
		else
			std::cout << "empty";
		std::cout << '\n';
	}
 }

#if DICT_CTOR
void DSA_TestSuite_Lab5::DictConstructor() {
	std::cout << "Testing constructor\n";


	const int randomBuckets = rand() % 11 + 10;
	myDict dict(randomBuckets, BadHash);

	if (verboseMode) {
		std::cout << "\t\tTable\t\t\tNumBuckets\tHashFunc\n"
			<< "Expected\t" << "valid address" << "\t\t" << randomBuckets << "\t\t" << BadHash << '\n'
			<< "Yours\t\t" << dict.mTable << "\t" << dict.mNumBuckets << "\t\t" << dict.mHashFunc << '\n';
	}

	if (!dict.mTable)
		PrintMessage("Table should not be null");
	if (metrics.inUse != (SIZEOFEMPTYLIST * randomBuckets) + sizeof(void*))
		PrintMessage("Table is not allocated to the correct size");
	if (dict.mNumBuckets != randomBuckets)
		PrintMessage("numBuckets has incorrect value");
	if (dict.mHashFunc != BadHash)
		PrintMessage("hashFunc is not pointing to valid function");

	// Testing for success
	if (metrics.inUse == (SIZEOFEMPTYLIST * randomBuckets) + sizeof(void*) &&
		randomBuckets == dict.mNumBuckets &&
		BadHash == dict.mHashFunc)
		PrintMessage();
}
#endif	// End DICT_CTOR

#if DICT_PAIR_CTOR
void DSA_TestSuite_Lab5::DictPairConstructor() {
	std::cout << "Testing Pair constructor\n";

	const float randomFloat = rand() % 100 + (float(rand() % 10) / 10);

	myPair pair(randomFloat, randomFloat * 2);

	if (verboseMode) {
		std::cout << "\t\tKey\tValue\n"
			<< "Expected\t" << randomFloat << '\t' << randomFloat * 2 << '\n'
			<< "Yours\t\t" << pair.key << '\t' << pair.value << '\n';
	}

	if (pair.key != randomFloat)
		PrintMessage("Key has incorrect value");
	if (pair.value != randomFloat * 2)
		PrintMessage("Value has incorrect value");

	// Testing for success
	if (randomFloat == pair.key &&
		randomFloat * 2 == pair.value)
		PrintMessage();
}
#endif	// End DICT_PAIR_CTOR

#if DICT_DTOR
void DSA_TestSuite_Lab5::DictDestructor() {
	std::cout << "Testing destructor\n";

	myDict* dict = new myDict(size_t(rand() % 10) + 1, BadHash);
	
	delete dict;
	
	if (verboseMode)
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (metrics.inUse != 0)
		PrintMessage("Not all dynamic memory was freed");

	// Testing for success
	if (!metrics.inUse)
		PrintMessage();
}
#endif	//End DICT_DTOR

#if DICT_COPY_CTOR
void DSA_TestSuite_Lab5::DictCopyConstructor() {
	std::cout << "Testing copy constructor\n";

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* original = dictWithValues.dict;
	bool correctBucketSize = true, correctItems = true;
	std::list<myPair> originalBucket;

	size_t memoryOfList = metrics.inUse - (sizeof(float) * dictWithValues.size) - SIZEOFEMPTYLIST;

	// Calling copy constructor
	myDict copy(*original);

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayDictionary(*dictWithValues.dict);
		std::cout << "\t\tYours\n";
		DisplayDictionary(copy);
	}


	bool correctMemory = true;
	if ((metrics.inUse != ((memoryOfList * 2) + (sizeof(float) * dictWithValues.size)) + SIZEOFEMPTYLIST))
		correctMemory = false;

	// Error tests
	if (copy.mTable == original->mTable)
		PrintMessage("Table is using a shallow copy");
	if (!correctMemory)
		PrintMessage("Incorrect amount of memory allocated");
	if (copy.mNumBuckets != original->mNumBuckets)
		PrintMessage("numBuckets has incorrect value");
	if (copy.mHashFunc != original->mHashFunc)
		PrintMessage("hashFunc is not pointing to correct function");
	
	for (size_t i = 0; i < primeBuckets[randomBuckets]; ++i) {
		// Checking each bucket to make sure it has the correct number of elements
		if (original->mTable[i].size() != copy.mTable[i].size()) {
			PrintMessage("Size of one or more buckets is incorrect");
			correctBucketSize = false;
			break;
		}

		originalBucket = original->mTable[i];
		
		// Checking to make sure each individual bucket has the correct values
		for (auto copyIter = copy.mTable[i].begin(); copyIter != copy.mTable[i].end(); ++copyIter) {
			if (std::find(originalBucket.begin(), originalBucket.end(), *copyIter) == originalBucket.end()) {
				PrintMessage("One or more items were not found in correct bucket");
				correctItems = false;
				break;
			}
		}
	}

	// Testing for success
	if (copy.mTable != original->mTable &&
		correctMemory &&
		copy.mNumBuckets == original->mNumBuckets &&
		copy.mHashFunc == original->mHashFunc &&
		correctBucketSize && correctItems)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_COPY_CTOR

#if DICT_ASSIGNMENT_OP
void DSA_TestSuite_Lab5::DictAssignmentOperator() {
	std::cout << "Testing assignment operator\n";

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();

	myDict* original = dictWithValues.dict;
	bool correctBucketSize = true, correctItems = true;
	std::list<myPair> originalBucket;

	myDict assign(100, nullptr);

	size_t memoryUsed = metrics.inUse;

	// Calling assignment operator
	assign = *original;

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayDictionary(*dictWithValues.dict);
		std::cout << "\t\tYours\n";
		DisplayDictionary(assign);
	}

	// Error tests
	if (assign.mTable == original->mTable)
		PrintMessage("Table is using a shallow copy");
	if (metrics.inUse > memoryUsed)
		PrintMessage("Old table's memory was not cleaned up before re-allocating");
	if (assign.mNumBuckets != original->mNumBuckets)
		PrintMessage("numBuckets has incorrect value");
	if (assign.mHashFunc != original->mHashFunc)
		PrintMessage("hashFunc is not pointing to correct function");

	for (size_t i = 0; i < primeBuckets[randomBuckets]; ++i) {
		// Checking each bucket to make sure it has the correct number of elements
		if (original->mTable[i].size() != assign.mTable[i].size()) {
			PrintMessage("Size of one or more buckets is incorrect");
			correctBucketSize = false;
			break;
		}

		originalBucket = original->mTable[i];

		// Checking to make sure each individual bucket has the correct values
		for (auto copyIter = assign.mTable[i].begin(); copyIter != assign.mTable[i].end(); ++copyIter) {
			if (std::find(originalBucket.begin(), originalBucket.end(), *copyIter) == originalBucket.end()) {
				PrintMessage("One or more items were not found in correct bucket");
				correctItems = false;
				break;
			}
		}
	}

	// Testing for success
	if (assign.mTable != original->mTable &&
		metrics.inUse < memoryUsed &&
		assign.mNumBuckets == original->mNumBuckets &&
		assign.mHashFunc == original->mHashFunc &&
		correctBucketSize && correctItems)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_ASSIGNMENT_OP

#if DICT_CLEAR
void DSA_TestSuite_Lab5::DictClear() {
	std::cout << "Testing Clear method\n";

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* dict = dictWithValues.dict;
	bool bucketsCleared = true;

	size_t memoryUsed = metrics.inUse;
	size_t memoryAfterClear = metrics.inUse - (dictWithValues.size * SIZEOFLISTNODE);

	dict->Clear();

	if (verboseMode) {
		std::cout << "No additional information to display for this test\n";
	}

	// Error tests
	if (nullptr == dict->mTable)
		PrintMessage("Table should not be deleted");
	if (metrics.inUse != memoryAfterClear)
		PrintMessage("No memory should be manually allocated/deleted");
	if (dictWithValues.size != dict->mNumBuckets)
		PrintMessage("numBuckets should not be reset");
	if (BadHash != dict->mHashFunc)
		PrintMessage("hashFunc should not be reset");
	for(size_t i = 0; i < dict->mNumBuckets; ++i)
		if (dict->mTable[i].size() != 0) {
			PrintMessage("One or more buckets has a size greater than zero");
			bucketsCleared = false;
			break;
		}

	// Testing for success
	if (dict->mTable != nullptr &&
		metrics.inUse == memoryAfterClear &&
		dict->mNumBuckets == dictWithValues.size &&
		dict->mHashFunc == BadHash &&
		bucketsCleared)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_CLEAR

#if DICT_INSERT
void DSA_TestSuite_Lab5::DictInsert() {
	std::cout << "Testing Insert method (new key)\n";

	randomBuckets = rand() % numPrimeBuckets;
	myDict dict(primeBuckets[randomBuckets], BadHash);
	unsigned int correctBucket;
	bool found = false;
	float floatKey = RandomFloat();
	myPair foundPair(0,0);

	// Calling Insert
	dict.Insert(floatKey, floatKey * 2);

	if (verboseMode) {
		std::cout << "Adding [" << floatKey << "," << floatKey * 2 << "] to bucket #" << BadHash(floatKey) << '\n';
		DisplayDictionary(dict);
	}

	// Using hash function to get bucket
	correctBucket = BadHash(floatKey);

	// Iterating through bucket
	for (std::list<myPair>::const_iterator iter = dict.mTable[correctBucket].begin();
		iter != dict.mTable[correctBucket].end(); ++iter) {
		if (iter->key == floatKey) {
			found = true;
			foundPair = *iter;
			break;
		}
	}

	// Error tests
	if (!found)
		PrintMessage("Data was not found in correct bucket");
	if (foundPair.key != floatKey)
		PrintMessage("Key has incorrect value");
	if (foundPair.value != floatKey * 2)
		PrintMessage("Value has incorrect value");

	// Success
	if (found &&
		foundPair.key == floatKey &&
		foundPair.value == floatKey * 2)
		PrintMessage();
}
#endif	// End DICT_INSERT

#if DICT_INSERT_EXISTING
void DSA_TestSuite_Lab5::DictInsertOverwrite() {
	std::cout << "Testing Insert method (existing key)\n";

	randomBuckets = rand() % numPrimeBuckets;
	myDict dict(primeBuckets[randomBuckets], BadHash);
	unsigned int correctBucket;
	bool found = false;
	float floatKey = RandomFloat();
	myPair foundPair(0, 0);

	// Calling Insert
	dict.Insert(floatKey, floatKey * 2);
	// Overwriting same key
	dict.Insert(floatKey, floatKey * 3);

	if (verboseMode) {
		std::cout << "Overwriting [" << floatKey << "," << floatKey * 2 << "] in bucket #" << BadHash(floatKey) 
			<< " with new key " << floatKey*3 << '\n';
		DisplayDictionary(dict);
	}

	// Using hash function to get bucket
	correctBucket = BadHash(floatKey);

	// Iterating through bucket
	for (std::list<myPair>::const_iterator iter = dict.mTable[correctBucket].begin();
		iter != dict.mTable[correctBucket].end(); ++iter) {
		if (iter->key == floatKey && iter->value == floatKey*3) {
			found = true;
			foundPair = *iter;
			break;
		}
	}

	// Error tests
	if (!found)
		PrintMessage("Data was not found in correct bucket");
	if (foundPair.key != floatKey)
		PrintMessage("Key has incorrect value");
	if (foundPair.value != floatKey * 3)
		PrintMessage("Value has incorrect value");

	// Success
	if (found &&
		foundPair.key == floatKey &&
		foundPair.value == floatKey * 3)
		PrintMessage();
}
#endif	// End DICT_INSERT_EXISTING

#if DICT_FIND
void DSA_TestSuite_Lab5::DictFind() {
	

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* dict = dictWithValues.dict;

	float valueToSearchFor = dictWithValues.values[rand() % dictWithValues.size];

	std::cout << "Testing Find method for key " << valueToSearchFor << " (found)\n";

	// Searching for key
	const float* result = dict->Find(valueToSearchFor);

	if (verboseMode) {
		DisplayDictionary(*dict);
	}

	// Error testing
	if (*result != valueToSearchFor * 2)
		PrintMessage("Find did not return correct result (possibly not looking in correct bucket)");

	// Testing for success
	if (*result == valueToSearchFor * 2)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_FIND

#if DICT_FIND_NOT_FOUND
void DSA_TestSuite_Lab5::DictFindNotFound() {
	std::cout << "Testing Find method (not found)\n";

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* dict = dictWithValues.dict;

	float valueToSearchFor = -1;

	// Searching for key
	const float* result = dict->Find(valueToSearchFor);

	if (verboseMode) {
		std::cout << "No additional information to display for this test\n";
	}

	// Error testing
	if (result != nullptr)
		PrintMessage("Find should return nullptr on not found");

	// Testing for success
	if (nullptr == result)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_FIND_NOT_FOUND

#if DICT_REMOVE
void DSA_TestSuite_Lab5::DictRemove() {
	std::cout << "Testing Remove method (Key in Dictionary)\n";

	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* dict = dictWithValues.dict;

	float valueToRemove = dictWithValues.values[rand() % dictWithValues.size];
	int correctBucket = BadHash(valueToRemove);

	bool removed = dict->Remove(valueToRemove);
	bool removedFromBucket = true;

	if (verboseMode) {
		std::cout << "No additional information to display for this test\n";
	}

	// Error testing
	for (auto iter = dict->mTable[correctBucket].begin();
		iter != dict->mTable[correctBucket].end(); ++iter) {
		if (iter->key == valueToRemove) {
			PrintMessage("Pair was not removed from Dictionary)");
			removedFromBucket = false;
			break;
		}
	}

	// Testing for success
	if (removed && removedFromBucket)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_REMOVE

#if DICT_REMOVE_NOT_FOUND
void DSA_TestSuite_Lab5::DictRemoveNotFound() {
	std::cout << "Testing Remove method (Key not in Dictionary)\n"; 
	
	randomBuckets = rand() % numPrimeBuckets;
	DictionaryWithValues dictWithValues = GenerateDictionary();
	myDict* dict = dictWithValues.dict;

	float valueToRemove = -1;
	int correctBucket = BadHash(valueToRemove);

	bool removed = dict->Remove(valueToRemove);

	if (verboseMode) {
		std::cout << "No additional information to display for this test\n";
	}
	
	if (removed)
		PrintMessage("Remove returned incorrect result\n");

	// Testing for success
	if (!removed)
		PrintMessage();

	// Cleaning up temporaries
	delete dictWithValues.dict;
	delete[] dictWithValues.values;
}
#endif	// End DICT_REMOVE_NOT_FOUND
#endif	// End LAB_5