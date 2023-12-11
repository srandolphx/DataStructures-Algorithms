/*
File:			DSA_Main.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	03.21.2021
Purpose:		Main file for SDV2213 Labs
				Contains menu code and calls to all unit tests
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE BEYOND 
				CHECKING FOR MEMORY LEAKS
*/

/************/
/* Includes */
/************/
#include <ctime>
#include <iostream>
#include "DSA_TestSuite_Lab1.h"
#include "DSA_TestSuite_Lab2.h"
#include "DSA_TestSuite_Lab3.h"
#include "DSA_TestSuite_Lab4.h"
#include "DSA_TestSuite_Lab5.h"
#include "DSA_TestSuite_Lab6.h"
#include "DSA_TestSuite_Lab7.h"
#include "DSA_TestSuite_Lab8.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

/***********/
/* Defines */
/***********/

// Enables memory leak detection
#define _CRTDBG_MAP_ALLOC


#define LAB1	'1'
#define LAB2	'2'
#define LAB3	'3'
#define LAB4	'4'
#define LAB5	'5'
#define LAB6	'6'
#define LAB7	'7'
#define LAB8	'8'
#define EXIT	'0'
#define VERBOSE 'T'

/*************/
/* Prototypes*/
/*************/

// Displays the lab option menu to the console window
void DisplayMenu();

// Runs the Lab 1 Unit Tests
void Lab1Tests();

// Runs the Lab 2 Unit Tests
void Lab2Tests();

// Runs the Lab 3 Unit Tests
void Lab3Tests();

// Runs the Lab4 Unit Tests
void Lab4Tests();

// Runs the Lab5 Unit Tests
void Lab5Tests();

// Runs the Lab6 Unit Tests
void Lab6Tests();

// Runs the Lab7 Unit Tests
void Lab7Tests();

// Runs the Lab8 Unit Tests
void Lab8Tests();

// Entry point of the program
int main() {

	// Memory leak detection code
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// This function call will set a breakpoint at the location of a leaked block
	// Set the parameter to the identifier for a leaked block
	_CrtSetBreakAlloc(-1);

	// Seeding the random number generator
	srand(unsigned int(time(nullptr)));

	// Menu variables
	char choice = -1;
	bool exitLoop = false;

	// Main menu loop	
	while (!exitLoop) {

		// Clear the screen
		system("cls");

		if (sizeof(void*) != 8)
			std::cout << "Make sure you are running your program in x64 mode\n\n";

		DisplayMenu();

		// Input validation
		std::cout << "Lab Selection: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		choice = toupper(choice);

		if (EXIT == choice)
			break;

		system("cls");
		switch (choice) {
			case LAB1:
				Lab1Tests();
				system("pause");
				break;
			case LAB2:
				Lab2Tests();
				system("pause");
				break;
			case LAB3:
				Lab3Tests();
				system("pause");
				break;
			case LAB4:
				Lab4Tests();
				system("pause");
				break;
			case LAB5:
				Lab5Tests();
				system("pause");
				break;
			case LAB6:
				Lab6Tests();
				system("pause");
				break;
			case LAB7:
				Lab7Tests();
				system("pause");
				break;
			case LAB8:
				Lab8Tests();
				system("pause");
				break;
			case VERBOSE:
				verboseMode = !verboseMode;
				break;
			default:
				std::cout << "Invalid selection";
				break;
		}

		std::cout << "\n\n";
	}

	return 0;
}


// Displays the lab option menu to the console window
void DisplayMenu() {
	std::cout << "1) Lab 1 - DynArray\n"
			  << "2) Lab 2 - vector\n"
			  << "3) Lab 3 - DList\n"
			  << "4) Lab 4 - list\n"
			  << "5) Lab 5 - Dictionary\n"
			  << "6) Lab 6 - unordered_map\n"
			  << "7) Lab 7 - BST\n"
			  << "8) Lab 8 - Huffman compression\n"
			  << "0) Exit\n\n"
			  << "T) Toggle verbose mode " << (!verboseMode ? "on" : "off") << "\n";

}

// Runs the Lab 1 Unit Tests
void Lab1Tests() {
#if LAB_1

#if LAB1_DYNARRAY_DEFAULT_CTOR
	DSA_TestSuite_Lab1::DynArrayDefaultConstructorNoArgs();
#endif
#if LAB1_DYNARRAY_CONSTRUCTOR_WITH_ARGS
	DSA_TestSuite_Lab1::DynArrayDefaultConstructorWithArgs();
#endif
#if LAB1_DYNARRAY_BRACKET_OP_READ_ONLY_BUILT_IN
	DSA_TestSuite_Lab1::DynArrayBracketOperator_ReadOnly();
#endif
#if LAB1_DYNARRAY_BRACKET_OP_WRITE_BUILT_IN
	DSA_TestSuite_Lab1::DynArrayBracketOperator_Write();
#endif
#if LAB1_DYNARRAY_SIZE
	DSA_TestSuite_Lab1::DynArrayAccessors_Size();
#endif
#if LAB1_DYNARRAY_CAPACITY
	DSA_TestSuite_Lab1::DynArrayAccessors_Capacity();
#endif
#if LAB1_DYNARRAY_RESERVE_ZERO
	DSA_TestSuite_Lab1::DynArrayReserveZero();
#endif
#if LAB1_DYNARRAY_RESERVE_DOUBLE
	DSA_TestSuite_Lab1::DynArrayReserveDouble();
#endif
#if LAB1_DYNARRAY_RESERVE_VALUE
	DSA_TestSuite_Lab1::DynArrayReserveSpecific();
#endif
#if LAB1_DYNARRAY_RESERVE_SMALLER
	DSA_TestSuite_Lab1::DynArrayReserveSmaller();
#endif
#if LAB1_DYNARRAY_APPEND_NO_RESIZE
	DSA_TestSuite_Lab1::DynArrayAppendNoResize();
#endif
#if LAB1_DYNARRAY_APPEND_RESIZE
	DSA_TestSuite_Lab1::DynArrayAppendResize();
#endif
#if LAB1_DYNARRAY_CLEAR
	DSA_TestSuite_Lab1::DynArrayClear();
#endif
#if LAB1_DYNARRAY_DTOR
	DSA_TestSuite_Lab1::DynArrayDestructor();
#endif
#if LAB1_DYNARRAY_COPY_CTOR_BUILT_IN
	DSA_TestSuite_Lab1::DynArrayCopyConstructorInt();
#endif
#if LAB1_DYNARRAY_COPY_CTOR_CLASS
	DSA_TestSuite_Lab1::DynArrayCopyConstructorClass();
#endif
#if LAB1_DYNARRAY_ASSIGNMENT_BUILT_IN
	DSA_TestSuite_Lab1::DynArrayAssignmentOperatorInt();
#endif
#if LAB1_DYNARRAY_ASSIGNMENT_CLASS
	DSA_TestSuite_Lab1::DynArrayAssignmentOperatorClass();
#endif

#else
	std::cout << "LAB_1 is not toggled on in DynArray.h\n";
#endif	// End LAB_1
}

// Runs the Lab2 Unit Tests
void Lab2Tests() {
#if LAB_2

#if LAB2_PALINDROME_NUMBER
	DSA_TestSuite_Lab2::CheckForPalindrome();
#endif
#if LAB2_VECTOR_FILL_FILE
	DSA_TestSuite_Lab2::VectorFillFromFile();
#endif
#if LAB2_VECTOR_FILL_ARRAY
	DSA_TestSuite_Lab2::VectorFillFromArray();
#endif
#if LAB2_VECTOR_CLEAR
	DSA_TestSuite_Lab2::VectorClear();
#endif
#if LAB2_VECTOR_SORT_ASCENDING
	DSA_TestSuite_Lab2::VectorSortAscending();
#endif
#if LAB2_VECTOR_SORT_DESCENDING
	DSA_TestSuite_Lab2::VectorSortDescending();
#endif
#if LAB2_VECTOR_BRACKETS
	DSA_TestSuite_Lab2::VectorIndexing();
#endif
#if LAB2_VECTOR_CONTAINS_TRUE
	DSA_TestSuite_Lab2::VectorContainsTrue();
#endif
#if LAB2_VECTOR_CONTAINS_FALSE
	DSA_TestSuite_Lab2::VectorContainsFalse();
#endif
#if LAB2_VECTOR_MOVE_PALINDROME
	DSA_TestSuite_Lab2::VectorMovePalindrome();
#endif
#else
	std::cout << "LAB_2 is not toggled on in DSA_Lab2.h\n";
#endif	// End LAB_2
}

// Runs the Lab3 Unit Tests
void Lab3Tests() {
#if LAB_3
#if LIST_CTOR
	DSA_TestSuite_Lab3::LinkedListDefaultConstructor();
#endif
#if LIST_NODE_CTOR_DEFAULT
	DSA_TestSuite_Lab3::LinkedListNodeConstructorWithDefaults();
#endif
#if LIST_NODE_CTOR
	DSA_TestSuite_Lab3::LinkedListNodeConstructor();
#endif
#if LIST_ADDHEAD_EMPTY
	DSA_TestSuite_Lab3::LinkedListAddHeadEmpty();
#endif
#if LIST_ADDHEAD				
	DSA_TestSuite_Lab3::LinkedListAddHeadExisting();
#endif
#if LIST_ADDTAIL_EMPTY			
	DSA_TestSuite_Lab3::LinkedListAddTailEmpty();
#endif
#if LIST_ADDTAIL				
	DSA_TestSuite_Lab3::LinkedListAddTailExisting();
#endif
#if LIST_CLEAR					
	DSA_TestSuite_Lab3::LinkedListClear();
#endif
#if LIST_DTOR
	DSA_TestSuite_Lab3::LinkedListDestructor();
#endif
#if LIST_ITER_BEGIN				
	DSA_TestSuite_Lab3::LinkedListIterBegin();
#endif
#if LIST_ITER_END				
	DSA_TestSuite_Lab3::LinkedListIterEnd();
#endif
#if LIST_ITER_INCREMENT_PRE		
	DSA_TestSuite_Lab3::LinkedListIterPreIncrement();
#endif
#if LIST_ITER_INCREMENT_POST	
	DSA_TestSuite_Lab3::LinkedListIterPostIncrement();
#endif
#if LIST_ITER_DECREMENT_PRE		
	DSA_TestSuite_Lab3::LinkedListIterPreDecrement();
#endif
#if LIST_ITER_DECREMENT_POST	
	DSA_TestSuite_Lab3::LinkedListIterPostDecrement();
#endif
#if LIST_INSERT_EMPTY			
	DSA_TestSuite_Lab3::LinkedListInsertEmpty();
#endif
#if LIST_INSERT_HEAD			
	DSA_TestSuite_Lab3::LinkedListInsertHead();
#endif
#if LIST_INSERT					
	DSA_TestSuite_Lab3::LinkedListInsertMiddle();
#endif
#if LIST_ERASE_EMPTY			
	DSA_TestSuite_Lab3::LinkedListEraseEmpty();
#endif
#if LIST_ERASE_HEAD				
	DSA_TestSuite_Lab3::LinkedListEraseHead();
#endif
#if LIST_ERASE_TAIL				
	DSA_TestSuite_Lab3::LinkedListEraseTail();
#endif
#if LIST_ERASE					
	DSA_TestSuite_Lab3::LinkedListEraseMiddle();
#endif
#if LIST_COPY_CTOR_INT
	DSA_TestSuite_Lab3::LinkedListCopyConstructorInt();
#endif
#if LIST_COPY_CTOR_USER_DEFINED
	DSA_TestSuite_Lab3::LinkedListCopyConstructorClass();
#endif
#if LIST_ASSIGNMENT_OP_INT
	DSA_TestSuite_Lab3::LinkedListAssignmentOperatorInt();
#endif
#if LIST_ASSIGNMENT_OP_USER_DEFINED
	DSA_TestSuite_Lab3::LinkedListAssignmentOperatorClass();
#endif
#else
	std::cout << "LAB_3 is not toggled on in DList.h\n"; 
#endif	// End LAB_3
}

// Runs the Lab4 Unit Tests
void Lab4Tests() {
#if LAB_4
#if LIST_QUEUE_ADD
	DSA_TestSuite_Lab4::ListQueueAdd();
#endif
#if LIST_STACK_ADD
	DSA_TestSuite_Lab4::ListStackAdd();
#endif
#if LIST_QUEUE_REMOVE
	DSA_TestSuite_Lab4::ListQueueRemove();
#endif
#if LIST_STACK_REMOVE
	DSA_TestSuite_Lab4::ListStackRemove();
#endif
#if LIST_INSERT_INDEX
	DSA_TestSuite_Lab4::ListInsertIndex();
#endif
#if LIST_INSERT_ITER
	DSA_TestSuite_Lab4::ListInsertIterator();
#endif
#if LIST_REMOVE_DECIMAL
	DSA_TestSuite_Lab4::ListRemoveDecimal();
#endif
#else
	std::cout << "LAB_4 is not toggled on in DSA_Lab4.h\n";
#endif	// End LAB_4
}

// Runs the Lab5 Unit Tests
void Lab5Tests() {
#if LAB_5

#if DICT_CTOR
	DSA_TestSuite_Lab5::DictConstructor();
#endif
#if DICT_PAIR_CTOR
	DSA_TestSuite_Lab5::DictPairConstructor();
#endif
#if DICT_DTOR
	DSA_TestSuite_Lab5::DictDestructor();
#endif
#if DICT_CLEAR
	DSA_TestSuite_Lab5::DictClear();
#endif
#if DICT_INSERT
	DSA_TestSuite_Lab5::DictInsert();
#endif
#if DICT_INSERT_EXISTING
	DSA_TestSuite_Lab5::DictInsertOverwrite();
#endif
#if DICT_FIND
	DSA_TestSuite_Lab5::DictFind();
#endif
#if DICT_FIND_NOT_FOUND
	DSA_TestSuite_Lab5::DictFindNotFound();
#endif
#if DICT_REMOVE
	DSA_TestSuite_Lab5::DictRemove();
#endif
#if DICT_REMOVE_NOT_FOUND
	DSA_TestSuite_Lab5::DictRemoveNotFound();
#endif
#if DICT_ASSIGNMENT_OP
	DSA_TestSuite_Lab5::DictAssignmentOperator();
#endif
#if DICT_COPY_CTOR
	DSA_TestSuite_Lab5::DictCopyConstructor();
#endif

#else
	std::cout << "LAB_5 is not toggled on in Dictionary.h\n";
#endif	// End LAB_5
}

// Runs the Lab5 Unit Tests
void Lab6Tests() {
#if LAB_6
#if MAP_POPULATE_LETTER_VALUES
	DSA_TestSuite_Lab6::MapPopulateLetterValues();
#endif
#if MAP_GET_LETTER_VALUE
	DSA_TestSuite_Lab6::MapGetLetterValue();
#endif
#if MAP_GET_WORD_VALUE
	DSA_TestSuite_Lab6::MapGetWordValue();
#endif
#if MAP_CREATE_PAIR
	DSA_TestSuite_Lab6::MapCreatePair();
#endif
#if MAP_LOAD_FILE
	DSA_TestSuite_Lab6::MapLoadFile();
#endif
#if MAP_FIND_WORD_SCORE
	DSA_TestSuite_Lab6::MapFindWordScore();
#endif
#else
	std::cout << "LAB_6 is not toggled on in DSA_Lab6.h\n";
#endif // End LAB_6
}

void Lab7Tests() {
#if LAB_7
#if BST_CTOR
	DSA_TestSuite_Lab7::BSTDefaultConstructor();
#endif
#if BST_NODE_CTOR
	DSA_TestSuite_Lab7::BSTNodeConstructor();
#endif
#if BST_PUSH_ROOT
	DSA_TestSuite_Lab7::BSTPushRoot();
#endif
#if BST_PUSH_ROOT_LEFT
	DSA_TestSuite_Lab7::BSTPushRootLeft();
#endif
#if BST_PUSH_ROOT_RIGHT
	DSA_TestSuite_Lab7::BSTPushRootRight();
#endif
#if BST_PUSH_LEFT
	DSA_TestSuite_Lab7::BSTPushLeft();
#endif
#if BST_PUSH_RIGHT
	DSA_TestSuite_Lab7::BSTPushRight();
#endif
#if BST_CONTAINS_TRUE
	DSA_TestSuite_Lab7::BSTContainsTrue();
#endif
#if BST_CONTAINS_FALSE
	DSA_TestSuite_Lab7::BSTContainsFalse();
#endif
#if BST_REMOVE_CASE0_ROOT
	DSA_TestSuite_Lab7::BSTRemoveCase0Root();
#endif
#if BST_REMOVE_CASE0_LEFT
	DSA_TestSuite_Lab7::BSTRemoveCase0Left();
#endif
#if BST_REMOVE_CASE0_RIGHT
	DSA_TestSuite_Lab7::BSTRemoveCase0Right();
#endif
#if BST_REMOVE_CASE1_ROOT_LEFT
	DSA_TestSuite_Lab7::BSTRemoveCase1RootLeft();
#endif
#if BST_REMOVE_CASE1_ROOT_RIGHT
	DSA_TestSuite_Lab7::BSTRemoveCase1RootRight();
#endif
#if BST_REMOVE_CASE1_LEFT_LEFT
	DSA_TestSuite_Lab7::BSTRemoveCase1LeftLeft();
#endif
#if BST_REMOVE_CASE1_LEFT_RIGHT
	DSA_TestSuite_Lab7::BSTRemoveCase1LeftRight();
#endif
#if BST_REMOVE_CASE1_RIGHT_LEFT
	DSA_TestSuite_Lab7::BSTRemoveCase1RightLeft();
#endif
#if BST_REMOVE_CASE1_RIGHT_RIGHT
	DSA_TestSuite_Lab7::BSTRemoveCase1RightRight();
#endif
#if BST_REMOVE_CASE2_SUBTREE
	DSA_TestSuite_Lab7::BSTRemoveCase2Subtree();
#endif
#if BST_REMOVE_CASE2_NO_SUBTREE
	DSA_TestSuite_Lab7::BSTRemoveCase2NonRootNoSubtree();
#endif
#if BST_REMOVE
	DSA_TestSuite_Lab7::BSTRemove();
#endif
#if BST_REMOVE_NOT_FOUND
	DSA_TestSuite_Lab7::BSTRemoveNotFound();
#endif
#if BST_IN_ORDER_TRAVERSAL
	DSA_TestSuite_Lab7::BSTInOrderTraversal();
#endif
#if BST_CLEAR
	DSA_TestSuite_Lab7::BSTClear();
#endif
#if BST_DTOR
	DSA_TestSuite_Lab7::BSTDestructor();
#endif
#if BST_ASSIGNMENT_OP
	DSA_TestSuite_Lab7::BSTAssignmentOperator();
#endif
#if BST_COPY_CTOR
	DSA_TestSuite_Lab7::BSTCopyConstructor();
#endif
#else
	std::cout << "LAB_7 is not toggled on in BST.h\n";
#endif	// End LAB_7
}

void Lab8Tests() {
#if LAB_8
#if HUFFMAN_CTOR
	DSA_TestSuite_Lab8::HuffmanConstructor();
#endif
#if HUFFMAN_GENERATE_FREQUENCY
	DSA_TestSuite_Lab8::HuffmanGenerateFrequencyTable();
#endif
#if HUFFMAN_GENERATE_LEAFLIST
	DSA_TestSuite_Lab8::HuffmanGenerateLeafList();
#endif
#if HUFFMAN_GENERATE_TREE
	DSA_TestSuite_Lab8::HuffmanGenerateTree();
#endif
#if HUFFMAN_CLEAR_TREE
	DSA_TestSuite_Lab8::HuffmanClearTree();
#endif
#if HUFFMAN_DTOR
	DSA_TestSuite_Lab8::HuffmanDestructor();
#endif
#if HUFFMAN_GENERATE_ENCODING
	DSA_TestSuite_Lab8::HuffmanGenerateEncodingTable();
#endif
#if HUFFMAN_COMPRESS
	DSA_TestSuite_Lab8::HuffmanCompress();
#endif
#if HUFFMAN_DECOMPRESS
	DSA_TestSuite_Lab8::HuffmanDecompress();
#endif
#else
	std::cout << "LAB_8 is not toggled on in Huffman.h\n";
#endif	// End LAB_8
}