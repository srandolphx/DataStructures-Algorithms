#include <iostream>

// Memory leak detection
#define _CRTDBG_MAP_ALLOC

class Dynamic {

	char* mStr;

public:

	Dynamic(const char* _str) {
		mStr = new char[strlen(_str) + 1];
		strcpy_s(mStr, strlen(_str) + 1, _str);
	}

	// Rule of 3

	// Destructor
	~Dynamic() {
		delete[] mStr;
	}

	// Copy constructor
	Dynamic(const Dynamic& _copy) {
		*this = _copy;	// This will call the assignment operator
	}

	// Assignment Operator
	Dynamic& operator=(const Dynamic& _assign) {
		// Self-assignment check
		if (this != &_assign) {

			// Clean up existing memory
			delete[] mStr;

			// Deep copies
			mStr = new char[strlen(_assign.mStr) + 1];
			strcpy_s(mStr, strlen(_assign.mStr) + 1, _assign.mStr);
		}
		return *this;
	}


	void Display() const {
		std::cout << mStr << '\n';
	}
};


template<typename Type>
class Example {

public:

	Example() {
		
	}

};

class Point {

	int x, y;

public:

	// Constructor
	Point(int _x = 0, int _y = 0) {
		x = _x;
		y = _y;
	}

	// Display to the console
	void Display() const {
		std::cout << "X: " << x << '\t' << "Y: " << y << '\n';
	}

	// Compare to see if two points are equal
	bool operator==(const Point& _pt) const {
		return ((x == _pt.x) && (y == _pt.y));
	}

	// Add two points together
	Point operator+(const Point& _pt) const {
		Point sum;
		sum.x = this->x + _pt.x;
		sum.y = this->y + _pt.y;

		return sum;
	}

	// Add two points together
	Point Add(const Point& _pt) const {
		Point sum;
		sum.x = this->x + _pt.x;
		sum.y = this->y + _pt.y;

		return sum;
	}
};


int main() {

	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
	_CrtSetBreakAlloc(-1);


	// Point example
#if 0
	Point p;

	p.Display();

	Point pt1(5, 3);
	Point pt2(5, 3);

	pt1.Display();

	if (pt1 == pt2)
		std::cout << "The two points are at the same location.\n";
	else
		std::cout << "The two points are different.\n";

	Point newPoint = pt1 + pt2;

	newPoint.Display();
#endif

	// Rule of 3
#if 1

	Dynamic test("test");

	test.Display();

	Dynamic clone("Blank");
	clone = test;		// Assignment

	clone.Display();

	clone = clone;
	// Clone highest-level character
	// clone = FindHighest(characterList);

	clone.Display();

	Dynamic assignment = test;	// Copy constructor call (initialization)

	assignment.Display();


#endif


	std::cout << "\n\n";
	system("pause");
	return 0;
}

