#include "Array.hpp"

#define MAX_VAL 750//from given subject main
using std::cout;
using std::endl;

namespace {
	
	inline std::string YELLOWISH() {return "\033[33m";}
	inline std::string RESETISH() {return "\033[0m";}

	int givenMain()
	{
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];
		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}
		//SCOPE
		{
			Array<int> tmp = numbers;
			Array<int> test(tmp);
		}

		for (int i = 0; i < MAX_VAL; i++)
		{
			if (mirror[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				return 1;
			}
		}
		try
		{
			numbers[-2] = 0;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		try
		{
			numbers[MAX_VAL] = 0;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		for (int i = 0; i < MAX_VAL; i++)
		{
			numbers[i] = rand();
		}
		delete [] mirror;//
		return 0;
	}
	
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
			arr[i] = TestClass(i * 100);
		}

		cout << "\nReading values back:" << endl;
		for (unsigned int i = 0; i < arr.size(); ++i) {
			cout << "arr[" << i << "] = " << arr[i].getValue() << endl;
		}

		cout << "\nTesting copy constructor" << endl;
		Array<TestClass> copyArr(arr);
		cout << "\nReading copied values back:" << endl;
		for (unsigned int i = 0; i < copyArr.size(); ++i) {
			cout << "copyArr[" << i << "] = " << copyArr[i].getValue() << endl;
		}

		cout << "\nTesting copy assignment" << endl;
		Array<TestClass> assignedArr;
		assignedArr = arr;
		cout << "\nReading copy-assigned values back:" << endl;
		for (unsigned int i = 0; i < assignedArr.size(); ++i) {
			cout << "copyArr[" << i << "] = " << assignedArr[i].getValue() << endl;
		}
	}
}

int main (void) {
	try {
		cout << YELLOWISH() << "givenSubjectMain" << RESETISH() << endl;
		givenMain();
		cout << endl;

		testWithClass();
	} catch (std::exception& e) {
		cout << "Exception in main!" << e.what() << endl;
	}
	return 0;
}