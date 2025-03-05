#include "Bureaucrat.hpp"
#define BUREAUCRATIC_LADDER 10
#include <limits>

int main (){
	try {
		Bureaucrat a;
		Bureaucrat b("Stevey", 2);
		a.upGrade();
		b.downGrade();
		Bureaucrat *c = new Bureaucrat[std::numeric_limits<unsigned int>::max()];
		c[1].getName();
		for (int i = 0; i < BUREAUCRATIC_LADDER; i++){b.upGrade();}
		cout << a << b;
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "Something else went wrong!" << endl;
	}
	return 0;
}
