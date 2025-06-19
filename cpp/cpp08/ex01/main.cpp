#include "Span.hpp"

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
		cout << YELLOWISH() << "given subject main test" << RESETISH() << endl;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
		return 0;
	}


	bool	testLargeVector() {
		cout << YELLOWISH() << "\ntestLargeVector" << RESETISH() << endl;
		int correct = 0;
		const unsigned int N = 100000;
		Span sp(N);

		std::vector<int> bigVec(N);
		std::iota(bigVec.begin(), bigVec.end(), 0); // Fill with 0 to N-1
		sp.addRange(bigVec.begin(), bigVec.end());

		if (sp.shortestSpan() == 1) correct++;
		if (sp.longestSpan() == N - 1) correct++;

		return (correct == 2);
	}


	bool	testExceptions() {
		cout << YELLOWISH() << "\ntestExceptions" << RESETISH() << endl;
		int correct = 0;
		Span sp(2);
		try {
			sp.shortestSpan();
		} catch (const std::runtime_error& e) {
			cout << "Caught exception (empty): " << e.what() << endl;
			correct++;
		}

		sp.addNumber(1);
		try {
			sp.shortestSpan();
		} catch (const std::runtime_error& e) {
			cout << "Caught exception (one element): " << e.what() << endl;
			correct++;
		}

		sp.addNumber(42);
		try {
			sp.addNumber(99);
		} catch (const std::overflow_error& e) {
			cout << "Caught exception (overflow): " << e.what() << endl;
			correct++;
		}
		return (correct == 3);
	}


	bool	testDuplicateSpan() {
		cout << YELLOWISH() << "\ntestDuplicateSpan" << RESETISH() << endl;
		int correct = 0;
		{
			Span sp(3);
			sp.addNumber(10);
			sp.addNumber(20);
			sp.addNumber(10);

			cout << "Shortest span (with duplicate): " << sp.shortestSpan() << endl;
			cout << "Longest span: " << sp.longestSpan() << endl;

			if (sp.shortestSpan() == 0) correct++;
			if (sp.longestSpan() == 10) correct++;
		}
		{
			Span sp(4);
			sp.addNumber(42);
			sp.addNumber(42);
			sp.addNumber(42);
			sp.addNumber(42);

			if (sp.shortestSpan() == 0) correct++;
			if (sp.longestSpan() == 0) correct++;
		}

		return (correct == 4);
	}


	bool	negativeNumbers() {
		cout << YELLOWISH() << "\nnegativeNumbers" << RESETISH() << endl;
		int correct = 0;
		Span sp(6);
		sp.addNumber(-50);
		sp.addNumber(-10);
		sp.addNumber(-30);
		sp.addNumber(0);
		sp.addNumber(10);
		sp.addNumber(100);

		if (sp.shortestSpan() == 10) correct++;
		if (sp.longestSpan() == 150) correct++;

		return (correct == 2);
	}


	bool	edgeValues() {
		cout << YELLOWISH() << "\nedgeValues" << RESETISH() << endl;
		int correct = 0;
		Span sp(3);
		sp.addNumber(-2147483648);
		sp.addNumber(0);
		sp.addNumber(2147483647);

		cout << "shortest span:" << sp.shortestSpan() << endl;
		cout << "longest span:" << sp.longestSpan() << endl;
		if (sp.shortestSpan() == 2147483647) correct++;
		if (sp.longestSpan() == 4294967295) correct++;

		return (correct == 2);
	}


	bool	allEqual() {
		cout << YELLOWISH() << "\nallEqual" << RESETISH() << endl;
		int correct = 0;
		Span sp(4);
		sp.addNumber(42);
		sp.addNumber(42);
		sp.addNumber(42);
		sp.addNumber(42);

		if (sp.shortestSpan() == 0) correct++;
		if (sp.longestSpan() == 0) correct++;

		return (correct == 2);
	}

}

int main(void)
{
	try {
		givenSubjectMain();
		cout << endl;

		Tester myTests;
		myTests.addTest(testLargeVector);
		myTests.addTest(testExceptions);
		myTests.addTest(testDuplicateSpan);
		myTests.addTest(negativeNumbers);
		myTests.addTest(edgeValues);
		myTests.addTest(allEqual);

		myTests.run();

	} catch (std::exception& e) {
		cout << "exception in main:" << e.what() << endl;
	}
}
