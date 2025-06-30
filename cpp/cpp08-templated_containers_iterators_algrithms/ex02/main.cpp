#include "MutantStack.hpp"

#include <iostream>
#include <vector>
#include <functional>
#include <list>

using std::cout;
using std::endl;

namespace {

	inline std::string REDISH() {return "\033[1;31m";}
	inline std::string YELLOWISH() {return "\033[33m";}
	inline std::string GREENISH() {return "\033[1;32m";}
	inline std::string RESETISH() {return "\033[0m";}

	class Tester {
		std::vector<std::function<bool()>> tests_;

	public:
		Tester(std::vector<std::function<bool()>> tests) : tests_{std::move(tests)} {};
		void addTest(std::function<bool()> test) {
			tests_.push_back(test);
		}

		int run() {
			int passed = 0;
			for (size_t i = 0; i < tests_.size(); ++i) {
				bool result = tests_[i]();
				cout << "Test " << i + 1 << ": " << (result ?
												GREENISH() + "PASSED"
												: REDISH() + "FAILED") << RESETISH() << endl;
				passed += result;
			}
			if (passed == static_cast<int>(tests_.size())) {
				cout << GREENISH() << "All tests passed ✅" << RESETISH() <<  endl;
			} else {
				cout << passed << " out of " << tests_.size() << " tests passed ❌" << endl;
			}
			return passed;
		}
	};

	class emptyClass {
		int a;
	public:
		emptyClass() : a(0) {}
		emptyClass(int value) : a(value) {}
		emptyClass(const emptyClass& other) : a(other.a) {}
		emptyClass& operator=(const emptyClass& other) {
			if (this != &other) {
				a = other.a;
			}
			return *this;
		}
		~emptyClass() = default;

		bool operator==(const emptyClass& other) const {
			return a == other.a;
		}
		int getValue() const { return a; }
	};


	int	givenSubjectMain() {
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		std::stack<int> s(mstack);
		return 0;
	}

	int	givenSubjectMainWithList() {
		std::list<int> mstack;
		mstack.push_back(5);
		mstack.push_back(17);
		std::cout << mstack.back() << std::endl;
		mstack.pop_back();
		std::cout << mstack.size() << std::endl;
		mstack.push_back(3);
		mstack.push_back(5);
		mstack.push_back(737);
		//[...]
		mstack.push_back(0);
		std::list<int>::iterator it = mstack.begin();
		std::list<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		std::list<int> s(mstack);
		return 0;
	}

	bool	ctorTest() {
		int correct = 0;
		MutantStack<std::string> mstack;
		mstack.push("Hi");
		mstack.push("World");

		// copy constructor
		MutantStack<std::string> copyStack(mstack);
		if (copyStack.size() == mstack.size() && copyStack.top() == mstack.top())
			++correct;
	
		// assignment operator
		MutantStack<std::string> assignedStack;
		assignedStack = mstack;
		if (assignedStack.size() == mstack.size() && assignedStack.top() == mstack.top())
			++correct;
	
		return correct == 2;
	}


	bool	emptyClassTest() {
		int correct = 0;
		MutantStack<emptyClass> mstack;
		mstack.push(emptyClass(42));
		mstack.push(emptyClass(21));

		// copy constructor
		MutantStack<emptyClass> copyStack(mstack);
		if (copyStack.size() == mstack.size()) {
			if (copyStack.top() == mstack.top()) {
				++correct;
			}
		}

		// assignment operator
		MutantStack<emptyClass> assignedStack;
		assignedStack = mstack;
		if (assignedStack.size() == mstack.size()) {
			if (assignedStack.top() == mstack.top()) {
				++correct;
			}
		}

		return correct == 2;
	}

} // namespace

int main()
{
	try {
		cout << YELLOWISH() << "givenSubjectMain" << RESETISH() << endl;
		givenSubjectMain();
		cout << endl;

		cout << YELLOWISH() << "\ngivenSubjectMainWithList" << RESETISH() << endl;
		givenSubjectMainWithList();
		cout << endl;

		Tester tests({
			ctorTest,
			emptyClassTest
		});

		tests.run();

	} catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl;
		return 1;
	}
	return 0;
}
