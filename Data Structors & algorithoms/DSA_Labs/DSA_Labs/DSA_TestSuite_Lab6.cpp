/*
File:			DSA_TestSuite_Lab5.cpp
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
Created:		01.07.2021
Last Modified:	02.26.2021
Purpose:		Definitions of Lab5 Unit Tests for Dictionary
Notes:			Property of Full Sail University
*/

/************/
/* Includes */
/************/
#include <string>
#include <fstream>
#include <iostream>
#include "DSA_TestSuite_Lab6.h"
#include "DSA_Memory_Management.h"
#include "DSA_TestSuite_GlobalFunctions.h"

#if LAB_6
#if MAP_POPULATE_LETTER_VALUES
void DSA_TestSuite_Lab6::MapPopulateLetterValues() {
	std::cout << "Testing population of letter values\n";

	// Generating random values for letters
	int values[26];
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	bool success = true;

	DSA_Lab6 scrabble;
	scrabble.PopulateLetterValues(values);

	if (verboseMode) {
		std::cout << "Expected:\t";
		for (size_t i = 0; i < 26; ++i)
			std::cout << values[i] << ' ';
		std::cout << '\n';
		std::cout << "Yours:\t\t";
		for (size_t i = 0; i < 26; ++i)
			std::cout << scrabble.mLetterValues[i] << ' ';
		std::cout << '\n';
	}

	// Error testing
	for(size_t i = 0; i < 26; ++i)
		if (scrabble.mLetterValues[i] != values[i]) {
			PrintMessage("One or more values in array are incorrect.\n");
			success = false;
			break;
		}

	// Testing for success
	if (success)
		PrintMessage();
}
#endif	// End MAP_POPULATE_LETTER_VALUES

#if MAP_GET_LETTER_VALUE
void DSA_TestSuite_Lab6::MapGetLetterValue() {
	std::cout << "Testing getting the value of a single letter\n";

	// Generating random values for letters
	int values[26];
	char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
		'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	bool success = true;

	DSA_Lab6 scrabble;
	memcpy(scrabble.mLetterValues, values, sizeof(int) * 26);

	if (verboseMode) {
		std::cout << "\t\tExpected\tYours\n";
		for (size_t i = 0; i < 26; ++i) {
			std::cout << "\t\t" << values[i] << "\t\t" << scrabble.GetLetterValue(letters[i]) << '\n';
		}
	}

	// Error testing
	for(size_t i = 0; i < 26; ++i)
		if (scrabble.GetLetterValue(letters[i]) != values[i]) {
			PrintMessage("GetLetterValue is not returning correct value");
			success = false;
			break;
		}

	// Testing for success
	if (success)
		PrintMessage();
}
#endif	// End MAP_GET_LETTER_VALUE

#if MAP_GET_WORD_VALUE
void DSA_TestSuite_Lab6::MapGetWordValue() {
	std::cout << "Testing getting the value of a word\n";

	// Generating random values for letters
	int values[26];
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	std::string sampleWords[3] = { "APPLE", "PEROXIDE", "UMBRAGEOUSNESS" };
	int results[3] = { 0,0,0 };
	for (size_t i = 0; i < 3; ++i)
		for (size_t l = 0; l < sampleWords[i].size(); ++l)
			results[i] += values[sampleWords[i][l] - ((1 << 6) | 1)];
	bool success = true;

	DSA_Lab6 scrabble;
	memcpy(scrabble.mLetterValues, values, sizeof(int) * 26);

	if (verboseMode) {
		std::cout << "\t\tTesting several words\n";
		for (size_t i = 0; i < 3; ++i) {
			std::cout << '\t' << sampleWords[i] << "\t" << "Expected (" << results[i] << ")\tYours (" << scrabble.GetWordValue(sampleWords[i]) << ")\n";
		}
	}

	// Error testing
	for (size_t i = 0; i < 3; ++i)
		if (scrabble.GetWordValue(sampleWords[i]) != results[i]) {
			PrintMessage("GetWordValue is not returning correct value");
			success = false;
			break;
		}

	// Testing for success
	if (success)
		PrintMessage();
}
#endif	// End MAP_GET_WORD_VALUE

#if MAP_CREATE_PAIR
void DSA_TestSuite_Lab6::MapCreatePair() {
	std::cout << "Testing creating a pair for the map\n";

	using myPair = std::pair<std::string, int>;

	// Generating random values for letters
	int values[26];
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	std::string sampleWords[3] = { "APPLE", "PEROXIDE", "UMBRAGEOUSNESS" };
	int results[3] = { 0,0,0 };
	for (size_t i = 0; i < 3; ++i) {
		for (size_t l = 0; l < sampleWords[i].size(); ++l) {
			results[i] += values[sampleWords[i][l] - ((1 << 6) | 1)];
		}
	}
	bool success = true;

	DSA_Lab6 scrabble;
	memcpy(scrabble.mLetterValues, values, sizeof(int) * 26);
	myPair currPair;

	if (verboseMode) {
		std::cout << "\t\tPairs created\n"
			<< "\tExpected\n";
		for (size_t i = 0; i < 3; ++i)
			std::cout << "\t[" << sampleWords[i] << "," << results[i] << "]\n";
		std::cout << "\tYours\n";
		for (size_t i = 0; i < 3; ++i) {
			currPair = scrabble.CreatePair(sampleWords[i]);
			std::cout << "\t[" << currPair.first << "," << currPair.second << "]\n";
		}
	}

	// Error testing
	for (size_t i = 0; i < 3; ++i) {
		currPair = scrabble.CreatePair(sampleWords[i]);
		if (currPair.first != sampleWords[i]) {
			PrintMessage("CreatePair is not storing word correctly");
			success = false;
break;
		}
		if (currPair.second != results[i]) {
			PrintMessage("CreatePair is not storing correct word value");
			success = false;
			break;
		}
	}

	// Testing for success
	if (success)
		PrintMessage();
}
#endif	// End MAP_CREATE_PAIR

#if MAP_LOAD_FILE
void DSA_TestSuite_Lab6::MapLoadFile() {
	std::cout << "Testing loading file into unordered_map (this will take a few seconds)\n";
	using myPair = std::pair<std::string, int>;
	const int numWords = 178636;

	// Generating random values for letters
	int values[26];
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	std::string sampleWords[3] = { "APPLE", "PEROXIDE", "UMBRAGEOUSNESS" };
	int results[3] = { 0,0,0 };
	for (size_t i = 0; i < 3; ++i) {
		for (size_t l = 0; l < sampleWords[i].size(); ++l) {
			results[i] += values[sampleWords[i][l] - ((1 << 6) | 1)];
		}
	}
	bool success = true;

	DSA_Lab6 scrabble;
	memcpy(scrabble.mLetterValues, values, sizeof(int) * 26);

	scrabble.LoadWords("words.txt");

	if (verboseMode) {
		std::cout << "\t\tExpected words:\t" << numWords << '\n'
			<< "Your words:\t" << scrabble.mScrabbleMap.size() << '\n';
	}

	// Error testing
	if (numWords != scrabble.mScrabbleMap.size())
		PrintMessage("Not all words were loaded into map");

	for (int i = 0; i < 3; ++i) {
		if (results[i] != scrabble.mScrabbleMap.find(sampleWords[i])->second) {
			PrintMessage("Word value is incorrect");
			success = false;
		}
	}

	if (numWords == scrabble.mScrabbleMap.size() &&
		success)
		PrintMessage();
}
#endif	// End MAP_LOAD_FILE

#if MAP_FIND_WORD_SCORE
void DSA_TestSuite_Lab6::MapFindWordScore() {
	std::cout << "Testing finding score in the map\n";
	using myPair = std::pair<std::string, int>;

	// Generating random values for letters
	int values[26];
	for (size_t i = 0; i < 26; ++i)
		values[i] = rand() % 10 + 1;
	std::string sampleWords[4] = { "APPLE", "PEROXIDE", "UMBRAGEOUSNESS", "ZZZZ" };
	int results[4] = { 0,0,0, -1};
	for (size_t i = 0; i < 3; ++i) {
		for (size_t l = 0; l < sampleWords[i].size(); ++l) {
			results[i] += values[sampleWords[i][l] - ((1 << 6) | 1)];
		}
	}
	bool success = true;

	DSA_Lab6 scrabble;
	memcpy(scrabble.mLetterValues, values, sizeof(int) * 26);
	for (size_t i = 0; i < 3; ++i) {
		myPair pair;
		pair.first = sampleWords[i];
		pair.second = results[i];
		scrabble.mScrabbleMap.insert(pair);
	}

	std::ifstream ifl("DSA_Lab6.h");
	std::string currLine;
	bool usesFind = false;

	while (true) {
		std::getline(ifl, currLine);
		if (ifl.eof())
			break;

		if (currLine.find(".find(") != std::string::npos) {
			usesFind = true;
			break;
		}
	}
	ifl.close();

	if (verboseMode) {
		std::cout << "No additional information to display for this test\n";
	}

	// Error testing
	if (!usesFind)
		PrintMessage("Does not use .find to find word");

	for (size_t i = 0; i < 4; ++i) {
		if (scrabble.FindValueInMap(sampleWords[i]) != results[i]) {
			PrintMessage("FindValue not returning correct result");
			success = false;
			break;
		}
	}

	// Testing for success
	if (usesFind && success)
		PrintMessage();

}
#endif	// End MAP_FIND_WORD_SCORE
#endif	// End LAB_6