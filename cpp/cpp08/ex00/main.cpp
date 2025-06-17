#include "easyfind.hpp"

using std::cout;
using std::endl;

int main (void) {
	
	std::vector<int> intVec;
	for (int i = 0; i < 15; i++) {
		intVec.push_back(15 - i);
	}
	int target = 7;
	size_t	index = easyfind(intVec, target);
	cout << "found target " + std::to_string(target) + " at index " + std::to_string(index) << endl;
	return 0;
}
