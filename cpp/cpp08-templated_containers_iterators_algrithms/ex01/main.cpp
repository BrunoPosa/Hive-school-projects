#include "Span.hpp"

#include <functional>//std::function
#include <numeric>//std::iota

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
		sp.addRange(bigVec.begin(), bigVec.end(), bigVec);

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


	bool	addRangeByPointerType() {
		cout << YELLOWISH() << "\naddRangeByPointerType" << RESETISH() << endl;
		int correct = 0;

		Span sp(8);
		int array[] = {8, 10, -3, 5, 7, 25, 11, -2};

		cout << "array:" << endl;
		for (auto n : array)	cout << n << ", ";
		cout << endl;
		sp.addRange(array, array + 8, array);

		if (sp.shortestSpan() == 1) correct++;
		cout << "shortest span:" << sp.shortestSpan() << endl;
		if (sp.longestSpan() == 28) correct++;
		cout << "longest span:" << sp.longestSpan() << endl;

		return (correct == 2);
	}


	bool	addRangeFromDifferentContainers() {
		cout << YELLOWISH() << "\naddRangeFromDifferentContainers" << RESETISH() << endl;
		int correct = 0;

		Span sp(8);
		std::vector<int> A; A.push_back(3); A.push_back(5);  A.push_back(7);
		std::vector<int> B; B.push_back(-2); B.push_back(-4);

		try {
			sp.addRange(A.begin(), B.end(), A);
			cout << "longest span:" << sp.longestSpan() << endl;
		} catch (std::runtime_error& e) {
			cout << "caught exception (different containers): " << e.what() << endl;
			correct++;
		}

		return (correct == 1);
	}

}

int main(void)
{
	try {
		givenSubjectMain();
		cout << endl;

		Tester myTests({
			testLargeVector,
			testExceptions,
			testDuplicateSpan,
			negativeNumbers,
			edgeValues,
			allEqual,
			addRangeByPointerType,
			addRangeFromDifferentContainers
		});

		myTests.run();

	} catch (std::exception& e) {
		cout << REDISH() << "exception in main:" << e.what() << RESETISH() << endl;
	}
}
