/*
File:			DSA_TestSuite_GlobalFunctions.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	11.26.2020
Purpose:		Definitions of global functions used in all unit tests
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

/************/
/* Includes */
/************/
#include "Console.h"
#include "DSA_TestSuite_GlobalFunctions.h"

bool verboseMode = false;

	// Default constructor
	//		Only needed to create arrays in unit tests
IntWrapper::IntWrapper() {}

// Constructor
//
// In:	_value		The value to store
IntWrapper::IntWrapper(int _value) : mValue(_value) {}

// Copy constructor
//		Used to initialize one object to another
//		
// In:	_copy		The object to copy from
IntWrapper::IntWrapper(const IntWrapper& _copy) {
	*this = _copy;
}

// Overloaded typecast operator to convert to int
IntWrapper::operator int() {
	return mValue;
}

// Assignment operator
//		Used to assign one object to another
// 
// In:	_assign				The object to assign from
//
// Return: The invoking object (by reference)
//		This allows us to daisy-chain
IntWrapper& IntWrapper::operator=(const IntWrapper& _assign) {
	if (this != &_assign) {
		mValue = _assign.mValue;
	}
	return *this;
}

// Default constructor
//
// In:	_str		A string
//		_val		A value
UserDefined::UserDefined(const std::string& _str, int _val) : mString(_str), mValue (_val) { }

// == operator for unit tests that require checking for equality
//
// In:	_b			The UserDefined object to compare with
//
// Return: True, if they contain the same information
bool UserDefined::operator==(const UserDefined& _b) {
	return mString == _b.mString
		&& mValue  == _b.mValue;
}

// != operator for unit tests that require checking for inequality
//
// In:	_b			The UserDefined object to compare with
//
// Return: True, if they do not contain the same information
bool UserDefined::operator!=(const UserDefined& _b) {
	return mString != _b.mString
		|| mValue  != _b.mValue;
}

// Display an object using <<
//
// In:	_os			The ostream to display with
//		_obj		The object to display
//
// Return: The ostream, so that we can daisy-chain
std::ostream& operator<<(std::ostream& _os, const UserDefined& _obj) {
	_os << '[' << _obj.mString << ", " << _obj.mValue << "]";
	return _os;
}

// Used to print out PASS/FAIL messages
//
// In:	_msg		The string to print (reason for failure)
//		_success	Deteremines the PASS/FAIL result
void PrintMessage(const char* _msg) {
	
	System::Console::ForegroundColor(System::ConsoleColor::Red);
	std::cout << "FAIL";
	System::Console::ForegroundColor(System::ConsoleColor::Gray);
	std::cout << " - " << _msg << '\n';
}

void PrintMessage() {
	System::Console::ForegroundColor(System::ConsoleColor::Green);
	std::cout << "PASS\n";
	System::Console::ForegroundColor(System::ConsoleColor::Gray);
}