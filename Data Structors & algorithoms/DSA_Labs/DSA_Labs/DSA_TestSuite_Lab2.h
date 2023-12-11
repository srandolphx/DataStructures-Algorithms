/*
File:			DSA_TestSuite_Lab2.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.30.2020
Last Modified:	02.26.2021
Purpose:		Declaration of Lab2 Unit Tests for DSA_Lab2
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include "DSA_Lab2.h"

class DSA_TestSuite_Lab2 {

public:

#if LAB_2
	static void CheckForPalindrome();
	static void VectorFillFromFile();
	static void VectorFillFromArray();
	static void VectorClear();
	static void VectorSortAscending();
	static void VectorSortDescending();
	static void VectorIndexing();
	static void VectorContainsTrue();
	static void VectorContainsFalse();
	static void VectorMovePalindrome();
#endif	// End LAB_2
};

