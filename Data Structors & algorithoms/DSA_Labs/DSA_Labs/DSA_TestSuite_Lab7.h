/*
File:			DSA_TestSuite_Lab7.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		03.05.2021
Last Modified:	03.21.2021
Purpose:		Declaration of Lab7 Unit Tests for BST
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include "BST.h"
#include <vector>

class DSA_TestSuite_Lab7 {

#if LAB_7
	using myBST = BST<int>;
	using myNode = myBST::Node;

	static myBST* GenerateTree();
	static void GetNodes(myNode* _node, std::vector<myNode*>& _vec);

	static void DisplayNode(int _val, const myNode* _left, const myNode* _right, const myNode& _node);

	static void DisplayTree(const std::string& _prefix, const myNode* _node, bool _isLeft);
	static void DisplayTree(const myNode* _node);

public:
	static void BSTDefaultConstructor();
	static void BSTNodeConstructor();
	static void BSTCopyConstructor();
	static void BSTAssignmentOperator();
	static void BSTClear();
	static void BSTDestructor();
	static void BSTPushRoot();
	static void BSTPushRootLeft();
	static void BSTPushRootRight();
	static void BSTPushLeft();
	static void BSTPushRight();
	static void BSTContainsTrue();
	static void BSTContainsFalse();
	static void BSTRemoveCase0Root();
	static void BSTRemoveCase0Left();
	static void BSTRemoveCase0Right();
	static void BSTRemoveCase1RootLeft();
	static void BSTRemoveCase1RootRight();
	static void BSTRemoveCase1LeftLeft();
	static void BSTRemoveCase1LeftRight();
	static void BSTRemoveCase1RightLeft();
	static void BSTRemoveCase1RightRight();
	static void BSTRemoveCase2Subtree();
	static void BSTRemoveCase2NonRootNoSubtree();
	static void BSTRemove();
	static void BSTRemoveNotFound();
	static void BSTInOrderTraversal();
#endif	// End LAB_7
};

