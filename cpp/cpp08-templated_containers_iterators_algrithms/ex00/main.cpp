#include "easyfind.hpp"

#include <string>
#include <functional>
#include <random>
#include <algorithm>//std::shuffle, std::copy, std::find
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

using std::cout;
using std::endl;

namespace {
	constexpr int SIZE = 20;// Size of the vector, array, list, forward_list, and deque - elements are shuffled in range [0, SIZE-1]
	constexpr int TARGET = 7; // Target value to find in the containers

	inline std::vector<int> shuffledVector(int size) {
		std::vector<int> vec(size);
		for (int i = 0; i < size; ++i) {
			vec[i] = i;
		}
		// Shuffle with Mersenne Twister random number generator (using random_device for seeding)
		std::shuffle(vec.begin(), vec.end(), std::mt19937(std::random_device{}()));
		return vec;
	}

	inline std::string RED() {return "\033[1;31m";}
	inline std::string YELLOW() {return "\033[33m";}
	inline std::string GREEN() {return "\033[1;32m";}
	inline std::string BOLD() {return "\033[1m";}
	inline std::string RESET() {return "\033[0m";}

	class Tester {
		std::vector<std::function<bool()>> tests_;

	public:
		Tester(std::vector<std::function<bool()>> tests) : tests_{std::move(tests)} {};
		void addTest(std::function<bool()> test) {
			tests_.push_back(test);
		}

		int run() {
			unsigned int passed = 0;
			for (size_t i = 0; i < tests_.size(); ++i) {
				bool result = tests_[i]();
				cout << "Test " << i + 1 << ": " << (result ?
												GREEN() + "PASSED"
												: RED() + "FAILED") << RESET() << endl;
				passed += result;
			}
			if (passed == (tests_.size())) {
				cout << GREEN() << "All tests passed ✅" << RESET() << endl;
			} else {
				cout << passed << " out of " << tests_.size() << " tests passed ❌" << endl;
			}
			return passed;
		}
	};

	bool	VectorTest() {
		int target = TARGET;
		constexpr int	size = SIZE;
		size_t result = SIZE_MAX;

		try {
			std::vector<int> intVec = shuffledVector(size);
			cout << YELLOW() << "Searching for target " + std::to_string(target) + " in vector : " << RESET();
			for (int i = 0; i < size; ++i) {
				if (intVec[i] == target) {
					result = i;
					cout << YELLOW() << BOLD() << intVec[i] << " " << RESET();
				} else {
					cout << intVec[i] << " ";
				}
			}
			auto rvalue = easyfind(intVec, target);
			cout << YELLOW() << "found target " + std::to_string(target) + " at index " + std::to_string(rvalue) << RESET() << endl;

			return result == rvalue;

		} catch (const std::runtime_error& e) {
			cout << YELLOW() << "Exception in VectorTest" << RESET() << endl;
			if (result == SIZE_MAX && e.what() == std::string("Value not found")) {
				return true;
			} else {
				return false;
			}
		}
	}

	bool	ArrayTest() {
		int target = TARGET;
		constexpr int size = SIZE;
		size_t result = SIZE_MAX;

		try {
			auto vec = shuffledVector(size);
			int intArr[size];
			std::copy(vec.begin(), vec.end(), intArr);

			cout << YELLOW() << "Searching for target " + std::to_string(target) + " in array  : " << RESET();
			for (int i = 0; i < size; ++i) {
				if (intArr[i] == target) {
					result = i;
					cout << YELLOW() << BOLD() << intArr[i] << " " << RESET();
				} else {
					cout << intArr[i] << " ";
				}
			}
			auto rvalue = easyfind(intArr, target);
			cout << YELLOW() << "found target " + std::to_string(target) + " at index " + std::to_string(rvalue) << RESET() << endl;

			return result == rvalue;

		} catch (const std::runtime_error& e) {
			cout << YELLOW() << "Exception in ArrayTest" << RESET() << endl;
			if (result == SIZE_MAX && e.what() == std::string("Value not found")) {
				return true;
			} else {
				return false;
			}
		}
	}

	bool	ListTest() {
		int target = TARGET;
		constexpr int size = SIZE;
		size_t result = SIZE_MAX;

		try {
			auto vec = shuffledVector(size);
			std::list<int> intList(vec.begin(), vec.end());

			cout << YELLOW() << "Searching for target " + std::to_string(target) + " in list   : " << RESET();

			//list does not have direct access, so we use an iterator
			int i = 0;
			for (auto it = intList.begin(); it != intList.end(); ++it, ++i) {
				if (*it == target) {
					result = i;
					cout << YELLOW() << BOLD() << *it << " " << RESET();
				} else {
					cout << *it << " ";
				}
			}
			auto rvalue = easyfind(intList, target);
			cout << YELLOW() << "found target " + std::to_string(target) + " at value " + std::to_string(rvalue) << RESET() << endl;

			return result == rvalue;

		} catch (const std::runtime_error& e) {
			cout << YELLOW() << "Exception in ListTest" << RESET() << endl;
			if (result == SIZE_MAX && e.what() == std::string("Value not found")) {
				return true;
			} else {
				return false;
			}
		}
	}

	bool	ForwardListTest() {
		int target = TARGET;
		constexpr int size = SIZE;
		size_t result = SIZE_MAX;

		try {
			auto vec = shuffledVector(size);
			std::forward_list<int> intFList(vec.begin(), vec.end());

			cout << YELLOW() << "Searching for target " + std::to_string(target) + " in fwd_lst: " << RESET();

			//forward list does not have [] access so we use range-based for loop and iterates over elements
			int i = 0;
			for (const auto& elem : intFList) {
				if (elem == target) {
					result = i;
					cout << YELLOW() << BOLD() << elem << " " << RESET();
				} else {
					cout << elem << " ";
				}
				++i;
			}
			auto rvalue = easyfind(intFList, target);
			cout << YELLOW() << "found target " + std::to_string(target) + " at value " + std::to_string(rvalue) << RESET() << endl;

			return result == rvalue;

		} catch (const std::runtime_error& e) {
			cout << YELLOW() << "Exception in ForwardListTest" << RESET() << endl;
			if (result == SIZE_MAX && e.what() == std::string("Value not found")) {
				return true;
			} else {
				return false;
			}
		}
	}

	bool	DequeTest() {
		int target = TARGET;
		constexpr int size = SIZE;
		size_t result = SIZE_MAX;

		try {
			auto vec = shuffledVector(size);
			std::deque<int> intDeque(vec.begin(), vec.end());

			cout << YELLOW() << "Searching for target " + std::to_string(target) + " in deque  : " << RESET();

			for (int i = 0; i < size; ++i) {
				if (intDeque[i] == target) {
					result = i;
					cout << YELLOW() << BOLD() << intDeque[i] << " " << RESET();
				} else {
					cout << intDeque[i] << " ";
				}
			}
			auto rvalue = easyfind(intDeque, target);
			cout << YELLOW() << "found target " + std::to_string(target) + " at value " + std::to_string(rvalue) << RESET() << endl;

			return result == rvalue;

		} catch (const std::runtime_error& e) {
			cout << YELLOW() << "Exception in DequeTest" << RESET() << endl;
			if (result == SIZE_MAX && e.what() == std::string("Value not found")) {
				return true;
			} else {
				return false;
			}
		}
	}

} // namespace

int main (void) {
	try {
		Tester test({
			VectorTest,
			ArrayTest,
			ListTest,
			ForwardListTest,
			DequeTest
		});

		test.run();

	}
	catch (const std::exception& e) {
		cout << "exception in main: " << e.what() << endl;
		return 1;
	}
	return 0;
}
