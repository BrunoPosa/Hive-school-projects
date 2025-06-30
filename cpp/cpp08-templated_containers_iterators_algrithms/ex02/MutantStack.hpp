#pragma once

#include <stack>

template<typename T, typename Sequence = std::deque<T>>
class MutantStack : public std::stack<T, Sequence> {
public:
	typedef typename Sequence::iterator iterator;
	typedef typename Sequence::const_iterator const_iterator;

	using std::stack<T, Sequence>::stack;

	iterator	begin() { return std::begin(this->c); }
	iterator	end() {	return std::end(this->c);	}
	const_iterator	begin() const { return std::begin(this->c); }
	const_iterator	end() const { return std::end(this->c); }
};
