#include <iostream>
#include "BitStream.h"
using namespace std;


/**************/
/* BitOStream */
/**************/

// Constructor
//		Will create the file and write the header (if there is one)
//
// In:	_fileName		The name of the file to open for output (this will be truncated if it already exists)
//		_fileHeader		The header information for this file (will be written first) (OPTIONAL)
//		_headerSize		The number of bytes in the optional header (OPTIONAL)
BitOStream::BitOStream(const char* _fileName, const char* _fileHeader , unsigned int _headerSize) {
	// Clearing out buffer
	mBuffer = 0;
	// Setting the current bit index to the high bit
	mBitIndex = 7;

	// Opening the file in binary mode
	mStream.open(_fileName, ios_base::binary);
	// If there is a file header, write it out to the front of the file
	if (_fileHeader)
		mStream.write(_fileHeader, _headerSize);
}

// Destructor
//		Closes the file
BitOStream::~BitOStream() {
	// Close the file (and write any remaining bits, if necessary)
	Close();
}

// Insertion operator
//		This will write to the buffer.  If the buffer is full, it will write the buffer out to the file
//
// In:	_bits			A vector of bools to store in the buffer (as bits)
//
// Return:	The invoking object 
//		This allows insertions to be daisy-chained (standard behavior)
BitOStream& BitOStream::operator<<(vector<bool>& _bits) {
	// Loop through the vector
	for (unsigned int i = 0; i < _bits.size(); ++i) {
		// If the current index is true, turn on the current bit
		if (_bits[i])
			mBuffer |= 1 << mBitIndex;

		// Move to the next index (remember we're writing from high->low index)
		--mBitIndex;

		// If the buffer is full, write it to the file and reset the bit index
		if (mBitIndex < 0) {
			mStream.write(&mBuffer, 1);
			mBuffer = 0;
			mBitIndex = 7;
		}	
	}

	// Send back the invoking object
	return *this;
}

// Close the file
//		If there is any valid information in the buffer, it is written out with trailing 0's.  
void BitOStream::Close() {
	// If there are any remaining bits in the buffer, write them
	if (mBitIndex < 7)
		mStream.write(&mBuffer, 1);

	// Close the file
	mStream.close();
}

/**************/
/* BitIStream */
/**************/


// Constructor
//		Will open the file and read the header (if there is one)
//
// In:	_fileName		The name of the file to open for input
//		_fileHeader		Where to store the file header (OPTIONAL)
//		_headerSize		The number of bytes in the optional header (OPTIONAL)
BitIStream::BitIStream(const char* _fileName, char* _fileHeader, unsigned int _headerSize) {
	// Open the file in binary mode
	mStream.open(_fileName, ios_base::binary);

	// Some simple error-checking
	if (!mStream.is_open())
		cout << "File did not open properly.\n";

	// If there is a file header, read that data into the supplied space
	if (_fileHeader)
		mStream.read(_fileHeader, _headerSize);

	// Setting the current bit index to the high bit
	mBitIndex = 7;

	// Reading the first byte into the buffer
	mStream.read(&mBuffer, 1);
}

// Destructor
//		Will close the file
BitIStream::~BitIStream() {
	// Close the file
	Close();
}

// Extraction operator
//		Sends back one bit from the buffer.   Will read another char into the buffer once all
//		bits have been processed.
//
// In:	_bit		Where to store the bit
//
// Return:	The invoking object 
//		This allows insertions to be daisy-chained (standard behavior)
BitIStream& BitIStream::operator>>(bool& _bit) {
	// If we are through reading the current byte, reset the index and read the next byte
	if (mBitIndex < 0) {
		mBitIndex = 7;
		mStream.read(&mBuffer, 1);
	}

	// If the current bit is a 1, set the bit to true
	if (mBuffer & (1 << mBitIndex))
		_bit = 1;
	// Otherwise false
	else
		_bit = 0;

	// Move to the next index (remember we're reading from high->low index)
	--mBitIndex;

	// Send back the invoking object
	return *this;
}

// Check for End of File
//
// Return: True, if we are at the end of the file, having read every byte from the file and processed every bit
bool BitIStream::eof() {
	return mStream.eof();
}

// Close the file
void BitIStream::Close() {
	mStream.close();
}