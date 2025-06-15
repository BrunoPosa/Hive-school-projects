#include "Iter.hpp"

using std::string;
using std::cout;
using std::endl;

namespace {
	class Hiver {
		std::string name_;
		int cohort_;
		std::string coalition_;
	public:
		Hiver() : cohort_{5}, coalition_{}
		{};
		void setName(std::string name) { name_ = name; }
		void setCohort(int cohort) { cohort_ = cohort; }
		void setCoalition(std::string coalition) { coalition_ = coalition; }
		std::string getName() { return name_; }
		int	getCohort() { return cohort_; }
		std::string	getCoalition() { return coalition_; }
	};

	std::ostream&	operator<<(std::ostream& os, Hiver& obj)
	{
		os << "Hiver " << obj.getName() << " from cohort " << obj.getCohort() << " and coalition: " << obj.getCoalition(); 
		return os;
	}

	void printNumSquare(int num) {
		std::cout << num * num << std::endl;
	}

	void strToUpper(std::string str) {
		for (char& c : str) {
			c = std::toupper(c);
		}
		std::cout << str << std::endl;
	}


	/************/
	/*	TESTS	*/
	/************/
	void hiverClassTest() {
		cout << "hiverClassTest() - iter with printer" << endl;
		//init
		int n = 10;
		Hiver hivers[n];
		for (int i = 0; i < n; i++) {
			(i % 2) ? hivers[i].setCoalition("Guardian") : hivers[i].setCoalition("Builders");
			(i % 3) ? hivers[i].setCohort(5) :
				(i % 2) ? hivers[i].setCohort(6) : hivers[i].setCohort(7);
			hivers[i].setName(std::string("'peop" + std::to_string(i) + "_" + hivers[i].getCoalition() + std::to_string(hivers[i].getCohort())) + "'");
		}
		//run
		iter(hivers, n, printer);
	}

	void numTest1() {
		cout << "numTest1() - iter with printNumSquare" << endl;
		//init
		int n = 10;
		int arr[n];
		for (int i = 0; i < n; i++) {
			arr[i] = i;
		}
		//run
		iter(arr, n, printNumSquare);
	}

	void stringTest1() {
		//init
		int n = 10;
		string strings[n];
		std::srand(std::time(nullptr));
		cout << "init values of strings[]:" << endl;
		for (int i = 0; i < n; i++) {
			strings[i] = "rando_" + std::to_string(std::rand());
			cout << *(strings + i) << endl;
		}
		//run
		cout << "\nafter iter with strToUpper:" << endl;
		iter(strings, n, strToUpper);
	}
}

int main (void) {
	
	hiverClassTest();
	cout << "\n---------------------------------\n" << endl;
	numTest1();
	cout << "\n---------------------------------\n" << endl;
	stringTest1();

	return 0;
}