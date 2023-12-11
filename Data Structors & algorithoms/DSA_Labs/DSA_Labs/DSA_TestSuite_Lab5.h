/*
File:			DSA_TestSuite_Lab5.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		01.06.2021
Last Modified:	02.26.2021
Purpose:		Declaration of Lab5 Unit Tests for Dictionary
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include "Dictionary.h"

class DSA_TestSuite_Lab5 {

#if LAB_5
	using myDict = Dictionary<float, float>;
	using myPair = myDict::Pair;

	struct DictionaryWithValues {
		myDict* dict;
		float* values;
		size_t size;
	};

	static unsigned int BadHash(const float& _f);
	static DictionaryWithValues GenerateDictionary();
	static void DisplayDictionary(const myDict& _dict);

public:
	
	static void DictConstructor();
	static void DictPairConstructor();
	static void DictDestructor();
	static void DictCopyConstructor();
	static void DictAssignmentOperator();
	static void DictClear();
	static void DictInsert();
	static void DictInsertOverwrite();
	static void DictFind();
	static void DictFindNotFound();
	static void DictRemove();
	static void DictRemoveNotFound();
#endif	// End LAB_5
};

