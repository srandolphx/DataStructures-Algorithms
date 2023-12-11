/*
File:			DSA_TestSuite_Lab1.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	11.30.2020
Purpose:		Definitions of Lab1 Unit Tests for DynArray
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <string>
#include <sstream>
#include <iostream>
#include "DSA_TestSuite_Lab1.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

#if LAB_1
#if LAB1_DYNARRAY_DEFAULT_CTOR
void DSA_TestSuite_Lab1::DynArrayDefaultConstructorNoArgs() {
	std::cout << "Testing default constructor (with no arguments)\n";

	// Creating object using default constructor
	DynArray<int> da;

	if (verboseMode)
		VerboseOutput_DynArray("nullptr", 0, 0, da);

	if (metrics.inUse != 0)
		PrintMessage("No memory should be allocated");
	if (da.mArray != nullptr)
		PrintMessage("Array should be nullptr");
	if (da.mCapacity)
		PrintMessage("Capacity is not correct value");
	if (da.mSize)
		PrintMessage("Size is not correct value");

	// Testing for success
	if (!da.mSize && !da.mCapacity && !da.mArray)
		PrintMessage();

}
#endif	// End LAB1_DYNARRAY_DEFAULT_CTOR

#if LAB1_DYNARRAY_CONSTRUCTOR_WITH_ARGS
void DSA_TestSuite_Lab1::DynArrayDefaultConstructorWithArgs() {
	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;

	std::cout << "Testing default constructor (passing a starting capacity of " << randomSize << ")\n";

	// Creating object and passing value
	DynArray<int> da(randomSize);

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", randomSize, 0, da);

	if (metrics.inUse != sizeof(int) * randomSize)
		PrintMessage("Incorrect amount of memory allocated");
	if (da.mArray == nullptr)
		PrintMessage("Array should not be null");
	if (da.mCapacity != randomSize)
		PrintMessage("Capacity is not correct value");
	if (da.mSize)
		PrintMessage("Size is not correct value");



	// Testing for success
	if (!da.mSize &&
		da.mCapacity == randomSize &&
		da.mArray != nullptr &&
		metrics.inUse == (sizeof(int) * randomSize))
		PrintMessage();

}
#endif	// End LAB1_DYNARRAY_CONSTRUCTOR_WITH_ARGS

#if LAB1_DYNARRAY_DTOR
void DSA_TestSuite_Lab1::DynArrayDestructor() {
	std::cout << "Testing destructor\n";

	DynArray<int>* da = new DynArray<int>;
	da->mArray = new int[size_t(rand() % 10) + 1];
	
	delete da;

	if(verboseMode) 
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (metrics.inUse != 0) 
		PrintMessage("Not all dynamic memory was freed");
	
	// Testing for success
	if (!metrics.inUse)
		PrintMessage();
}

#endif	// End LAB1_DYNARRAY_DTOR

#if LAB1_DYNARRAY_COPY_CTOR_BUILT_IN
void DSA_TestSuite_Lab1::DynArrayCopyConstructorInt() {
	std::cout << "Testing copy constructor with built-in type\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;

	// Creating object to copy from
	DynArray<int> original;

	// Manually setting data members
	original.mArray = new int[randomSize];
	for (size_t i = 0; i < randomSize; ++i)		// Filling array with random values
		original.mArray[i] = rand() % 50;
	original.mCapacity = randomSize * 2;		// Setting a capacity that is not full
	original.mSize = randomSize;				// Setting the size to the number of elements used

	// Copy constructor call
	DynArray<int> copy = original;

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", original.mCapacity, original.mSize, copy, original.mArray);

	if (copy.mArray == original.mArray)
		PrintMessage("Shallow copy of array.   Whenever your class has dynamic memory, you *MUST* deep copy!");
	if (metrics.inUse != sizeof(int) * randomSize * 3)	// * 3 due to temp array in this method, and then da's mCapacity is 2x that
		PrintMessage("Incorrect amount of memory allocated");
	if (copy.mSize != original.mSize)
		PrintMessage("Size is not correct value");
	if (copy.mCapacity != original.mCapacity)
		PrintMessage("Capacity is not correct value");
	for (size_t i = 0; i < randomSize; ++i)
		if (copy.mArray[i] != original.mArray[i]) {
			PrintMessage("Values in array are not equal");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (copy.mArray[i] != original.mArray[i]) {
			identValues = false;
			break;
		}

	if (copy.mArray != original.mArray &&
		copy.mSize == original.mSize &&
		copy.mCapacity == original.mCapacity &&
		metrics.inUse == sizeof(int) * randomSize * 3 &&
		identValues)
		PrintMessage();

}
#endif	// LAB1_DYNARRAY_COPY_CTOR_BUILT_IN

#if LAB1_DYNARRAY_COPY_CTOR_CLASS
void DSA_TestSuite_Lab1::DynArrayCopyConstructorClass() {
	std::cout << "Testing copy constructor with user-defined type\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;

	// Creating object to copy from
	DynArray<UserDefined> original;

	// Manually setting data members
	original.mArray = new UserDefined[randomSize];
	int randVal;
	std::string* randString = new std::string;
	for (size_t i = 0; i < randomSize; ++i) {	// Filling array with random values
		randVal = rand() % 50;
		for (int i = 0; i < 3; ++i)
			*randString += char(rand() % 26 + 97);
		original.mArray[i].mString = *randString;
		randString->clear();
		original.mArray[i].mValue = randVal;
	}
	delete randString;
	original.mCapacity = randomSize;
	original.mSize = randomSize;			// Setting the size to the number of elements used

	size_t memoryPerObject = metrics.inUse;

	// Copy constructor call
	DynArray<UserDefined> copy = original;

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", original.mCapacity, original.mSize, copy, original.mArray);

	if (copy.mArray == original.mArray)
		PrintMessage("Shallow copy of array.   Whenever your class has dynamic memory, you *MUST* deep copy!");
	if (metrics.inUse != memoryPerObject * 2)
		PrintMessage("Incorrect amount of memory allocated");
	if (copy.mSize != original.mSize)
		PrintMessage("Size is not correct value");
	if (copy.mCapacity != original.mCapacity)
		PrintMessage("Capacity is not correct value");
	for (size_t i = 0; i < randomSize; ++i)
		if (copy.mArray[i] != original.mArray[i]) {
			PrintMessage("Values in array are not equal");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (copy.mArray[i] != original.mArray[i]) {
			identValues = false;
			break;
		}

	if (copy.mArray != original.mArray &&
		copy.mSize == original.mSize &&
		copy.mCapacity == original.mCapacity &&
		metrics.inUse == memoryPerObject * 2 &&
		identValues)
		PrintMessage();
}
#endif	// End LAB1_DYNARRAY_COPY_CTOR_CLASS

#if LAB1_DYNARRAY_ASSIGNMENT_BUILT_IN
void DSA_TestSuite_Lab1::DynArrayAssignmentOperatorInt() {
	std::cout << "Testing assignment operator with built-in type\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;

	// Creating object to assign from
	DynArray<int> original;

	// Manually setting data members
	original.mArray = new int[randomSize];
	for (size_t i = 0; i < randomSize; ++i)		// Filling array with random values
		original.mArray[i] = rand() % 50;
	original.mCapacity = randomSize * 2;		// Setting a capacity that is not full
	original.mSize = randomSize;				// Setting the size to the number of elements used


	DynArray<int> assign;
	// Assignment operator call
	assign = original;

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", original.mCapacity, original.mSize, assign, original.mArray);

	if (assign.mArray == original.mArray)
		PrintMessage("Shallow copy of array.   Whenever your class has dynamic memory, you *MUST* deep copy!");
	if (metrics.inUse != sizeof(int) * randomSize * 3)	// * 3 due to temp array in this method, and then da's mCapacity is 2x that
		PrintMessage("Incorrect amount of memory allocated.   Did you forget to delete before you re-allocated?");
	if (assign.mSize != original.mSize)
		PrintMessage("Size is not correct value");
	if (assign.mCapacity != original.mCapacity)
		PrintMessage("Capacity is not correct value");
	for (size_t i = 0; i < randomSize; ++i)
		if (assign.mArray[i] != original.mArray[i]) {
			PrintMessage("Values in array are not equal");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (assign.mArray[i] != original.mArray[i]) {
			identValues = false;
			break;
		}

	if (assign.mArray != original.mArray &&
		assign.mSize == original.mSize &&
		assign.mCapacity == original.mCapacity &&
		metrics.inUse == sizeof(int) * randomSize * 3 &&
		identValues)
		PrintMessage();

}
#endif	// End LAB1_DYNARRAY_ASSIGNMENT_BUILT_IN

#if LAB1_DYNARRAY_ASSIGNMENT_CLASS
void DSA_TestSuite_Lab1::DynArrayAssignmentOperatorClass() {
	std::cout << "Testing assignment operator with user-defined type\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;

	// Creating object to assign from
	DynArray<UserDefined> original;

	// Manually setting data members
	original.mArray = new UserDefined[randomSize];
	int randVal;
	std::string* randString = new std::string;
	for (size_t i = 0; i < randomSize; ++i) {	// Filling array with random values
		randVal = rand() % 50;
		for (int i = 0; i < 3; ++i)
			*randString += char(rand() % 26 + 97);
		original.mArray[i].mString = *randString;
		randString->clear();
		original.mArray[i].mValue = randVal;
	}
	delete randString;
	original.mCapacity = randomSize;
	original.mSize = randomSize;				// Setting the size to the number of elements used

	size_t memoryPerObject = metrics.inUse;

	DynArray<UserDefined> assign;
	// Assignment operator call
	assign = original;

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", original.mCapacity, original.mSize, assign, original.mArray);

	if (assign.mArray == original.mArray)
		PrintMessage("Shallow copy of array.   Whenever your class has dynamic memory, you *MUST* deep copy!");
	if (metrics.inUse != memoryPerObject * 2)
		PrintMessage("Incorrect amount of memory allocated");
	if (assign.mSize != original.mSize)
		PrintMessage("Size is not correct value");
	if (assign.mCapacity != original.mCapacity)
		PrintMessage("Capacity is not correct value");
	for (size_t i = 0; i < randomSize; ++i)
		if (assign.mArray[i] != original.mArray[i]) {
			PrintMessage("Values in array are not equal");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (assign.mArray[i] != original.mArray[i]) {
			identValues = false;
			break;
		}

	if (assign.mArray != original.mArray &&
		assign.mSize == original.mSize &&
		assign.mCapacity == original.mCapacity &&
		metrics.inUse == memoryPerObject * 2 &&
		identValues)
		PrintMessage();
}
#endif	// End LAB1_DYNARRAY_ASSIGNMENT_CLASS

#if LAB1_DYNARRAY_BRACKET_OP_READ_ONLY_BUILT_IN
void DSA_TestSuite_Lab1::DynArrayBracketOperator_ReadOnly() {
	std::cout << "Testing [] operator (read-only)\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;
	int* randomVals = new int[randomSize];
	for (size_t i = 0; i < randomSize; ++i)
		randomVals[i] = rand() % 100;
	int randomIndex = rand() % randomSize;


	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	memcpy(da.mArray, randomVals, sizeof(int) * randomSize);
	da.mCapacity = randomSize * 2;
	da.mSize = randomSize;

	if (verboseMode) {
		std::cout << "Attempting to access [" << randomIndex << "] (should be) " << randomVals[randomIndex] << "\n";
		VerboseOutput_DynArray("(valid address)", randomSize * 2, randomSize, da, da.mArray, false);
	}
	if (da[randomIndex] != randomVals[randomIndex])
		PrintMessage("Value returned is incorrect");


	// Testing for success
	if (da[randomIndex] == randomVals[randomIndex])
		PrintMessage();

	// Cleaning up temporary memory
	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_BRACKET_OP_READ_ONLY_BUILT_IN

#if LAB1_DYNARRAY_BRACKET_OP_WRITE_BUILT_IN
void DSA_TestSuite_Lab1::DynArrayBracketOperator_Write() {
	std::cout << "Testing [] operator (write)\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;
	int randomVal = rand() % 100;
	int* randomVals = new int[randomSize];
	for (size_t i = 0; i < randomSize; ++i)
		randomVals[i] = rand() % 100;
	int randomIndex = rand() % randomSize;

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	memcpy(da.mArray, randomVals, sizeof(int) * randomSize);
	da.mCapacity = randomSize * 2;
	da.mSize = randomSize;

	// Writing to index
	da[randomIndex] = randomVal;

	if (verboseMode) {
		std::cout << "Attempting to write [" << randomIndex << "] (should be) " << randomVal << "\n";
		VerboseOutput_DynArray("(valid address)", randomSize * 2, randomSize, da, da.mArray, false);
	}
	
	if (da[randomIndex] != randomVal)
		PrintMessage("Value returned is incorrect");


	// Testing for success
	if (da[randomIndex] == randomVal)
		PrintMessage();

	// Cleaning up temporary memory
	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_BRACKET_OP_WRITE_BUILT_IN

#if LAB1_DYNARRAY_SIZE
void DSA_TestSuite_Lab1::DynArrayAccessors_Size() {
	std::cout << "Testing Size accessor\n";

	size_t randomSize = rand() % 100;

	// Creating object (don't need to set everything)
	DynArray<char> da;
	da.mSize = randomSize;

	if (verboseMode) {
		std::cout << "\tExpected Size:\t\t" << randomSize << '\n';
		std::cout << "\tSize return:\t\t" << da.Size() << '\n';
	}

	if (da.Size() != randomSize)
		PrintMessage("Size accessor is returning incorrect value.");


	// Testing for success
	if (da.Size() == randomSize)
		PrintMessage();
}
#endif	// End LAB1_DYNARRAY_SIZE

#if LAB1_DYNARRAY_CAPACITY
void DSA_TestSuite_Lab1::DynArrayAccessors_Capacity() {
	std::cout << "Testing Capacity accessor\n";

	size_t randomSize = rand() % 100;

	// Creating object (don't need to set everything)
	DynArray<char> da;
	da.mCapacity = randomSize;

	if (verboseMode) {
		std::cout << "\tExpected Capacity:\t\t" << randomSize << '\n';
		std::cout << "\tCapacity Return:\t" << da.Capacity() << '\n';
	}

	if (da.Capacity() != randomSize)
		PrintMessage("Capacity accessor is returning incorrect value.");

	// Testing for success
	if (da.Capacity() == randomSize)
		PrintMessage();
}
#endif	// End LAB1_DYNARRAY_CAPACITY

#if LAB1_DYNARRAY_CLEAR
void DSA_TestSuite_Lab1::DynArrayClear() {
	std::cout << "Testing Clear\n";

	// Generating a random size for the array
	size_t randomSize = size_t(rand() % 20) + 1;

	DynArray<int> da;
	da.mArray = new int[randomSize];	// No need to fill in values
	da.mCapacity = randomSize * 2;

	// Calling clear
	da.Clear();

	if (verboseMode)
		VerboseOutput_DynArray("nullptr", 0, 0, da);

	if (da.mArray != nullptr)
		PrintMessage("Array should be nullptr");
	if (metrics.inUse != 0)
		PrintMessage("Memory was not correctly deleted");
	if (da.mCapacity != 0)
		PrintMessage("Capacity should be 0");
	if (da.mSize != 0)
		PrintMessage("Size should be 0");


	// Testing for success
	if (!da.mCapacity && !da.mSize && !da.mArray && !metrics.inUse)
		PrintMessage();
}
#endif	LAB1_DYNARRAY_CLEAR

#if LAB1_DYNARRAY_RESERVE_ZERO
void DSA_TestSuite_Lab1::DynArrayReserveZero() {
	std::cout << "Testing Reserve from empty DynArray\n";

	// Creating object
	DynArray<int> da;
	da.mArray = nullptr;
	da.mSize = da.mCapacity = 0;

	// Reserve call
	da.Reserve();

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", 1, 0, da);

	if (da.mArray == nullptr)
		PrintMessage("Array not pointing to valid memory");
	if (da.mCapacity != 1)
		PrintMessage("Capacity should be 1");
	if (da.mSize != 0)
		PrintMessage("Size should be 0");


	// Testing for success
	if (da.mArray != nullptr &&
		1 == da.mCapacity &&
		0 == da.mSize)
		PrintMessage();
}
#endif	// End LAB1_DYNARRAY_RESERVE_ZERO

#if LAB1_DYNARRAY_RESERVE_DOUBLE
void DSA_TestSuite_Lab1::DynArrayReserveDouble() {
	std::cout << "Testing Reserve with default doubling capacity\n";

	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;
	int* randomVals = new int[randomSize];

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	da.mCapacity = da.mSize = randomSize;
	for (size_t i = 0; i < randomSize; ++i)
		da.mArray[i] = randomVals[i] = rand() % 100;

	// Storing array address
	void* arrayAddress = da.mArray;

	size_t memoryUsed = metrics.inUse;

	// Calling Reserve with no parameters (should double capacity, and copy over data
	da.Reserve();

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", randomSize * 2, randomSize, da, randomVals);

	if (da.mArray == nullptr)
		PrintMessage("Array not pointing to valid memory");
	if (da.mArray == arrayAddress)
		PrintMessage("New array was not made");
	if (metrics.inUse != sizeof(int) * randomSize * 3)	// * 3 due to temp array in this method, and then da's mCapacity is 2x that
		PrintMessage("Array was created, but is not the correct number of elements");
	for (size_t i = 0; i < randomSize; ++i)
		if (da.mArray[i] != randomVals[i]) {
			PrintMessage("Data in array was not copied over correctly");
			break;
		}
	if (da.mCapacity != randomSize * 2)
		PrintMessage("Capacity was not doubled");
	if (da.mSize != randomSize)
		PrintMessage("Size should not change");


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (da.mArray[i] != randomVals[i]) {
			identValues = false;
			break;
		}

	if (da.mArray != nullptr &&
		metrics.inUse == sizeof(int) * randomSize * 3 &&
		da.mCapacity == randomSize * 2 &&
		da.mSize == randomSize &&
		identValues)
		PrintMessage();

	// Cleaning up memory
	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_RESERVE_DOUBLE

#if LAB1_DYNARRAY_RESERVE_VALUE
void DSA_TestSuite_Lab1::DynArrayReserveSpecific() {
	// Generating a random value to determine the starting size of the DynArray
	size_t randomSize = size_t(rand() % 6) + 5;
	size_t randomIncrease = size_t(rand() % 6) + 5;
	size_t finalSize = randomSize + randomIncrease;

	std::cout << "Testing Reserve with specific capacity (increasing from " << randomSize << " to " << finalSize << ")\n";

	int* randomVals = new int[randomSize];

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	da.mCapacity = da.mSize = randomSize;
	for (size_t i = 0; i < randomSize; ++i)
		da.mArray[i] = randomVals[i] = rand() % 100;

	// Storing array address
	void* arrayAddress = da.mArray;

	size_t memoryUsed = metrics.inUse;

	// Calling Reserve with no parameters (should double capacity, and copy over data)
	da.Reserve();

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", randomSize * 2, randomSize, da, randomVals);

	if (da.mArray == nullptr)
		PrintMessage("Array not pointing to valid memory");
	if (da.mArray == arrayAddress)
		PrintMessage("New array was not made");
	if (metrics.inUse != sizeof(int) * randomSize * 3)	// * 3 due to temp array in this method, and then da's mCapacity is 2x that
		PrintMessage("Array was created, but is not the correct number of elements");
	for (size_t i = 0; i < randomSize; ++i)
		if (da.mArray[i] != randomVals[i]) {
			PrintMessage("Data in array was not copied over correctly");
			break;
		}
	if (da.mCapacity != randomSize * 2)
		PrintMessage("Capacity was not doubled");
	if (da.mSize != randomSize)
		PrintMessage("Size should not change");


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize; ++i)
		if (da.mArray[i] != randomVals[i]) {
			identValues = false;
			break;
		}

	if (da.mArray != nullptr &&
		metrics.inUse == sizeof(int) * randomSize * 3 &&
		da.mCapacity == randomSize * 2 &&
		da.mSize == randomSize &&
		identValues)
		PrintMessage();

	// Cleaning up memory
	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_RESERVE_VALUE

#if LAB1_DYNARRAY_RESERVE_SMALLER
void DSA_TestSuite_Lab1::DynArrayReserveSmaller() {
	std::cout << "Testing Reserve with a smaller capacity\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	int* randomVals = new int[randomSize];

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	da.mCapacity = da.mSize = randomSize;
	for (size_t i = 0; i < randomSize; ++i)
		da.mArray[i] = randomVals[i] = rand() % 100 + 1;

	size_t memoryUsed = metrics.inUse;

	void* array = da.mArray;

	// Calling Reserve with smaller capacity (function should do nothing)
	da.Reserve(randomSize - 1);

	if (verboseMode) {
		// Converting address to string
		std::ostringstream address;
		address << array;
		std::string arrayAddress = address.str();
		VerboseOutput_DynArray(arrayAddress.c_str(), randomSize, randomSize, da, randomVals);
	}

	if (da.mArray != array)
		PrintMessage("Array should not be changed when reserving with a smaller size");
	if (memoryUsed != metrics.inUse)
		PrintMessage("Amount of memory should not change"); if (da.mSize != randomSize)
		PrintMessage("Size should not change when reserving with a smaller size");
	if (da.mCapacity != randomSize)
		PrintMessage("Capacity should not change when reserving with a smaller size");


	// Testing for success
	if (da.mArray == array &&
		da.mSize == randomSize &&
		da.mCapacity == randomSize)
		PrintMessage();

	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_RESERVE_SMALLER

#if LAB1_DYNARRAY_APPEND_NO_RESIZE
void DSA_TestSuite_Lab1::DynArrayAppendNoResize() {
	std::cout << "Tesing Append with no need to resize\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	int* randomVals = new int[randomSize + 1];
	int randomVal = rand() % 100 + 1;

	randomVals[randomSize] = randomVal;

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize * 2];
	da.mSize = randomSize;
	da.mCapacity = randomSize * 2;
	for (size_t i = 0; i < randomSize; ++i)
		da.mArray[i] = randomVals[i] = rand() % 100 + 1;

	size_t memoryUsed = metrics.inUse;
	void* array = da.mArray;

	da.Append(randomVal);

	if (verboseMode) {
		// Converting address to string
		std::ostringstream address;
		address << array;
		std::string arrayAddress = address.str();
		VerboseOutput_DynArray(arrayAddress.c_str(), randomSize * 2, randomSize + 1, da, randomVals);
	}

	if (array != da.mArray)
		PrintMessage("Array does not need to be re-allocated");
	if (metrics.inUse != memoryUsed)
		PrintMessage("No dynamic allocations needed");
	if (da.mSize != randomSize + 1)
		PrintMessage("Size was not incremented");
	if (da.mCapacity != randomSize * 2)
		PrintMessage("Capacity does not need to change");
	for (size_t i = 0; i < randomSize + 1; ++i)
		if (da.mArray[i] != randomVals[i]) {
			PrintMessage("Data in array was not added correctly");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize + 1; ++i)
		if (da.mArray[i] != randomVals[i]) {
			identValues = false;
			break;
		}

	if (da.mArray == array &&
		metrics.inUse == sizeof(int) * randomSize * 3 + sizeof(int) &&
		da.mCapacity == randomSize * 2 &&
		da.mSize == randomSize + 1 &&
		identValues)
		PrintMessage();

	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_APPEND_NO_RESIZE

#if LAB1_DYNARRAY_APPEND_RESIZE
void DSA_TestSuite_Lab1::DynArrayAppendResize() {
	std::cout << "Tesing Append with resize\n";

	size_t randomSize = size_t(rand() % 6) + 5;

	int* randomVals = new int[randomSize + 1];
	int randomVal = rand() % 100 + 1;

	randomVals[randomSize] = randomVal;

	// Creating object
	DynArray<int> da;
	da.mArray = new int[randomSize];
	da.mSize = randomSize;
	da.mCapacity = randomSize;
	for (size_t i = 0; i < randomSize; ++i)
		da.mArray[i] = randomVals[i] = rand() % 100 + 1;

	size_t memoryUsed = metrics.inUse;
	void* array = da.mArray;

	da.Append(randomVal);

	if (verboseMode)
		VerboseOutput_DynArray("(valid address)", randomSize * 2, randomSize + 1, da, randomVals);

	if (array == da.mArray)
		PrintMessage("Array needs to be re-allocated");
	if (metrics.inUse != memoryUsed + sizeof(int) * randomSize)
		PrintMessage("Incorrect amount of memory allocated.Did you forget to delete before you re-allocated ?");
	if (da.mSize != randomSize + 1)
		PrintMessage("Size was not incremented");
	if (da.mCapacity != randomSize * 2)
		PrintMessage("Capacity needs to double");
	for (size_t i = 0; i < randomSize + 1; ++i)
		if (da.mArray[i] != randomVals[i]) {
			PrintMessage("Data in array was not added correctly");
			break;
		}


	// Testing for success
	bool identValues = true;
	for (size_t i = 0; i < randomSize + 1; ++i)
		if (da.mArray[i] != randomVals[i]) {
			identValues = false;
			break;
		}

	if (da.mArray != array &&
		metrics.inUse == memoryUsed + sizeof(int) * randomSize &&
		da.mCapacity == randomSize * 2 &&
		da.mSize == randomSize + 1 &&
		identValues)
		PrintMessage();

	delete[] randomVals;
}
#endif	// End LAB1_DYNARRAY_APPEND_RESIZE
#endif	// End LAB_1