/*
File:			DSA_TestSuite_Lab4.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		12.30.2020
Last Modified:	02.26.2021
Purpose:		Declaration of Lab4 Unit Tests for list
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

// Header protection
#pragma once

#include <iostream>
#include "DSA_Lab4.h"

class DSA_TestSuite_Lab4 {

public:

#if LAB_4
	static void ListQueueAdd();
	static void ListStackAdd();
	static void ListQueueRemove();
	static void ListStackRemove();
	static void ListInsertIndex();
	static void ListInsertIterator();
	static void ListRemoveDecimal();
#endif	// End LAB_4
};

