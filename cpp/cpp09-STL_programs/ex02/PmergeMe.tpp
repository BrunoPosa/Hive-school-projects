#include "PmergeMe.hpp"

using std::cout;
using std::endl;

//is it faster to process passing a single argument of space-separated ints? or as many args
template<typename T>
bool PmergeMe<T>::validateStr(int ac, char **args) {
	for (int i = 1; i < ac; i++) {
		int j = 0;
		if (args[i][0] == '\0') {
			return false;
		}

		while (args[i][j]) {
			if (std::isdigit(args[i][j++]) == false) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
void PmergeMe<T>::sort(T args) {
	cout << "sorting.." << endl;
	(void) args;
}