/*
File:			DSA_TestSuite_Lab3.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		12.27.2020
Last Modified:	02.26.2021
Purpose:		Declaration of Lab3 Unit Tests for DList
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <list>
#include "DList.h"
#include "DSA_TestSuite_GlobalFunctions.h"


class DSA_TestSuite_Lab3 {

#if LAB_3
	using Node = DList<int>::Node;

public:
	static void LinkedListDefaultConstructor();
	static void LinkedListNodeConstructorWithDefaults();
	static void LinkedListDestructor();
	static void LinkedListNodeConstructor();
	static void LinkedListCopyConstructorInt();
	static void LinkedListCopyConstructorClass();
	static void LinkedListAssignmentOperatorInt();
	static void LinkedListAssignmentOperatorClass();
	static void LinkedListAddHeadEmpty();
	static void LinkedListAddHeadExisting();
	static void LinkedListAddTailEmpty();
	static void LinkedListAddTailExisting();
	static void LinkedListClear();
	static void LinkedListInsertEmpty();
	static void LinkedListInsertHead();
	static void LinkedListInsertMiddle();
	static void LinkedListEraseEmpty();
	static void LinkedListEraseHead();
	static void LinkedListEraseTail();
	static void LinkedListEraseMiddle();
	static void LinkedListIterBegin();
	static void LinkedListIterEnd();
	static void LinkedListIterPreIncrement();
	static void LinkedListIterPostIncrement();
	static void LinkedListIterPreDecrement();
	static void LinkedListIterPostDecrement();

	static void DisplayNode(int _val, const Node* _next,
		const Node* _prev, const Node& _node);

	static void DisplayList(const std::list<int>& _list, 
		const DList<int>& _dlist);

	static void DisplayList(const std::list<UserDefined>& _list,
		const DList<UserDefined>& _dlist);
#endif	// End LAB_3
};