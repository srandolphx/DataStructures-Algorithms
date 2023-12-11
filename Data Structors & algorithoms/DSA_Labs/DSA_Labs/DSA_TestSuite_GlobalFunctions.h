/*
File:			DSA_TestSuite_GlobalFunctions.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	12.26.2020
Purpose:		Declarations of global functions used in all unit tests
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <string>
#include <iostream>

extern bool verboseMode;

// A wrapper class for an int
//	Used for obfuscation
class IntWrapper {
public:
	int mValue = -1;			// The value being stored

	// Default constructor
	//		Only needed to create arrays in unit tests
	IntWrapper();

	// Constructor
	//
	// In:	_value		The value to store
	IntWrapper(int _value);

	// Copy constructor
	//		Used to initialize one object to another
	//		
	// In:	_copy		The object to copy from
	IntWrapper(const IntWrapper& _copy);

	// Overloaded typecast operator to convert to int
	operator int();

	// Assignment operator
	//		Used to assign one object to another
	// 
	// In:	_assign				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	IntWrapper& operator=(const IntWrapper& _assign);
};

// A generic struct used within several unit tests for user-defined values
struct UserDefined {
	std::string mString;
	int mValue = -1;

	// Default constructor
	//
	// In:	_str		A string
	//		_val		A value
	UserDefined(const std::string& _str = "", int _val = -1);

	// == operator for unit tests that require checking for equality
	//
	// In:	_b			The UserDefined object to compare with
	//
	// Return: True, if they contain the same information
	bool operator==(const UserDefined& _b);

	// != operator for unit tests that require checking for inequality
	//
	// In:	_b			The UserDefined object to compare with
	//
	// Return: True, if they do not contain the same information
	bool operator!=(const UserDefined& _b);

	// Display an object using <<
	//
	// In:	_os			The ostream to display with
	//		_obj		The object to display
	//
	// Return: The ostream, so that we can daisy-chain
	friend std::ostream& operator<<(std::ostream& _os, const UserDefined& _obj);
};

// Used to print out FAIL messages
//
// In:	_msg		The string to print (reason for failure)
//		_success	Deteremines the PASS/FAIL result
void PrintMessage(const char* _msg);

// Used to print out SUCCESS message
void PrintMessage();