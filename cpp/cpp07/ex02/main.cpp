#include "Array.hpp"

using std::cout;
using std::endl;

namespace {
	class TestClass {
		int _value;

	public:
		TestClass() : _value(42) {
			cout << "TestClass default constructor" << endl;
		}
		TestClass(int v) : _value(v) {
			cout << "TestClass param constructor" << endl;
		}
		TestClass(const TestClass& other) : _value(other._value) {
			cout << "TestClass copy constructor" << endl;
		}
		TestClass& operator=(const TestClass& other) {
			cout << "TestClass copy assignment" << endl;
			if (this != &other)
				_value = other._value;
			return *this;
		}
		~TestClass() {
			cout << "TestClass destructor" << endl;
		}

		int getValue() const { return _value; }
	};

	void testWithClass() {
		cout << "Creating Array<TestClass> with 3 elements" << endl;
		Array<TestClass> arr(3);

		cout << "\nAssigning new TestClass objects" << endl;
		for (unsigned int i = 0; i < arr.size(); ++i) {
			arr[i] = TestClass(i * 100); // triggers param constructor + copy assignment
		}

		cout << "\nReading values back:" << endl;
		for (unsigned int i = 0; i < arr.size(); ++i) {
			cout << "arr[" << i << "] = " << arr[i].getValue() << endl;
		}

		cout << "\nTesting copy constructor" << endl;
		Array<TestClass> copyArr(arr); // triggers deep copy

		cout << "\nTesting copy assignment" << endl;
		Array<TestClass> assignedArr;
		assignedArr = arr;
	}
}

int main (void) {
	try {
		// Array<int> c;
		// Array<int> a(10);
		// Array<int> b(a);
		// int *z = new int();
		// cout << "a=" << *z << endl;
		// // cout << a[20] << endl;


		// Test 1: Default constructor
		Array<int> a;
		cout << "Size of default array: " << a.size() << endl;

		// Test 2: Parameterized constructor
		Array<int> b(0);
		cout << "Size of parameterized array: " << b.size() << endl;

		// Fill array with values
		for (unsigned int i = 0; i < b.size(); ++i) {
			b[i] = static_cast<int>(i * 10); // 0, 10, 20, 30, 40
		}

		// Read values to confirm write succeeded
		cout << "Contents of array b: ";
		for (unsigned int i = 0; i < b.size(); ++i) {
			cout << b[i] << " ";
		}
		cout << endl;

		// Test 3: Bounds checking
		try {
			cout << "Accessing out-of-bounds index..." << endl;
			cout << b[10] << endl; // Should throw
		} catch (const std::exception& e) {
			cout << "Caught exception on out-of-bounds access" << endl;
		}

		// Test 4: Copy constructor
		Array<int> c(b); // deep copy
		cout << "Contents of copy-constructed array c: ";
		for (unsigned int i = 0; i < c.size(); ++i) {
			cout << c[i] << " ";
		}
		cout << endl;

		// Test 5: Copy assignment
		Array<int> d;
		d = b;
		cout << "Contents of copy-assigned array d: ";
		for (unsigned int i = 0; i < d.size(); ++i) {
			cout << d[i] << " ";
		}
		cout << endl;

		testWithClass();
	} catch (std::exception& e) {
		cout << "Exception! " << e.what() << endl;
	}
	return 0;
}