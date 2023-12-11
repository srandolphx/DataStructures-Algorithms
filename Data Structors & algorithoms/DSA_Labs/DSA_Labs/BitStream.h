#pragma once

// A pair of classes used to read/write bits from/to a file

/************/
/* Includes */
/************/
#include <vector>
#include <fstream>
using namespace std;

// A class used to write a binary file at the bit level
class BitOStream {

	// Data members
	ofstream mStream;		// The stream to use for outputting
	char mBuffer;			// The single byte to fill with 1's and 0's.   Once it is "full", it can be written out
	int mBitIndex;			// The current bit "index" to write to

public:

	// Constructor
	//		Will create the file and write the header (if there is one)
	//
	// In:	_fileName		The name of the file to open for output (this will be truncated if it already exists)
	//		_fileHeader		The header information for this file (will be written first) (OPTIONAL)
	//		_headerSize		The number of bytes in the optional header (OPTIONAL)
	BitOStream(const char* _fileName, const char* _fileHeader = nullptr, unsigned int _headerSize = 0);

	// Destructor
	//		Closes the file
	~BitOStream();

	// Insertion operator
	//		This will write to the buffer.  If the buffer is full, it will write the buffer out to the file
	//
	// In:	_bits			A vector of bools to store in the buffer (as bits)
	//
	// Return:	The invoking object 
	//		This allows insertions to be daisy-chained (standard behavior)
	BitOStream& operator<<(vector<bool>& _bits);

	// Close the file
	//		If there is any valid information in the buffer, it is written out with trailing 0's.  
	void Close();
};

// A class used to read a binary file at the bit level
class BitIStream {

	ifstream mStream;		// The stream to use for inputting
	char mBuffer;	// The current byte to read
	int mBitIndex;			// The current bit in the buffer to read

public:

	// Constructor
	//		Will open the file and read the header (if there is one)
	//
	// In:	_fileName		The name of the file to open for input
	//		_fileHeader		Where to store the file header (OPTIONAL)
	//		_headerSize		The number of bytes in the optional header (OPTIONAL)
	BitIStream(const char* _fileName, char* _fileHeader = nullptr, unsigned int _headerSize = 0);

	// Destructor
	//		Will close the file
	~BitIStream();

	// Extraction operator
	//		Sends back one bit from the buffer.   Will read another char into the buffer once all
	//		bits have been processed.
	//
	// In:	_bit		Where to store the bit
	//
	// Return:	The invoking object 
	//		This allows extractions to be daisy-chained (standard behavior)
	BitIStream& operator>>(bool& _bit);

	// Check for End of File
	//
	// Return: True, if we are at the end of the file, having read every byte from the file and processed every bit
	bool eof();

	// Close the file
	void Close();
};