#include "Array.hpp"

using std::cout;
using std::endl;

namespace {
	class TestClass {
		int _value;

	public:
		TestClass() : _value(42) {
			std::cout << "TestClass default constructor\n";
		}
		TestClass(int v) : _value(v) {
			std::cout << "TestClass param constructor\n";
		}
		TestClass(const TestClass& other) : _value(other._value) {
			std::cout << "TestClass copy constructor\n";
		}
		TestClass& operator=(const TestClass& other) {
			std::cout << "TestClass copy assignment\n";
			if (this != &other)
				_value = other._value;
			return *this;
		}
		~TestClass() {
			std::cout << "TestClass destructor\n";
		}

		int getValue() const { return _value; }
	};

	void testWithClass() {
		std::cout << "Creating Array<TestClass> with 3 elements\n";
		Array<TestClass> arr(3);

		std::cout << "\nAssigning new TestClass objects\n";
		for (unsigned int i = 0; i < arr.size(); ++i) {
			arr[i] = TestClass(i * 100); // triggers param constructor + copy assignment
		}

		std::cout << "\nReading values back:\n";
		for (unsigned int i = 0; i < arr.size(); ++i) {
			std::cout << "arr[" << i << "] = " << arr[i].getValue() << "\n";
		}

		std::cout << "\nTesting copy constructor\n";
		Array<TestClass> copyArr(arr); // triggers deep copy

		std::cout << "\nTesting copy assignment\n";
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
		std::cout << "Size of default array: " << a.size() << "\n";

		// Test 2: Parameterized constructor
		Array<int> b(5);
		std::cout << "Size of parameterized array: " << b.size() << "\n";

		// Fill array with values
		for (unsigned int i = 0; i < b.size(); ++i) {
			b[i] = static_cast<int>(i * 10); // 0, 10, 20, 30, 40
		}

		// Read values to confirm write succeeded
		std::cout << "Contents of array b: ";
		for (unsigned int i = 0; i < b.size(); ++i) {
			std::cout << b[i] << " ";
		}
		std::cout << "\n";

		// Test 3: Bounds checking
		try {
			std::cout << "Accessing out-of-bounds index...\n";
			std::cout << b[10] << "\n"; // Should throw
		} catch (const std::exception& e) {
			std::cout << "Caught exception on out-of-bounds access\n";
		}

		// Test 4: Copy constructor
		Array<int> c(b); // deep copy
		std::cout << "Contents of copy-constructed array c: ";
		for (unsigned int i = 0; i < c.size(); ++i) {
			std::cout << c[i] << " ";
		}
		std::cout << "\n";

		// Test 5: Copy assignment
		Array<int> d;
		d = b;
		std::cout << "Contents of copy-assigned array d: ";
		for (unsigned int i = 0; i < d.size(); ++i) {
			std::cout << d[i] << " ";
		}
		std::cout << "\n\n";

		testWithClass();
	} catch (std::exception& e) {
		cout << "Exception! " << e.what() << endl;
	}
	return 0;
}