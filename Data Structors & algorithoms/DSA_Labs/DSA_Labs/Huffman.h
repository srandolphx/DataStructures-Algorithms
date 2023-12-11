/*
File:			Huffman.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:	Sylvester Randolph 
				sjrandolph1@fullsail.edu

Created:		03.14.2021
Last Modified:	03.14.2021
Purpose:		A class to wrap up Huffman compression algorithm
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/

// Master toggle
#define LAB_8 1

// Individual unit test toggles
#define HUFFMAN_CTOR					1
#define HUFFMAN_GENERATE_FREQUENCY		1
#define HUFFMAN_GENERATE_LEAFLIST		1
#define HUFFMAN_GENERATE_TREE			1
#define HUFFMAN_CLEAR_TREE				1
#define HUFFMAN_DTOR					1
#define HUFFMAN_GENERATE_ENCODING		1
#define HUFFMAN_COMPRESS				1
#define HUFFMAN_DECOMPRESS				1

#if LAB_8
// Wraps up Huffman compression algorithm
class Huffman {

	friend class DSA_TestSuite_Lab8; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;		// The value to store (-1 if not a leaf node, 0-255 for the ascii value)
		unsigned int freq;	// The frequency of the node
		HuffNode* left;		// Left child
		HuffNode* right;	// Right child
		HuffNode* parent;	// Parent node

		// Constructor
		// 
		// In:	_value		The value of the node
		//		_freq		The frequency of the node
		//		_left		The node's left child (OPTIONAL)
		//		_right		The node's right child (OPTIONAL)
		//		_parent		The parent node (OPTIONAL)
		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
		}

		// Copy constructor
		//
		// In:	_hnode		The node to copy from
		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
		}
	};

	// A binary predicate used to compare HuffNodes
	//		This is used in the GenerateTree method
	struct HuffCompare {
		// Compare the frequency of two nodes
		// 
		// In:	_a		The first node
		//		_b		The second node
		//
		// Return: True, if _a's freq is greater than _b's freq
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	std::string mFileName;					// The name of the file to open for read/write
	unsigned int mFrequencyTable[257];		// The frequency of each character in the file (the index in the array is the char's ASCII value)
											// [256] of the array is the total count of characters in the file
	vector<HuffNode*> mLeafList;			// Contains all of the dynamically allocated leaf nodes
	HuffNode* mRoot;						// The root of the huffman tree (set in GenerateTree)
	vector<bool> mEncodingTable[256];		// Contains all of the bit-codes used to compress/decompress a file

	//write & use twice
	void zeroFreqTable() 
	{
		for (int i = 0; i < 257; i++)
			mFrequencyTable[i] = 0;
	}
	// Default constructor
	//
	// In:	_fileName		The name of the file to open
	//		_access			The way to open the file
	Huffman(const std::string& _fileName) {
		// 1. Assign the data members the values from the parameters
		mFileName = _fileName;
		// 2. Zero out the frequency table
		zeroFreqTable();
		// 3. Set the root to null
		mRoot = nullptr;
	}

	// Destructor
	//		Needs to clean up any left-over dynamic memory in tree
	~Huffman() {
		// 1. Clear out the tree
		ClearTree();
	}


	// Generate the frequency table for the Huffman algorithm (WRITING ONLY)
	//
	// NOTE:	mFrequencyTable is an array of 257 unsigned ints representing the 
	//			count of each character in the file (the index in the array is the char's ASCII value)
	//				Example:  'A' is ASCII 65, so if A is the character being checked, [65] of your array would get incremented
	//			[256] of your array is the total count of characters in the file
	void GenerateFrequencyTable() {
		 
		// 1. Open the file in binary mode	
		ifstream file(mFileName, ios::in | ios::binary);
		// 2. Get the total count of the file	(This can also be done in the next step instead)		
		zeroFreqTable();
		// 3. Read the file one byte at a time, and increment the corresponding index
		char t;
		while (file.get(t)) 
		{
			mFrequencyTable[(int)t]++;
			mFrequencyTable[256]++; //step 2
		}
		// 4. Close the file when complete
		file.close();
	}

	// Generate the leaf list for the Huffman algorithm (used in READ AND WRITE)
	//
	// Note:	Will cause leaks until ClearTree is implemented
	void GenerateLeafList() {
	
		// 1. Iterate through the frequency table (for all ASCII values) and dynamically create a leaf node for each non-0
		//		frequency.  Add it to the mLeafList vector.
		for (int i = 0; i < 256; i++) 
		{
			if (mFrequencyTable[i] > 0)
				mLeafList.push_back(new HuffNode(i, mFrequencyTable[i]));
		}
	}

	// Generate a Huffman tree
	void GenerateTree() {
		// 1. Create the priority queue
		//		This will be storing HuffNode*'s
		//		in a vector, and will be using the HuffCompare for comparison
		std::priority_queue<HuffNode*,
			vector<HuffNode*>, HuffCompare> queue;

		// 2. Add in all values from your leaf list
		for (int i = 0; i < mLeafList.size(); i++) 
		{
			queue.push(mLeafList[i]);
		}
		// 3. Enter the tree generation algorithm
		//		While the queue has more than 1 node
		//			Store the top two nodes into some temporary pointers and pop them
		//			Create a new parent node /w 1st node as left, and 2nd as right
		//			Set the parent value to -1, and frequency to the sum of its children
		//			Set the 1st and 2nd node's parent to the new node you created
		//			Insert new node into queue
		while (1 < queue.size()) {
			HuffNode* t1(queue.top());
			queue.pop();
			HuffNode* t2(queue.top());
			queue.pop();

			HuffNode* parent = new HuffNode(-1, t1->freq + t2->freq);
			parent->left = t1;
			parent->right = t2;
			t1->parent = parent;
			t2->parent = parent;

			queue.push(parent);
		}
		// 4. Set the root of the tree (this will be the only node in the queue)
		mRoot = queue.top();
	}

	// Generating the encoding table for the Huffman algorithm
	//
	//				Each vector will contain the bit-code corresponding to that index in the frequency table
	void GenerateEncodingTable() {
		// 1. Go through all of the leaf nodes and generate the bit codes
		//		You will do this by traversing up the tree from the leaf node
		//			As you move up, push a 0 to the vector if you passed through a left child connection
		//			and a 1 if you passed through a right
		//			Once you hit the root node, reverse the values in the vector
		for (int i = 0; i < mLeafList.size(); i++) {

			HuffNode* t = mLeafList[i];
			while (t != mRoot) {
				if (t->parent->left == t) {
					mEncodingTable[mLeafList[i]->value].push_back(0);
				}
				else if (t->parent->right == t) {
					mEncodingTable[mLeafList[i]->value].push_back(1);
				}
				t = t->parent;
			}
			reverse(mEncodingTable[mLeafList[i]->value].begin(), mEncodingTable[mLeafList[i]->value].end());
		}

		return;
	}

	// Clear the tree of all dynamic memory (by using the helper function)
	void ClearTree() {
		// 1. Call the helper function with the root and then set it back to null
		ClearTree(mRoot);
		mRoot = nullptr;
	}

	// Clear the tree of all dynamic memory (recursive helper function)
	// 
	// In:	_curr		The current node to clean up
	//
	// Note:	This will be a recursive function that does a post-order deletion
	void ClearTree(HuffNode* _curr) {
		// 1. Implement this method
		if (!_curr) return;

		ClearTree(_curr->left);
		ClearTree(_curr->right);

		delete[] _curr;
	}

	// Write a Huffman compressed file to disk
	//
	// In:	_outputFile			Where to write the compressed data to
	//
	// Note: You will use most of your other functionality to complete this function
	void Compress(const char* _outputFile) {
		// 1. Create the frequency table, leaf list, tree, and encoding table
		GenerateFrequencyTable();
		GenerateLeafList();
		GenerateTree();
		GenerateEncodingTable();
		// 2. Create a BitOStream and supply it the huffman header
		BitOStream ofile(_outputFile,
			(char*)mFrequencyTable, sizeof(unsigned int) * 257);

		// 3. Open the input file in binary mode with a standard ifstream
		ifstream ifile(mFileName, ios_base::binary);
		// 4. Start the compression process.   (You can read the whole file into a buffer first if you want)
		//		For each character in the original file, write out the bit-code from the encoding table
		char t;
		for (; ifile.get(t);)
		{
			ofile << mEncodingTable[(int)t];
		}
		
		// 5. Close the file streams when done
		ifile.close();
		ofile.Close();
		// 6. Clear the tree (and optional buffer)
		ClearTree();
	}

	// check
	bool isLeaf(HuffNode* _node) {
		if (_node->left || _node->right) return false;
		else return true;
	}
	// Decompress a huffman-compressed file
	//
	// In:	_outputFile		Where to write the uncompressed data to
	//
	// Note: The mFileName will be the compressed file
	void Decompress(const char* _outputFile) {
		// 1. Create a BitIStream and read the frequency table
		BitIStream ifile(mFileName.c_str(), (char*)&mFrequencyTable, sizeof(unsigned int) * 257);
		// 2. Create the leaf list and tree
		GenerateLeafList();
		GenerateTree();
		// 3. Create the stream for output (binary mode)
		ofstream ofile(_outputFile, ios::out | ios::binary);
		// 4. Create a bool to use for traversing down the list, and a char to store the character for writing
		bool trav;
		char t;
		int i = 0;
		// 5. Create a node pointer for use in traversing the list (start it at the top)
		HuffNode* h = mRoot;
		// 6. Go through the compressed file one bit at a time, traversing through the tree
		//		When you get to a leaf node, write out the value, and go back to the root
		//	Note: Remember, there may be trailing 0's at the end of the file, so only loop the appropriate number of times
		for (int i = 0; i < mFrequencyTable[256]; i++) 
		{
			if (ifile.eof()) break;
			for (int j = 0; j < 8; j++) 
			{

				if (ifile.eof()) break;

				if (isLeaf(h)) 
				{
					ofile << (char)h->value;
					h = mRoot;
				}
				else {
					ifile >> trav;
					if (trav) 
					{
						h = h->right;
					}
					else 
					{
						h = h->left;
					}
				}
			}
		}
		// 7. Close the streams
		ifile.Close();
		ofile.close();
		// 8. Clean up the dynamic memory by clearing the tree
		ClearTree();
	}
};

#endif	// End LAB_8