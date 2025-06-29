#pragma once

#include <stack>

//main()
#include <iostream>
#include <vector>
#include <functional>
#include <list>

template<typename T, typename Sequence = std::deque<T>>
class MutantStack : public std::stack<T, Sequence> {
public:
	typedef typename Sequence::iterator iterator;
	typedef typename Sequence::const_iterator const_iterator;

	MutantStack() = default;
	MutantStack(const MutantStack& other) = default;
	MutantStack& operator=(const MutantStack& other) {
		if (this != &other) {
			std::stack<T>::operator=(other);
		}
		return *this;
	}
	~MutantStack() = default;

	iterator	begin() { return std::begin(this->c); }
	iterator	end() {	return std::end(this->c);	}
	const_iterator	begin() const { return std::begin(this->c); }
	const_iterator	end() const { return std::end(this->c); }
};
