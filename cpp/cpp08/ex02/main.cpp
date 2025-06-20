#include "MutantStack.hpp"

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

}

int main()
{
	cout << YELLOWISH << "givenSubjectMain" << endl;
	givenSubjectMain();
	cout << endl;


	return 0;
}