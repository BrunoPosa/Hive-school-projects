#pragma once

#include <stack>

//main()
#include <iostream>
#include <vector>
#include <functional>

template<typename T, typename Sequence = std::deque<T>>
class MutantStack : public std::stack<T, Sequence> {

	Sequence::iterator	begin() {
		return std::begin(this->c);
	}
};