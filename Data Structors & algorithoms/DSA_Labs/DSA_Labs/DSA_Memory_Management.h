/*
File:			DSA_Memory_Management.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	11.21.2020
Purpose:		Declarations of overloaded new/delete in order to give
				better metrics of how much memory is being used.
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

// Header protection
#pragma once


// Keeps track of how much memory is being used within the application
struct AllocationMetrics {
	//size_t totalAllocated = 0;		// Amount of memory currently allocated
	//size_t totalFreed = 0;			// Amount of memory that has been released

	//// Gets the delta of memory in use to released
	//size_t inUse;
	size_t inUse = 0;
};

// Single instance for metrics
extern AllocationMetrics metrics;

// Overloaded new that makes use of AllocationMetrics
//
// In:	_size		The amount of memory to allocate
//
// Return: A pointer to the first address in the block of heap-allocated memory
void* operator new(size_t _size);

// Overloaded delete that makes use of AllocationMetrics
//
// In:	_memory		Pointer to the first address of block to be deallocated
void operator delete(void* _memory);

