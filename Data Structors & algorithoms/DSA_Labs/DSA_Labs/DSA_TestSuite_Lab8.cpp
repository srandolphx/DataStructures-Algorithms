/*
File:			DSA_TestSuite_Lab8.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		03.12.2021
Last Modified:	03.19.2021
Purpose:		Definitions of Lab8 Unit Tests for Huffman compression
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <string>
#include <iostream>
#include "DSA_TestSuite_Lab8.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

#if LAB_8
bool DSA_TestSuite_Lab8::HuffmanCompareTree(myHuffNode* _a, myHuffNode* _b) {
	// Check for empty
	if (!_a && !_b)
		return 1;

	// One is empty
	else if (!_a || !_b)
		return 0;

	// Both non-empty
	else {
		return	(_a->value == _b->value &&
			_a->freq == _b->freq &&
			HuffmanCompareTree(_a->left, _b->left) &&
			HuffmanCompareTree(_a->left, _b->left));
	}
}

void DSA_TestSuite_Lab8::ParseTree(myHuffNode* _node, myVector& _nodeVec) {
	if (_node) {
		ParseTree(_node->left, _nodeVec);
		_nodeVec.push_back(_node);
		ParseTree(_node->right, _nodeVec);
	}
}


// Generate frequency tables for each of the sample files
unsigned int* GetFreqTable(int _fileNumber) {

	unsigned int* freqTable = new unsigned int[257];

	// us-cities.txt
	if (!_fileNumber) {
		//	0		1		2		3		4		5		6		7		8		9
		unsigned int freq[257] = { 0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 0
									18579,	0,		0,		18579,	0,		0,		0,		0,		0,		0,		// 10
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0, 		// 20
									0,		0,		5984,	0,		0,		0,		0,		0,		0,		2, 		// 30
									0,		0,		0,		0,		0,		1,		0,		0,		0,		0, 		// 40
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 50
									0,		0,		0,		0,		0,		933,	1933,	2616,	816,	834,	// 60
									1002,	1076,	1447,	334,	305,	533,	1442,	1913,	824,	582,	// 70
									1594,	56,		1157,	2337,	798,	116,	508,	1274,	2,		101,	// 80
									51,		0,		0,		0,		0,		0,		0,		13765,	1778,	2928,	// 90
									4107,	16254,	1025,	2723,	3479,	9870,	37,		2568,	11884,	2495,	// 100
									11333,	11486,	1761,	115,	10804,	6800,	8469,	3886,	2337,	1926,	// 110
									278,	2814,	231,	0,		0,		0,		0,		0,		0,		0, 		// 120
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 130
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0, 		// 140
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 150
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0, 		// 160
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 170
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 180
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 190
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 200
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 210
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 220
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 230
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 240
									0,		0,		0,		0,		0,		0,		202882 };						// 250
		memcpy(freqTable, freq, sizeof(unsigned int) * 257);
	}
	// words.txt
	else {
		//	0		1		2		3		4		5		6		7		8		9
		unsigned int freq[257] = { 0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 0
									178635,	0,		0,		0,		0,		0,		0,		0,		0,		0,		// 10
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 20 
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 30
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 40
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 50
									0,		0,		0,		0,		0,		120923,	30120,	64162,	54854,	182711,	// 60
									20016,	43460,	36764,	140275,	2674,	14435,	84604,	44853,	106737,	103479,	// 70
									46599,	2584,	112444,	150189,	104029,	52104,	15429,	12416,	4761,	25860,	// 80
									7601,	0,		0,		0,		0,		0,		0,		0,		0,		0,		// 90
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 100
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 110
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 120
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 130
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 140
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 150
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 160
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 170
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 180
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 190
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 200
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 210
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 220
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 230
									0,		0,		0,		0,		0,		0,		0,		0,		0,		0,		// 240
									0,		0,		0,		0,		0,		0,		1762718							// 250

		};


		memcpy(freqTable, freq, sizeof(unsigned int) * 257);
	}
	return freqTable;
}

#if HUFFMAN_CTOR
void DSA_TestSuite_Lab8::HuffmanConstructor() {
	// Creating a random filename (not an actual file)
	std::string file;
	for (int i = 0; i < 5; ++i)
		file += char((rand() % 26) + 97);
	file += ".file";

	std::cout << "Testing Huffman constructor with " << file << "\n";

	Huffman huff(file);
	unsigned int testFreq = 0;
	bool isSameFreq = true;
	bool emptyEncoding = true;

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	// Error testing
	if (huff.mFileName != file)
		PrintMessage("Filename was not copied into data member");

	for (size_t i = 0; i < 257; ++i) {
		if (memcmp(&huff.mFrequencyTable, &testFreq, 4) != 0) {
			PrintMessage("One (or more) indices have not been set to 0");
			isSameFreq = false;
			break;
		}
	}

	if (huff.mLeafList.size())
		PrintMessage("Leaf list should be empty at this point");

	if (huff.mRoot != nullptr)
		PrintMessage("Root should be null");

	for (size_t i = 0; i < 256; ++i)
		if (huff.mEncodingTable[i].size()) {
			PrintMessage("All encoding tables should be empty");
			emptyEncoding = false;
			break;
		}


	// Testing for success
	if (huff.mFileName == file &&
		isSameFreq && emptyEncoding &&
		nullptr == huff.mRoot &&
		!huff.mLeafList.size())
		PrintMessage();
}
#endif	// End HUFFMAN_CTOR

#if HUFFMAN_GENERATE_FREQUENCY
void DSA_TestSuite_Lab8::HuffmanGenerateFrequencyTable() {
	int fileNum = rand() % 2;
	std::string fileName = (0 == fileNum ? "us-cities.txt" : "words.txt");

	std::cout << "Testing Huffman frequency table generation with " << fileName << '\n';

	bool isSameFreq = true;
	unsigned int testFreq = 0;
	unsigned int* testFreqTable = GetFreqTable(fileNum);

	Huffman huff(fileName);
	huff.GenerateFrequencyTable();

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	// Error testing
	bool failMsg = true;
	for (size_t i = 0; i < 257; ++i) {
		if (huff.mFrequencyTable[i] != testFreqTable[i]) {
			string indexString = "[" + std::to_string(i) +
				"]:\t Expected: " + std::to_string(testFreqTable[i]) +
				"\tYours: " + std::to_string(huff.mFrequencyTable[i]);
			if (failMsg) {
				PrintMessage("One or more values in frequency table are incorrect");
				isSameFreq = false;
				failMsg = false;
			}
			std::cout << indexString << '\n';
		}
	}

	// Clean up
	delete[] testFreqTable;

	// Testing for success
	if (isSameFreq)
		PrintMessage();
}
#endif	// End HUFFMAN_GENERATE_FREQUENCY

#if HUFFMAN_GENERATE_LEAFLIST
void DSA_TestSuite_Lab8::HuffmanGenerateLeafList() {
	int fileNum = rand() % 2;
	std::string fileName = (0 == fileNum ? "us-cities.txt" : "words.txt");

	std::cout << "Testing Huffman leaf list generation with " << fileName << '\n';

	int leafSize = !fileNum ? 57 : 27;
	unsigned int testFreq = 0;
	unsigned int* testFreqTable = GetFreqTable(fileNum);
	bool isSameFreq = true;

	Huffman huff(fileName);
	memcpy(huff.mFrequencyTable, testFreqTable, sizeof(unsigned int) * 257);
	huff.GenerateLeafList();

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	// Error testing
	if (huff.mLeafList.size() != leafSize)
		PrintMessage("Leaf list is incorrect size (did you accidentally include the total?)");

	
	for (auto iter = huff.mLeafList.begin(); iter != huff.mLeafList.end(); ++iter) {
		if ((*iter)->freq != testFreqTable[(*iter)->value]) {
			PrintMessage("Frequency of one or more nodes is incorrect");
			isSameFreq = false;
			break;
		}
	}

	// Clean up
	delete[] testFreqTable;
	for (size_t i = 0; i < huff.mLeafList.size(); ++i)
		delete huff.mLeafList[i];

	// Testing for success
	if (huff.mLeafList.size() == leafSize &&
		isSameFreq)
		PrintMessage();
}
#endif	// End HUFFMAN_GENERATE_LEAFLIST

#if HUFFMAN_GENERATE_TREE
struct leaf {
	short val;
	unsigned int freq;
};

void DSA_TestSuite_Lab8::HuffmanGenerateTree() {
	std::cout << "Testing generation of Huffman tree\n";

	Huffman huff("not_used.txt");

	bool correctTree = false;
	unsigned int totalFreq = 15;

	// Generating data for string/file containing "This is a test.";
	leaf leafNodes[9] = { {' ', 3},
							{'.', 1},
							{'T', 1},
							{'a', 1},
							{'e', 1},
							{'h', 1},
							{'i', 2},
							{'s', 3},
							{'t', 2},
	};

	// Adding leaves to list
	for (size_t i = 0; i < 9; ++i)
		huff.mLeafList.push_back(new myHuffNode(leafNodes[i].val, leafNodes[i].freq));

	// Creating tree in a convulated way to not give away the answer
	myHuffNode tree[17] = {
		/* 0 */		Huffman::HuffNode(-1,	15,	&tree[1],	&tree[2],	nullptr),
		/* 1 */		Huffman::HuffNode(-1,	6,	&tree[3],	&tree[4],	&tree[0]),
		/* 2 */		Huffman::HuffNode(-1,	9,	&tree[5],	&tree[6],	&tree[0]),
		/* 3 */		Huffman::HuffNode(-1,	3,	&tree[7],	&tree[8],	&tree[1]),
		/* 4 */		Huffman::HuffNode('s',	3,	nullptr,	nullptr,	&tree[1]),
		/* 5 */		Huffman::HuffNode(-1,	4,	&tree[9],	&tree[10],	&tree[2]),
		/* 6 */		Huffman::HuffNode(-1,	5,	&tree[11],	&tree[12],	&tree[2]),
		/* 7 */		Huffman::HuffNode('e',	1,	nullptr,	nullptr,	&tree[3]),
		/* 8 */		Huffman::HuffNode('i',	2,	nullptr,	nullptr,	&tree[3]),
		/* 9 */		Huffman::HuffNode(-1,	2,	&tree[13],	&tree[14],	&tree[5]),
		/* 10 */	Huffman::HuffNode(-1,	2,	&tree[15],	&tree[16],	&tree[5]),
		/* 11 */	Huffman::HuffNode('t',	2,	nullptr,	nullptr,	&tree[6]),
		/* 12 */	Huffman::HuffNode(' ',	3,	nullptr,	nullptr,	&tree[6]),
		/* 13 */	Huffman::HuffNode('h',	1,	nullptr,	nullptr,	&tree[9]),
		/* 14 */	Huffman::HuffNode('a',	1,	nullptr,	nullptr,	&tree[9]),
		/* 15 */	Huffman::HuffNode('.',	1,	nullptr,	nullptr,	&tree[10]),
		/* 16 */	Huffman::HuffNode('T',	1,	nullptr,	nullptr,	&tree[10]),
	};

	huff.GenerateTree();
	bool identicalTree = HuffmanCompareTree(huff.mRoot, &tree[0]);
	bool parentNodes = true;

	if (verboseMode) {
		// TODO
	}

	// Error testing
	if (!huff.mRoot)
		PrintMessage("Root is not pointing to a valid node");
	if (huff.mRoot && huff.mRoot->freq != totalFreq)
		PrintMessage("Root does not contain total frequency");
	if (huff.mRoot && huff.mRoot->left && huff.mRoot->left->parent != huff.mRoot) {
		PrintMessage("Nodes do not have valid parent pointers");
		parentNodes = false;
	}
	if (!identicalTree)
		PrintMessage("Trees are not identical.   Double-check algorithm");

	// Testing for success
	if (huff.mRoot &&
		totalFreq == huff.mRoot->freq &&
		parentNodes && identicalTree)
		PrintMessage();

	// Clean up
	myVector nodes;
	ParseTree(huff.mRoot, nodes);
	for (auto iter = nodes.begin(); iter != nodes.end(); ++iter)
		delete *iter;
	huff.mRoot = nullptr;
}
#endif	// End HUFFMAN_GENERATE_TREE

#if HUFFMAN_CLEAR_TREE
void DSA_TestSuite_Lab8::HuffmanClearTree() {
	std::cout << "Testing Clear method\n";

	Huffman huff("not_used.txt");

	size_t memoryUsed = metrics.inUse;

	myHuffNode* tree[17];
	for (size_t i = 0; i < 17; ++i)
		tree[i] = new myHuffNode(-1, -1);

	
	/* 0 */		*tree[0] = myHuffNode(-1, 15, tree[1], tree[2], nullptr);
	/* 1 */		*tree[1] = myHuffNode(-1,	6,	tree[3],	tree[4],	tree[0]);
	/* 2 */		*tree[2] = myHuffNode(-1,	9,	tree[5],	tree[6],	tree[0]);
	/* 3 */		*tree[3] = myHuffNode(-1,	3,	tree[7],	tree[8],	tree[1]);
	/* 4 */		*tree[4] = myHuffNode('s',	3,	nullptr,	nullptr,	tree[1]);
	/* 5 */		*tree[5] = myHuffNode(-1,	4,	tree[9],	tree[10],	tree[2]);
	/* 6 */		*tree[6] = myHuffNode(-1,	5,	tree[11],	tree[12],	tree[2]);
	/* 7 */		*tree[7] = myHuffNode('e',	1,	nullptr,	nullptr,	tree[3]);
	/* 8 */		*tree[8] = myHuffNode('i',	2,	nullptr,	nullptr,	tree[3]);
	/* 9 */		*tree[9] = myHuffNode(-1,	2,	tree[13],	tree[14],	tree[5]);
	/* 10 */	*tree[10] = myHuffNode(-1,	2,	tree[15],	tree[16],	tree[5]);
	/* 11 */	*tree[11] = myHuffNode('t',	2,	nullptr,	nullptr,	tree[6]);
	/* 12 */	*tree[12] = myHuffNode(' ',	3,	nullptr,	nullptr,	tree[6]);
	/* 13 */	*tree[13] = myHuffNode('h',	1,	nullptr,	nullptr,	tree[9]);
	/* 14 */	*tree[14] = myHuffNode('a',	1,	nullptr,	nullptr,	tree[9]);
	/* 15 */	*tree[15] = myHuffNode('.',	1,	nullptr,	nullptr,	tree[10]);
	/* 16 */	*tree[16] = myHuffNode('T',	1,	nullptr,	nullptr,	tree[10]);
			
	huff.mRoot = tree[0];

	huff.ClearTree();

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	if (metrics.inUse != memoryUsed)
		PrintMessage("Not all nodes from tree were deleted");
	if (huff.mRoot)
		PrintMessage("Root was not set to nullptr after delete");

	if (memoryUsed == metrics.inUse &&
		nullptr == huff.mRoot)
		PrintMessage();
}
#endif	// End HUFFMAN_CLEAR_TREE

#if HUFFMAN_DTOR
void DSA_TestSuite_Lab8::HuffmanDestructor() {
	std::cout << "Testing Destructor\n";

	size_t memoryUsed = metrics.inUse;

	Huffman*huff = new Huffman("not_used.txt");

	myHuffNode* tree[17];
	for (size_t i = 0; i < 17; ++i)
		tree[i] = new myHuffNode(-1, -1);


	/* 0 */		*tree[0] = myHuffNode(-1, 15, tree[1], tree[2], nullptr);
	/* 1 */		*tree[1] = myHuffNode(-1, 6, tree[3], tree[4], tree[0]);
	/* 2 */		*tree[2] = myHuffNode(-1, 9, tree[5], tree[6], tree[0]);
	/* 3 */		*tree[3] = myHuffNode(-1, 3, tree[7], tree[8], tree[1]);
	/* 4 */		*tree[4] = myHuffNode('s', 3, nullptr, nullptr, tree[1]);
	/* 5 */		*tree[5] = myHuffNode(-1, 4, tree[9], tree[10], tree[2]);
	/* 6 */		*tree[6] = myHuffNode(-1, 5, tree[11], tree[12], tree[2]);
	/* 7 */		*tree[7] = myHuffNode('e', 1, nullptr, nullptr, tree[3]);
	/* 8 */		*tree[8] = myHuffNode('i', 2, nullptr, nullptr, tree[3]);
	/* 9 */		*tree[9] = myHuffNode(-1, 2, tree[13], tree[14], tree[5]);
	/* 10 */	*tree[10] = myHuffNode(-1, 2, tree[15], tree[16], tree[5]);
	/* 11 */	*tree[11] = myHuffNode('t', 2, nullptr, nullptr, tree[6]);
	/* 12 */	*tree[12] = myHuffNode(' ', 3, nullptr, nullptr, tree[6]);
	/* 13 */	*tree[13] = myHuffNode('h', 1, nullptr, nullptr, tree[9]);
	/* 14 */	*tree[14] = myHuffNode('a', 1, nullptr, nullptr, tree[9]);
	/* 15 */	*tree[15] = myHuffNode('.', 1, nullptr, nullptr, tree[10]);
	/* 16 */	*tree[16] = myHuffNode('T', 1, nullptr, nullptr, tree[10]);

	huff->mRoot = tree[0];

	delete huff;

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	if (metrics.inUse != memoryUsed)
		PrintMessage("Not all nodes from tree were deleted");

	if (memoryUsed == metrics.inUse)
		PrintMessage();
}
#endif	// End HUFFMAN_DTOR

#if HUFFMAN_GENERATE_ENCODING
void DSA_TestSuite_Lab8::HuffmanGenerateEncodingTable() {
	std::cout << "Testing generation of Huffman encoding table\n";

	Huffman huff("dummy.txt");
	bool correctEncoding = true;

	// Generating data for string/file containing "This is a test."
		// Creating tree in a convuluted way to not give away the answer
	Huffman::HuffNode tree[17] = {
		/* 0 */		Huffman::HuffNode(-1,	15,	&tree[1],	&tree[2],	nullptr),
		/* 1 */		Huffman::HuffNode(-1,	6,	&tree[3],	&tree[4],	&tree[0]),
		/* 2 */		Huffman::HuffNode(-1,	9,	&tree[5],	&tree[6],	&tree[0]),
		/* 3 */		Huffman::HuffNode(-1,	3,	&tree[7],	&tree[8],	&tree[1]),
		/* 4 */		Huffman::HuffNode('s',	3,	nullptr,	nullptr,	&tree[1]),
		/* 5 */		Huffman::HuffNode(-1,	4,	&tree[9],	&tree[10],	&tree[2]),
		/* 6 */		Huffman::HuffNode(-1,	5,	&tree[11],	&tree[12],	&tree[2]),
		/* 7 */		Huffman::HuffNode('e',	1,	nullptr,	nullptr,	&tree[3]),
		/* 8 */		Huffman::HuffNode('i',	2,	nullptr,	nullptr,	&tree[3]),
		/* 9 */		Huffman::HuffNode(-1,	2,	&tree[13],	&tree[14],	&tree[5]),
		/* 10 */	Huffman::HuffNode(-1,	2,	&tree[15],	&tree[16],	&tree[5]),
		/* 11 */	Huffman::HuffNode('t',	2,	nullptr,	nullptr,	&tree[6]),
		/* 12 */	Huffman::HuffNode(' ',	3,	nullptr,	nullptr,	&tree[6]),
		/* 13 */	Huffman::HuffNode('h',	1,	nullptr,	nullptr,	&tree[9]),
		/* 14 */	Huffman::HuffNode('a',	1,	nullptr,	nullptr,	&tree[9]),
		/* 15 */	Huffman::HuffNode('.',	1,	nullptr,	nullptr,	&tree[10]),
		/* 16 */	Huffman::HuffNode('T',	1,	nullptr,	nullptr,	&tree[10]),
	};

	Huffman::HuffNode* leafNodes[9] = {
		&tree[12],	// ' '
		&tree[15],	// '.'
		&tree[16],	// 'T'
		&tree[14],	// 'a'
		&tree[7],	// 'e'
		&tree[13],	// 'h'
		&tree[8],	// 'i'
		&tree[4],	// 's'
		&tree[11],	// 't'
	};


	// Adding leaves to list
	for (int i = 0; i < 9; ++i)
		huff.mLeafList.push_back(leafNodes[i]);

	// Test data
	vector<bool> encodingData[9];
	int indices[9] = { ' ', '.', 'T', 'a', 'e', 'h', 'i', 's', 't' };
	encodingData[0].push_back(1); encodingData[0].push_back(1); encodingData[0].push_back(1);
	encodingData[1].push_back(1); encodingData[1].push_back(0); encodingData[1].push_back(1); encodingData[1].push_back(0);
	encodingData[2].push_back(1); encodingData[2].push_back(0); encodingData[2].push_back(1); encodingData[2].push_back(1);
	encodingData[3].push_back(1); encodingData[3].push_back(0); encodingData[3].push_back(0); encodingData[3].push_back(1);
	encodingData[4].push_back(0); encodingData[4].push_back(0); encodingData[4].push_back(0);
	encodingData[5].push_back(1); encodingData[5].push_back(0); encodingData[5].push_back(0); encodingData[5].push_back(0);
	encodingData[6].push_back(0); encodingData[6].push_back(0); encodingData[6].push_back(1);
	encodingData[7].push_back(0); encodingData[7].push_back(1);
	encodingData[8].push_back(1); encodingData[8].push_back(1); encodingData[8].push_back(0);

	huff.mRoot = &tree[0];

	huff.GenerateEncodingTable();

	if (verboseMode) {
		// TODO
	}

	for (int i = 0; i < 9; ++i)
		if (huff.mEncodingTable[indices[i]] != encodingData[i]) {
			PrintMessage(std::string(to_string(indices[i]) + " Encoding data is incorrect.   Did you not reverse the codes?").c_str());
			correctEncoding = false;
		}

	huff.mRoot = nullptr;

	if (correctEncoding)
		PrintMessage();
}
#endif	// End HUFFMAN_GENERATE_ENCODING

#if HUFFMAN_COMPRESS
void DSA_TestSuite_Lab8::HuffmanCompress() {
	int fileNum = rand() % 2;
	string fileName = fileNum == 0 ? "us-cities.txt" : "words.txt";

	std::cout << "Testing compression of "<< fileName << " using Huffman algorithm (this might take a few seconds)\n";
	
	string compressedFileName = fileNum == 0 ? "us-cities.bin" : "words.bin";
	string checkFileName = fileNum == 0 ? "us-cities_check.bin" : "words_check.bin";
	char* checkBuffer = nullptr, * studentBuffer = nullptr;
	int checkTotal = 0, studentTotal = 0;

	Huffman huff(fileName);
	bool identicalData = true;

	huff.Compress(compressedFileName.c_str());

	// Error testing

	// Open the two files to do a byte-by-byte comparison
	ifstream checkFile(checkFileName, ios_base::binary);
	ifstream studentFile(compressedFileName, ios_base::binary);

	if (!studentFile.is_open())
		PrintMessage("Compressed file did not open correctly");

	else {
	
		// Read all of both files
		checkFile.seekg(0, ios_base::end);
		studentFile.seekg(0, ios_base::end);
		checkTotal = (int)checkFile.tellg();
		studentTotal = (int)studentFile.tellg();
		checkFile.seekg(0, ios_base::beg);
		studentFile.seekg(0, ios_base::beg);
		checkBuffer = new char[checkTotal];
		studentBuffer = new char[studentTotal];
		checkFile.read(checkBuffer, checkTotal);
		studentFile.read(studentBuffer, studentTotal);
		checkFile.close();
		studentFile.close();

		if (studentTotal < checkTotal) {
			PrintMessage("Your file is too small (missing data)");
		}
		else if (studentTotal > checkTotal) {
			PrintMessage("Your file is too large (possibly tried to uncompress trailing 0's)");
		}
		if (studentTotal == checkTotal && memcmp(studentBuffer, checkBuffer, studentTotal) != 0) {
			PrintMessage("Data is incorrect");
			identicalData = false;
		}
	}

	delete[] checkBuffer;
	delete[] studentBuffer;
	std::remove(compressedFileName.c_str());

	// Success
	if (studentTotal != 0 && studentTotal == checkTotal && 
		identicalData)
		PrintMessage();
}
#endif	// End HUFFMAN_COMPRESS

#if HUFFMAN_DECOMPRESS
void DSA_TestSuite_Lab8::HuffmanDecompress() {
	int fileNum = rand() % 2;
	string compressedFileName = fileNum == 0 ? "us-cities_check.bin" : "words_check.bin";
	std::cout << "Testing decompression of "<< compressedFileName << " using Huffman algorithm (this might take a few seconds)\n";


	string checkFileName = fileNum == 0 ? "us-cities.txt" : "words.txt";
	string studentFileName = fileNum == 0 ? "us-cities_uncompressed.txt" : "words_uncompressed.txt";
	char* checkBuffer, * studentBuffer;
	int checkTotal, studentTotal;
	bool identicalData = true;

	Huffman huff(compressedFileName);
	bool success = true;

	huff.Decompress(studentFileName.c_str());

	// Open the two files to do a byte-by-byte comparison
	ifstream checkFile(checkFileName, ios_base::binary);
	ifstream studentFile(studentFileName, ios_base::binary);

	// Read all of both files
	checkFile.seekg(0, ios_base::end);
	studentFile.seekg(0, ios_base::end);
	checkTotal = (int)checkFile.tellg();
	studentTotal = (int)studentFile.tellg();
	checkFile.seekg(0, ios_base::beg);
	studentFile.seekg(0, ios_base::beg);
	checkBuffer = new char[checkTotal];
	studentBuffer = new char[studentTotal];
	checkFile.read(checkBuffer, checkTotal);
	studentFile.read(studentBuffer, studentTotal);

	checkFile.close();
	studentFile.close();

	std::remove(studentFileName.c_str());

	if (studentTotal < checkTotal) {
		PrintMessage("Your file is too small (missing data)");
	}
	else if (studentTotal > checkTotal) {
		PrintMessage("Your file is too large (possibly tried to uncompress trailing 0's)");
	}
	if (success && memcmp(studentBuffer, checkBuffer, studentTotal) != 0) {
		PrintMessage("Data is incorrect");
		identicalData = false;
	}

	delete[] checkBuffer;
	delete[] studentBuffer;

	// Success
	if (studentTotal == checkTotal &&
		identicalData)
		PrintMessage();
}
#endif	// End HUFFMAN_DECOMPRESS

#endif	// End LAB_8