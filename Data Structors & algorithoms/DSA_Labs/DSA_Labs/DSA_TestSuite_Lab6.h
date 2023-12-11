/*
File:			DSA_TestSuite_Lab6.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		02.15.2021
Last Modified:	02.26.2021
Purpose:		Declaration of Lab6 Unit Tests for unordered_map
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once



/************/
/* Includes */
/************/
#include "DSA_Lab6.h"

class DSA_TestSuite_Lab6 {

public:

#if LAB_6
	static void MapPopulateLetterValues();
	static void MapGetLetterValue();
	static void MapGetWordValue();
	static void MapCreatePair();
	static void MapLoadFile();
	static void MapFindWordScore();
#endif	// End LAB_6
};
