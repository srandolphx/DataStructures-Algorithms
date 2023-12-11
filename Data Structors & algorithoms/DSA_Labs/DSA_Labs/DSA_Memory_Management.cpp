/*
File:			DSA_Memory_Management.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		11.21.2020
Last Modified:	11.21.2020
Purpose:		Definitions of overloaded new/delete in order to give
				better metrics of how much memory is being used.
Notes:			Property of Full Sail University

				DO NOT CHANGE ANY CODE IN THIS FILE
*/

/************/
/* Includes */
/************/
#include <cstdlib>
#include <iostream>
#include "DSA_Memory_Management.h"

//size_t AllocationMetrics::inUse {
//	return totalAllocated - totalFreed;
//}

AllocationMetrics metrics;

// Overloaded new that makes use of AllocationMetrics
//
// In:	_size		The amount of memory to allocate
//
// Return: A pointer to the first address in the block of heap-allocated memoryvoid* operator new(size_t _size) {
void* operator new(size_t _size) {
	// Allocating the memory (along with an extra header to keep track of the size)
	size_t* mem = (size_t*)malloc(_size + sizeof(size_t));
	// Set the size in the header
	mem[0] = _size;
	// Update the metrics
	metrics.inUse += _size;
	// Send back the allocated memory (minus the header)
	return (void*)(&mem[1]);
}

// Overloaded delete that makes use of AllocationMetrics
//
// In:	_memory		Pointer to the first address of block to be deallocated
void operator delete(void* _memory) {
	if (!_memory)
		return;

	// Creating a temp pointer to make code easier to work with
	size_t* mem = (size_t*)_memory;
	// Extracting the header information which contains the number of bytes allocated
	metrics.inUse -= mem[-1];
	// Get a pointer to the actual memory allocated (with the header)
	void* ptr = (void*)(&mem[-1]);
	// Release the memory back to the heap
	free(ptr);
}
