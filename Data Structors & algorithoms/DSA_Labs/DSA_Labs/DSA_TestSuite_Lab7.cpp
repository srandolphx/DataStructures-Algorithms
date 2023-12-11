/*
File:			DSA_TestSuite_Lab7.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		03.05.2021
Last Modified:	03.21.2021
Purpose:		Definitions of Lab7 Unit Tests for BST
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <iostream>
#include "DSA_TestSuite_Lab7.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

#if LAB_7
DSA_TestSuite_Lab7::myBST* DSA_TestSuite_Lab7::GenerateTree() {
	myBST* bst = new myBST;
	
	// Allocate all nodes
	myNode* val50 = new myNode(50);
	myNode* val25 = new myNode(25);
	myNode* val75 = new myNode(75);
	myNode* val10 = new myNode(10);
	myNode* val35 = new myNode(35);
	myNode* val65 = new myNode(65);
	myNode* val100 = new myNode(100);
	myNode* val15 = new myNode(15);
	myNode* val60 = new myNode(60);
	myNode* val80 = new myNode(80);

	// Manually linking all nodes
	val50->left = val25;	val50->right = val75;	val50->parent = nullptr;
	val25->left = val10;	val25->right = val35;	val25->parent = val50;
	val75->left = val65;	val75->right = val100;	val75->parent = val50;
	val10->left = nullptr;	val10->right = val15;	val10->parent = val25;
	val35->left = nullptr;	val35->right = nullptr;	val35->parent = val25;
	val65->left = val60;	val65->right = nullptr;	val65->parent = val75;
	val100->left = val80;	val100->right = nullptr; val100->parent = val75;
	val15->left = nullptr;	val15->right = nullptr;	val15->parent = val10;
	val60->left = nullptr;	val60->right = nullptr;	val60->parent = val65;
	val80->left = nullptr;	val80->right = nullptr;	val80->parent = val100;

	bst->mRoot = val50;

	/*
	bst->mRoot = new myNode(50);
	bst->mRoot->left = new myNode(25);
	bst->mRoot->left->left = new myNode(10);
	bst->mRoot->left->right = new myNode(35);
	bst->mRoot->left->left->right = new myNode(15);
	bst->mRoot->right = new myNode(75);
	bst->mRoot->right->left = new myNode(65);
	bst->mRoot->right->left->left = new myNode(60);
	bst->mRoot->right->right = new myNode(100);
	bst->mRoot->right->right->left = new myNode(80);
	*/

	/*
						50
						/\
				25				75
				/\				/\
			10		35		65		100
			  \				/		/
				15		   60	  80

	*/

	return bst;
}

void DSA_TestSuite_Lab7::GetNodes(myNode* _node, std::vector<myNode*>& _vec) {
	if (_node) {
		_vec.push_back(_node);
		GetNodes(_node->left, _vec);
		GetNodes(_node->right, _vec);
	}
}



void DSA_TestSuite_Lab7::DisplayNode(int _val, const myNode* _left, const myNode* _right, const myNode& _node) {
	std::cout << "\t\tExpected Values\t\tYour Values\n"
		<< "data:\t\t" << _val << "\t\t\t" << _node.data << '\n';
	std::cout << "left:\t\t" << _left << "\t" << _node.left << '\n';
	std::cout << "right:\t\t" << _right << "\t" << _node.right << '\n';
}

/* DisplayTree functionality originally from 
	https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
*/
void DSA_TestSuite_Lab7::DisplayTree(const std::string& _prefix, const myNode* _node, bool _isLeft) {
	if (_node != nullptr)     {
		std::cout << _prefix;

		std::cout << (!_isLeft ? "R--" : "L__");

		// print the value of the node
		std::cout << _node->data << std::endl;

		// enter the next tree level - left and right branch
		DisplayTree(_prefix + (!_isLeft ? "|   " : "    "), _node->right, false);
		DisplayTree(_prefix + (!_isLeft ? "|   " : "    "), _node->left, true);
	}
}

void DSA_TestSuite_Lab7::DisplayTree(const myNode* _node) {
	DisplayTree("", _node, false);
}


#if BST_CTOR
void DSA_TestSuite_Lab7::BSTDefaultConstructor() {
	std::cout << "Testing default constructor\n";
	myBST bst;

	if (verboseMode)
		std::cout << "No verbose data for this test (non-verbose ouput is sufficient)\n";

	// Error testing
	if (bst.mRoot)
		PrintMessage("Root should be null");
	if(metrics.inUse)
		PrintMessage("No memory should be allocated to an empty tree");

	// Testing for success
	if (nullptr == bst.mRoot &&
		0 == metrics.inUse)
		PrintMessage();
}
#endif	// End BST_CTOR

#if BST_NODE_CTOR
void DSA_TestSuite_Lab7::BSTNodeConstructor() {
	std::cout << "Testing BST::Node constructor with valid node parameters\n";

	int randVal = rand() % 100 + 1;

	myNode node(randVal);

	if (verboseMode)
		DisplayNode(randVal, nullptr, nullptr, node);

	if (randVal != node.data)
		PrintMessage("Data in node is incorrect");
	if (node.left || node.right)
		PrintMessage("Node is not a leaf node");

	// Success
	if (randVal == node.data &&
		!node.left &&
		!node.right)
		PrintMessage();
}
#endif	// End BST_NODE_CTOR

#if BST_COPY_CTOR
void DSA_TestSuite_Lab7::BSTCopyConstructor() {
	std::cout << "Testing copy constructor\n";

	// Creating an initial tree
	myBST* original = GenerateTree();
	std::vector<myNode*> origVec;
	GetNodes(original->mRoot, origVec);

	size_t memoryOriginal = metrics.inUse;

	// Calling copy constructor
	myBST copy(*original);

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(original->mRoot);
		std::cout << "\n\t\tYours\n";
		DisplayTree(copy.mRoot);
		std::cout << '\n';
	}

	std::vector<myNode*> copyVec;
	GetNodes(copy.mRoot, copyVec);

	size_t memoryUsed = metrics.inUse;
	size_t correctMemory = memoryOriginal * 2 - sizeof(myBST*);

	bool deepCopies = true;
	bool identicalValues = true;

	// Error testing
	if (origVec.size() != copyVec.size())
		PrintMessage("Entire tree was not copied");
	else {
		for (size_t i = 0; i < origVec.size(); ++i) {
			if (origVec[i] == copyVec[i]) {
				PrintMessage("BST is using shallow copies");
				deepCopies = false;
				break;
			}
			if (origVec[i]->data != copyVec[i]->data) {
				PrintMessage("One (or more) nodes have the incorrect value");
				identicalValues = false;
				break;
			}
		}
	}
	if (memoryUsed < correctMemory)
		PrintMessage("Not enough memory allocated (did you not allocate memory for each node?)");
	else if (memoryUsed > correctMemory)
		PrintMessage("Too much memory allocated (too many nodes allocated)");

	// Testing for success
	if (origVec.size() == copyVec.size() &&
		deepCopies && identicalValues &&
		metrics.inUse == correctMemory)
		PrintMessage();

	// Clean up
	delete original;

}
#endif	// End BST_COPY_CTOR

#if BST_ASSIGNMENT_OP
void DSA_TestSuite_Lab7::BSTAssignmentOperator() {
	std::cout << "Testing assignment operator\n";

	// Creating an initial tree
	myBST* original = GenerateTree();
	std::vector<myNode*> origVec;
	GetNodes(original->mRoot, origVec);

	size_t memoryOriginal = metrics.inUse;

	// Calling assignment operator
	myBST assign;
	assign = *original;

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(original->mRoot);
		std::cout << "\n\t\tYours\n";
		DisplayTree(assign.mRoot);
		std::cout << '\n';
	}

	std::vector<myNode*> copyVec;
	GetNodes(assign.mRoot, copyVec);

	size_t memoryUsed = metrics.inUse;
	size_t correctMemory = memoryOriginal * 2 - sizeof(myBST*);

	bool deepCopies = true;
	bool identicalValues = true;

	// Error testing
	if (origVec.size() != copyVec.size())
		PrintMessage("Entire tree was not copied");
	else {
		for (size_t i = 0; i < origVec.size(); ++i) {
			if (origVec[i] == copyVec[i]) {
				PrintMessage("BST is using shallow copies");
				deepCopies = false;
				break;
			}
			if (origVec[i]->data != copyVec[i]->data) {
				PrintMessage("One (or more) nodes have the incorrect value");
				identicalValues = false;
				break;
			}
		}
	}
	if (memoryUsed < correctMemory)
		PrintMessage("Not enough memory allocated (did you not allocate memory for each node?)");
	else if (memoryUsed > correctMemory)
		PrintMessage("Too much memory allocated (did you not clean up old nodes before re-allocating?)");

	// Testing for success
	if (origVec.size() == copyVec.size() &&
		deepCopies && identicalValues &&
		metrics.inUse == correctMemory)
		PrintMessage();

	// Clean up
	delete original;
}
#endif	// End BST_ASSIGNMENT_OP

#if BST_CLEAR
void DSA_TestSuite_Lab7::BSTClear() {
	std::cout << "Testing Clear\n";

	myBST* bst = GenerateTree();

	size_t memoryUsed = metrics.inUse;

	bst->Clear();

	// Error testing
	if (metrics.inUse == memoryUsed - sizeof(myNode*))
		PrintMessage("Only one node deleted.   Did you just delete root?");
	if (metrics.inUse > sizeof(myBST*))
		PrintMessage("Not all nodes were cleared");
	if (bst->mRoot != nullptr)
		PrintMessage("root was not set back to null");

	// Testing for success
	if (metrics.inUse == sizeof(myNode*) &&
		nullptr == bst->mRoot)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_CLEAR

#if BST_DTOR
void DSA_TestSuite_Lab7::BSTDestructor() {
	std::cout << "Testing destructor\n";

	myBST* bst = GenerateTree();

	size_t memoryUsed = metrics.inUse;

	bst->Clear();

	// Error testing
	if (metrics.inUse == memoryUsed - sizeof(myNode*))
		PrintMessage("Only one node deleted.   Did you just delete root?");
	if (metrics.inUse > sizeof(myBST*))
		PrintMessage("Not all nodes were cleared");

	// Testing for success
	if (metrics.inUse == sizeof(myNode*))
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_DTOR

#if BST_PUSH_ROOT
void DSA_TestSuite_Lab7::BSTPushRoot() {
	std::cout << "Testing Push on an empty tree\n";
	int randomVal = rand() % 99 + 1;

	myNode rootOnly(randomVal);

	myBST bst;
	bst.Push(randomVal);

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(&rootOnly);
		std::cout << "\n\t\tYours\n";
		DisplayTree(bst.mRoot);
	}

	// Error testing
	if (0 == metrics.inUse)
		PrintMessage("No dynamic memory was allocated");
	if (metrics.inUse > sizeof(myNode))
		PrintMessage("Too much memory was allocated (should only allocate one node)");
	if (nullptr == bst.mRoot)
		PrintMessage("Root was not set to allocated node");
	if (bst.mRoot->data != randomVal)
		PrintMessage("Node's value is incorrect");
	if (nullptr != bst.mRoot->left || nullptr != bst.mRoot->right)
		PrintMessage("Node is not set as a leaf node");
	if (nullptr != bst.mRoot->parent)
		PrintMessage("Root's parent should be null");

	// Testing for success
	if (metrics.inUse == sizeof(myNode) &&
		bst.mRoot &&
		bst.mRoot->data == randomVal &&
		nullptr == bst.mRoot->left &&
		nullptr == bst.mRoot->right &&
		nullptr == bst.mRoot->parent)
		PrintMessage();
}
#endif	// BST_PUSH_ROOT

#if BST_PUSH_ROOT_LEFT
void DSA_TestSuite_Lab7::BSTPushRootLeft() {
	std::cout << "Testing Push on a tree with only a root node (left)\n";

	// Setting up two nodes
	int rootVal = rand() % 50 + 50;
	int leftVal = rand() % rootVal + 1;
	myNode rootNode(rootVal), leftNode(leftVal);
	rootNode.left = &leftNode;

	myBST bst;
	bst.Push(rootVal);
	myNode* rootAddress = bst.mRoot;

	// Pushing left node
	bst.Push(leftVal);
	myNode* left = bst.mRoot->left;

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(&rootNode);
		std::cout << "\n\t\tYours\n";
		DisplayTree(bst.mRoot);
	}

	// Error testing
	if (0 == metrics.inUse)
		PrintMessage("No dynamic memory was allocated");
	if (metrics.inUse > sizeof(myNode)*2)
		PrintMessage("Too much memory was allocated (should only allocate one node)");
	if (nullptr == bst.mRoot)
		PrintMessage("Root should not be null");
	if (rootAddress != bst.mRoot)
		PrintMessage("Root's address should not be changed");
	if (nullptr == bst.mRoot->left)
		PrintMessage("New node was not linked to root's left");
	else {
		if (left->data != leftVal)
			PrintMessage("Newly added node's value is incorrect");
		if (nullptr != left->left || nullptr != left->right)
			PrintMessage("Node is not set as a leaf node");
		if (bst.mRoot != left->parent)
			PrintMessage("Node's parent is incorrect");
	}

	// Testing for success
	if (metrics.inUse == sizeof(myNode) * 2 &&
		bst.mRoot == rootAddress &&
		left && left->data == leftVal &&
		nullptr == left->left && nullptr == left->right &&
		left->parent == bst.mRoot)
		PrintMessage();

}
#endif	// End BST_PUSH_ROOT_LEFT

#if BST_PUSH_ROOT_RIGHT
void DSA_TestSuite_Lab7::BSTPushRootRight() {
	std::cout << "Testing Push on a tree with only a root node (right)\n";

	// Setting up two nodes
	int rootVal = rand() % 50 + 1;
	int leftVal = rand() % 50 + rootVal;
	myNode rootNode(rootVal), rightNode(leftVal);
	rootNode.right = &rightNode;

	myBST bst;
	bst.Push(rootVal);
	myNode* rootAddress = bst.mRoot;

	// Pushing left node
	bst.Push(leftVal);
	myNode* right = bst.mRoot->right;

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(&rootNode);
		std::cout << "\n\t\tYours\n";
		DisplayTree(bst.mRoot);
	}

	// Error testing
	if (0 == metrics.inUse)
		PrintMessage("No dynamic memory was allocated");
	if (metrics.inUse > sizeof(myNode) * 2)
		PrintMessage("Too much memory was allocated (should only allocate one node)");
	if (nullptr == bst.mRoot)
		PrintMessage("Root should not be null");
	if (rootAddress != bst.mRoot)
		PrintMessage("Root's address should not be changed");
	if (nullptr == bst.mRoot->right)
		PrintMessage("New node was not linked to root's right");
	else {
		if (right->data != leftVal)
			PrintMessage("Newly added node's value is incorrect");
		if (nullptr != right->left || nullptr != right->right)
			PrintMessage("Node is not set as a leaf node");
		if (bst.mRoot != right->parent)
			PrintMessage("Node's parent is incorrect");
	}

	// Testing for success
	if (metrics.inUse == sizeof(myNode) * 2 &&
		bst.mRoot == rootAddress &&
		right && right->data == leftVal &&
		nullptr == right->left && nullptr == right->right &&
		right->parent == bst.mRoot)
		PrintMessage();
}
#endif	// End BST_PUSH_ROOT_RIGHT

#if BST_PUSH_LEFT
void DSA_TestSuite_Lab7::BSTPushLeft() {
	std::cout << "Testing Push on a left Node not connected to the root\n";

	// Setting up three nodes
	int rootVal = rand() % 50 + 50;
	int rootLeftVal = rand() % 25 + 10;
	int childVal = rand() % 10;

	myNode root(rootVal);
	myNode rootLeft(rootLeftVal, &root);
	myNode child(childVal, &rootLeft);
	root.left = &rootLeft;
	rootLeft.left = &child;

	myBST bst;

	bst.Push(rootVal);
	bst.Push(rootLeftVal);
	bst.Push(childVal);

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(&root);
		std::cout << "\n\t\tYours\n";
		DisplayTree(bst.mRoot);
	}

	// Error testing
	myNode* addedNode = nullptr;
	if (0 == metrics.inUse)
		PrintMessage("No dynamic memory was allocated");
	if (metrics.inUse > sizeof(myNode) * 3)
		PrintMessage("Too much memory was allocated (should only allocate one node)");
	if (nullptr == bst.mRoot)
		PrintMessage("Root should not be null");
	if (bst.mRoot && bst.mRoot->left && nullptr == bst.mRoot->left->left)
		PrintMessage("Newly created node is not attached in tree at correct location (or at all)");
	else {
		addedNode = bst.mRoot->left->left;
		if (addedNode->data != childVal)
			PrintMessage("Value of new node is incorrect");
		if(addedNode->left != nullptr || addedNode->right != nullptr) 
			PrintMessage("Node is not set as a leaf node");
		if(addedNode->parent != bst.mRoot->left)
			PrintMessage("Node's parent is incorrect");
	}

	// Test for success
	if (metrics.inUse == sizeof(myNode) * 3 &&
		bst.mRoot && bst.mRoot->left && bst.mRoot->left->left &&
		childVal == addedNode->data &&
		nullptr == addedNode->left && nullptr == addedNode->right &&
		addedNode->parent == bst.mRoot->left)
		PrintMessage();
}
#endif	// End BST_PUSH_LEFT

#if BST_PUSH_RIGHT
void DSA_TestSuite_Lab7::BSTPushRight() {
	std::cout << "Testing Push on a left Node not connected to the root\n";

	// Setting up three nodes
	int rootVal = rand() % 50 + 50;
	int rootLeftVal = rand() % 10;
	int childVal = rand() % 10 + 10;

	myNode root(rootVal);
	myNode rootLeft(rootLeftVal, &root);
	myNode child(childVal, &rootLeft);
	root.left = &rootLeft;
	rootLeft.right = &child;

	myBST bst;

	bst.Push(rootVal);
	bst.Push(rootLeftVal);
	bst.Push(childVal);

	if (verboseMode) {
		std::cout << "\t\tExpected\n";
		DisplayTree(&root);
		std::cout << "\n\t\tYours\n";
		DisplayTree(bst.mRoot);
	}

	// Error testing
	myNode* addedNode = nullptr;
	if (0 == metrics.inUse)
		PrintMessage("No dynamic memory was allocated");
	if (metrics.inUse > sizeof(myNode) * 3)
		PrintMessage("Too much memory was allocated (should only allocate one node)");
	if (nullptr == bst.mRoot)
		PrintMessage("Root should not be null");
	if (bst.mRoot && bst.mRoot->left && nullptr == bst.mRoot->left->right)
		PrintMessage("Newly created node is not attached in tree at correct location (or at all)");
	else {
		addedNode = bst.mRoot->left->right;
		if (addedNode->data != childVal)
			PrintMessage("Value of new node is incorrect");
		if (addedNode->left != nullptr || addedNode->right != nullptr)
			PrintMessage("Node is not set as a leaf node");
		if (addedNode->parent != bst.mRoot->left)
			PrintMessage("Node's parent is incorrect");
	}

	// Test for success
	if (metrics.inUse == sizeof(myNode) * 3 &&
		bst.mRoot && bst.mRoot->left && bst.mRoot->left->right &&
		childVal == addedNode->data &&
		nullptr == addedNode->left && nullptr == addedNode->right &&
		addedNode->parent == bst.mRoot->left)
		PrintMessage();
}
#endif	// End BST_PUSH_RIGHT

#if BST_CONTAINS_TRUE
void DSA_TestSuite_Lab7::BSTContainsTrue() {
	BST<int>* bst = GenerateTree();
	std::vector<myNode*> nodes;
	GetNodes(bst->mRoot, nodes);
	int containsVal = nodes[rand() % nodes.size()]->data;
	std::cout << "Testing Contains on a value that is present in the list (" << containsVal << ")\n";

	bool found = bst->Contains(containsVal);

	if (verboseMode) {
		std::cout << "Yours\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (!found)
		PrintMessage("Contains returned false (value was in tree)");

	// Success
	if (found)
		PrintMessage();

	delete bst;
}
#endif	// End BST_CONTAINS_TRUE

#if BST_CONTAINS_FALSE
void DSA_TestSuite_Lab7::BSTContainsFalse() {
	BST<int>* bst = GenerateTree();
	std::vector<myNode*> nodes;
	GetNodes(bst->mRoot, nodes);
	int containsVal = nodes[rand() % nodes.size()]->data + rand()% 4 + 1;
	std::cout << "Testing Contains on a value that is not present in the list (" << containsVal << ")\n";

	bool found = bst->Contains(containsVal);

	if (verboseMode) {
		std::cout << "Yours\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (found)
		PrintMessage("Contains returned true (value was in tree)");

	// Success
	if (!found)
		PrintMessage();

	delete bst;
}
#endif	BST_CONTAINS_FALSE

#if BST_REMOVE_CASE0_ROOT
void DSA_TestSuite_Lab7::BSTRemoveCase0Root() {
	std::cout << "Testing RemoveCase0 on root\n";

	// Setting up tree for testing
	myBST bst;
	bst.mRoot = new myNode(50);

	bst.RemoveCase0(bst.mRoot);

	if(verboseMode)
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (metrics.inUse != 0)
		PrintMessage("Node was not deleted");
	if (bst.mRoot != nullptr)
		PrintMessage("Root was not set back to null");


	// Testing for success
	if (0 == metrics.inUse &&
		nullptr == bst.mRoot)
		PrintMessage();


}
#endif	// End BST_REMOVE_CASE0_ROOT

#if BST_REMOVE_CASE0_LEFT
void DSA_TestSuite_Lab7::BSTRemoveCase0Left() {
	std::cout << "Testing RemoveCase0 on non-root left child (60)\n";

	// Setting up tree for testing
	myBST* bst = GenerateTree();
	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* parent = bst->mRoot->right->left;
	myNode* nodeToRemove = parent->left;
	
	bst->RemoveCase0(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (parent->left != nullptr)
		PrintMessage("Parent of deleted node did not update its left pointer");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		nullptr == parent->left)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE0_LEFT

#if BST_REMOVE_CASE0_RIGHT
void DSA_TestSuite_Lab7::BSTRemoveCase0Right() {
	std::cout << "Testing RemoveCase0 on non-root right child (15)\n";

	// Setting up tree for testing
	myBST* bst = GenerateTree();
	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* parent = bst->mRoot->left->left;
	myNode* nodeToRemove = parent->right;

	bst->RemoveCase0(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (parent->right != nullptr)
		PrintMessage("Parent of deleted node did not update its right pointer");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		nullptr == parent->right)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE0_RIGHT

#if BST_REMOVE_CASE1_ROOT_LEFT
void DSA_TestSuite_Lab7::BSTRemoveCase1RootLeft() {
	std::cout << "Testing RemoveCase1 on root with left child (50)\n";

	// Generating test tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val25 = new myNode(25);
	myNode* val10 = new myNode(10);
	myNode* val35 = new myNode(35);
	myNode* val15 = new myNode(15);
	val50->left = val25;	val50->right = nullptr;	val50->parent = nullptr;
	val25->left = val10;	val25->right = val35;	val25->parent = val50;
	val10->left = nullptr;	val10->right = val15;	val10->parent = val15;
	val35->left = nullptr;	val35->right = nullptr;	val35->parent = val25;
	val15->left = nullptr;	val15->right = nullptr;	val15->parent = val10;
	bst->mRoot = val50;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	bst->RemoveCase1(bst->mRoot);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (bst->mRoot != val25)
		PrintMessage("Root was not updated to left node");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		nullptr == bst->mRoot->parent)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE1_ROOT_LEFT

#if BST_REMOVE_CASE1_ROOT_RIGHT
void DSA_TestSuite_Lab7::BSTRemoveCase1RootRight() {
	std::cout << "Testing RemoveCase1 on root with right child (50)\n";

	// Generating test tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val75 = new myNode(75);
	myNode* val65 = new myNode(65);
	myNode* val100 = new myNode(100);
	myNode* val60 = new myNode(60);
	myNode* val80 = new myNode(80);
	val50->left = nullptr;	val50->right = val75;	val50->parent = nullptr;
	val75->left = val65;	val75->right = val100;	val75->parent = val50;
	val65->left = val60;	val65->right = nullptr;	val65->parent = val75;
	val100->left = val80;	val100->right = nullptr; val100->parent = val75;
	val60->left = nullptr;	val60->right = nullptr;	val60->parent = val65;
	val80->left = nullptr;	val80->right = nullptr;	val80->parent = val100;
	bst->mRoot = val50;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	bst->RemoveCase1(bst->mRoot);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (bst->mRoot != val75)
		PrintMessage("Root was not updated to right node");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		nullptr == bst->mRoot->parent)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE1_ROOT_RIGHT

#if BST_REMOVE_CASE1_LEFT_LEFT
void DSA_TestSuite_Lab7::BSTRemoveCase1LeftLeft() {
	std::cout << "Testing RemoveCase1 on non-root left node that has a left child (65)\n";

	// Generating tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val75 = new myNode(75);
	myNode* val65 = new myNode(65);
	myNode* val100 = new myNode(100);
	myNode* val60 = new myNode(60);
	myNode* val80 = new myNode(80);
	myNode* val55 = new myNode(55);
	val50->left = nullptr;	val50->right = val75;	val50->parent = nullptr;
	val75->left = val65;	val75->right = val100;	val75->parent = val50;
	val65->left = val60;	val65->right = nullptr;	val65->parent = val75;
	val100->left = val80;	val100->right = nullptr; val100->parent = val75;
	val60->left = val55;	val60->right = nullptr;	val60->parent = val65;
	val80->left = nullptr;	val80->right = nullptr;	val80->parent = val100;
	val55->left = nullptr;	val55->right = nullptr; val55->parent = val60;
	bst->mRoot = val50;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = val65;
	myNode* parent = nodeToRemove->parent;
	myNode* child = nodeToRemove->left;

	bst->RemoveCase1(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (parent->left != child)
		PrintMessage("Parent's left pointer was not set to node after removed node");
	if (child->parent != parent)
		PrintMessage("Node after removed node's parent was not set to removed node's parent");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		parent->left == child &&
		child->parent == parent)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE1_LEFT_LEFT

#if BST_REMOVE_CASE1_LEFT_RIGHT
void DSA_TestSuite_Lab7::BSTRemoveCase1LeftRight() {
	std::cout << "Testing RemoveCase1 on non-root left node that has a right child (10)\n";

	// Generating tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val25 = new myNode(25);
	myNode* val10 = new myNode(10);
	myNode* val35 = new myNode(35);
	myNode* val15 = new myNode(15);
	myNode* val20 = new myNode(20);
	bst->mRoot = val50;

	val50->left = val25;	val50->right = nullptr;	val50->parent = nullptr;
	val25->left = val10;	val25->right = val35;	val25->parent = val50;
	val10->left = nullptr;	val10->right = val15;	val10->parent = val25;
	val35->left = nullptr;	val35->right = nullptr;	val35->parent = val25;
	val15->left = nullptr;	val15->right = val20;	val15->parent = val10;
	val20->left = nullptr;	val20->right = nullptr;	val20->parent = val15;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = val15;
	myNode* parent = nodeToRemove->parent;
	myNode* child = nodeToRemove->right;

	bst->RemoveCase1(nodeToRemove);

	if (verboseMode) {
		std::cout << "\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if(metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if(parent->right != child)
		PrintMessage("Parent's left pointer was not set to node after removed node");
	if (child->parent != parent)
		PrintMessage("Node after removed node's parent was not set to removed node's parent");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		parent->right == child &&
		child->parent == parent)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE1_LEFT_RIGHT

#if BST_REMOVE_CASE1_RIGHT_LEFT
void DSA_TestSuite_Lab7::BSTRemoveCase1RightLeft() {
	std::cout << "Testing RemoveCase1 on non-root right node that has a left child (100)\n";

	// Generating tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val75 = new myNode(75);
	myNode* val65 = new myNode(65);
	myNode* val100 = new myNode(100);
	myNode* val60 = new myNode(60);
	myNode* val80 = new myNode(80);
	val50->left = nullptr;	val50->right = val75;	val50->parent = nullptr;
	val75->left = val65;	val75->right = val100;	val75->parent = val50;
	val65->left = val60;	val65->right = nullptr;	val65->parent = val75;
	val100->left = val80;	val100->right = nullptr; val100->parent = val75;
	val60->left = nullptr;	val60->right = nullptr;	val60->parent = val65;
	val80->left = nullptr;	val80->right = nullptr;	val80->parent = val100;
	bst->mRoot = val50;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = val100;
	myNode* parent = nodeToRemove->parent;
	myNode* child = nodeToRemove->left;

	bst->RemoveCase1(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (parent->right != child)
		PrintMessage("Parent's right pointer was not set to node after removed node");
	if (child->parent != parent)
		PrintMessage("Node after removed node's parent was not set to removed node's parent");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		parent->right == child &&
		child->parent == parent)
		PrintMessage();

	// Clean up
	delete bst;

}
#endif	// End BST_REMOVE_CASE1_RIGHT_LEFT

#if BST_REMOVE_CASE1_RIGHT_RIGHT
void DSA_TestSuite_Lab7::BSTRemoveCase1RightRight() {
	std::cout << "Testing RemoveCase1 on non-root right node that has a right child (35)\n";

	// Generating tree
	myBST* bst = new myBST;
	myNode* val50 = new myNode(50);
	myNode* val25 = new myNode(25);
	myNode* val10 = new myNode(10);
	myNode* val35 = new myNode(35);
	myNode* val15 = new myNode(15);
	myNode* val40 = new myNode(40);
	bst->mRoot = val50;

	val50->left = val25;	val50->right = nullptr;	val50->parent = nullptr;
	val25->left = val10;	val25->right = val35;	val25->parent = val50;
	val10->left = nullptr;	val10->right = val15;	val10->parent = val15;
	val35->left = nullptr;	val35->right = val40;	val35->parent = val25;
	val15->left = nullptr;	val15->right = nullptr;	val15->parent = val10;
	val40->left = nullptr;	val40->right = nullptr;	val40->parent = val35;

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = val35;
	myNode* parent = nodeToRemove->parent;
	myNode* child = nodeToRemove->right;

	bst->RemoveCase1(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (parent->right != child)
		PrintMessage("Parent's right pointer was not set to node after removed node");
	if (child->parent != parent)
		PrintMessage("Node after removed node's parent was not set to removed node's parent");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		parent->right == child &&
		child->parent == parent)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE1_RIGHT_RIGHT_NOSUBTREE

#if BST_REMOVE_CASE2_SUBTREE
void DSA_TestSuite_Lab7::BSTRemoveCase2Subtree() {
	std::cout << "Testing RemoveCase2 on node that contains subtree (75)\n";

	myBST* bst = GenerateTree();

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = bst->mRoot->right;
	myNode* nodeToCheck = nodeToRemove->right;

	bst->RemoveCase2(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (nodeToRemove->data != 80)
		PrintMessage("Node's value was not replaced with next lowest value in tree");
	if (nodeToCheck->right != nullptr)
		PrintMessage("Next lowest node was not removed from tree");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		80 == nodeToRemove->data &&
		nullptr == nodeToCheck->right)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	BST_REMOVE_CASE2_SUBTREE

#if BST_REMOVE_CASE2_NO_SUBTREE
void DSA_TestSuite_Lab7::BSTRemoveCase2NonRootNoSubtree() {
	std::cout << "Testing RemoveCase2 on node that contains subtree (25)\n";

	myBST* bst = GenerateTree();

	size_t memoryUsed = metrics.inUse;

	if (verboseMode) {
		std::cout << "\t\tYours Before\n";
		DisplayTree(bst->mRoot);
	}

	myNode* nodeToRemove = bst->mRoot->left;

	bst->RemoveCase2(nodeToRemove);

	if (verboseMode) {
		std::cout << "\n\t\tYours After\n";
		DisplayTree(bst->mRoot);
	}

	// Error testing
	if (metrics.inUse > memoryUsed - sizeof(myNode))
		PrintMessage("Incorrect amount of memory (did you not delete the node?)");
	if (nodeToRemove->data != 35)
		PrintMessage("Node's value was not replaced with next lowest value in tree");
	if (nodeToRemove->right != nullptr)
		PrintMessage("Next lowest node was not removed from tree");

	// Testing for success
	if (metrics.inUse == memoryUsed - sizeof(myNode) &&
		35 == nodeToRemove->data &&
		nullptr == nodeToRemove->right)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_CASE2_NO_SUBTREE

#if BST_REMOVE
void DSA_TestSuite_Lab7::BSTRemove() {
	std::cout << "Testing Remove for Case 0/1/2\n";

	myBST* bstCase0 = GenerateTree();
	myBST* bstCase1 = GenerateTree();
	myBST* bstCase2 = GenerateTree();

	const int numCase0 = 4, numCase1 = 3, numCase2 = 3;
	int case0Nodes[numCase0] = { 15, 35, 60, 80 };
	int case1Nodes[numCase1] = { 10, 65, 100 };
	int case2Nodes[numCase2] = { 25, 50, 75 };

	int case0ToRemove = case0Nodes[rand() % numCase0];
	int case1ToRemove = case1Nodes[rand() % numCase1];
	int case2ToRemove = case2Nodes[rand() % numCase2];

	bool case0Removed = bstCase0->Remove(75);
	bool case1Removed = bstCase1->Remove(case1ToRemove);
	bool case2Removed = bstCase2->Remove(case2ToRemove);

	if(verboseMode)
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (false == case0Removed)
		PrintMessage("Case 0 node was not removed (incorrect if check?)");
	if (false == case1Removed)
		PrintMessage("Case 1 node was not removed (incorrect if check?)");
	if (false == case2Removed)
		PrintMessage("Case 2 node was not removed (incorrect if check?)");

	// Testing for success
	if (case0Removed &&
		case1Removed &&
		case2Removed)
		PrintMessage();

	// Clean up
	delete bstCase0;
	delete bstCase1;
	delete bstCase2;

}
#endif	// End BST_REMOVE

#if BST_REMOVE_NOT_FOUND
void DSA_TestSuite_Lab7::BSTRemoveNotFound() {
	std::cout << "Testing Remove for a value not in tree\n";

	myBST* bst = GenerateTree();

	int valueNotFound = rand() % 100 + 101;

	bool removed = bst->Remove(valueNotFound);

	if (verboseMode)
		std::cout << "No additional information to display for this test\n";

	// Error testing
	if (true == removed)
		PrintMessage("Remove returned true when no node was removed");

	// Testing for success
	if (false == removed)
		PrintMessage();

	// Clean up
	delete bst;
}
#endif	// End BST_REMOVE_NOT_FOUND

#if BST_IN_ORDER_TRAVERSAL
void DSA_TestSuite_Lab7::BSTInOrderTraversal() {
	std::cout << "Testing in-order traversal\n";

	BST<int>* bst = GenerateTree();
	std::string inOrderStr = "10 15 25 35 50 60 65 75 80 100";

	std::string result = bst->InOrder();

	if (verboseMode)
		std::cout << "Expected:\t" << inOrderStr << '\n'
				<< "Yours:\t\t" << result << '\n';

	if (result[result.size() - 1] == ' ')
		PrintMessage("String has a trailing space");
	else if (result != inOrderStr)
		PrintMessage("Method not returning string in correct order");

	// Success
	if (result == inOrderStr)
		PrintMessage();

	delete bst;
}
#endif	BST_IN_ORDER_TRAVERSAL

#endif	// End LAB_7