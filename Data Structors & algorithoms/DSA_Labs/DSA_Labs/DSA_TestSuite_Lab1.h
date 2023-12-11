/*
File:			DSA_TestSuite_Lab1.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	02.26.2021
Purpose:		Declaration of Lab1 Unit Tests for DynArray
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/************/
/* Includes */
/************/
#include <iostream>
#include "DynArray.h"

class DSA_TestSuite_Lab1 {

public:

#if LAB_1
	static void DynArrayDefaultConstructorNoArgs();
	static void DynArrayDefaultConstructorWithArgs();
	static void DynArrayDestructor();
	static void DynArrayCopyConstructorInt();
	static void DynArrayCopyConstructorClass();
	static void DynArrayAssignmentOperatorInt();
	static void DynArrayAssignmentOperatorClass();
	static void DynArrayBracketOperator_ReadOnly();
	static void DynArrayBracketOperator_Write();
	static void DynArrayAccessors_Size();
	static void DynArrayAccessors_Capacity();
	static void DynArrayClear();
	static void DynArrayReserveZero();
	static void DynArrayReserveDouble();
	static void DynArrayReserveSpecific();
	static void DynArrayReserveSmaller();
	static void DynArrayAppendNoResize();
	static void DynArrayAppendResize();

	template<typename Type>
	static void VerboseOutput_DynArray(const char* _expectedArray, size_t _expectedCapacity,
		size_t _expectedSize, const DynArray<Type>& _da, const Type* _array = nullptr, bool _displayArray = true) {
		std::cout << "\t\tExpected Values\t\tYour Values\n"
			<< "mArray:\t\t" << _expectedArray;
		std::cout << "\t";
		if (strlen(_expectedArray) <= 15)
			std::cout << "\t";
		if (!_da.mArray)
			std::cout << "\tnullptr";
		else
			std::cout << _da.mArray;
		std::cout << "\n"
			<< "mCapacity:\t" << _expectedCapacity << "\t\t\t" << _da.mCapacity << '\n'
			<< "mSize:\t\t" << _expectedSize << "\t\t\t" << _da.mSize << '\n';

		if (_array) {
			if (_displayArray) {
				std::cout << "Expected mArray Values: ";
				for (size_t i = 0; i < _expectedSize; ++i)
					std::cout << _array[i] << ", ";
				std::cout << "\b\b \n";
			}
			std::cout << "Your mArray Values:\t";
			for (size_t i = 0; i < _da.mSize; ++i)
				std::cout << _da.mArray[i] << ", ";
			std::cout << "\b\b \n";
		}
	}
#endif	// End LAB_1
	

};
	
