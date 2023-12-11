/*
File:			DSA_TestSuite_Lab7.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		03.14.2021
Last Modified:	03.14.2021
Purpose:		Declaration of Lab8 Unit Tests for Huffman
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include "Huffman.h"
#include <vector>

class DSA_TestSuite_Lab8 {

#if LAB_8
	using myHuffNode = Huffman::HuffNode;
	using myVector = std::vector<myHuffNode*>;

	// Helper method
	static bool HuffmanCompareTree(myHuffNode* _a, myHuffNode* _b);
	static void ParseTree(myHuffNode* _node, myVector& _nodeVec);

public:
	static void HuffmanConstructor();
	static void HuffmanGenerateFrequencyTable();
	static void HuffmanGenerateLeafList();
	static void HuffmanGenerateTree();
	static void HuffmanClearTree();
	static void HuffmanDestructor();
	static void HuffmanGenerateEncodingTable();
	static void HuffmanCompress();
	static void HuffmanDecompress();

#endif	// End LAB_8
};