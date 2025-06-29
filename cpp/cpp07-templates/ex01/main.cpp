#include "Iter.hpp"

using std::cout;
using std::endl;

namespace {

	/*	 ========== PREREQUISITES ==========	*/

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
		std::string getName() const { return name_; }
		int	getCohort() const { return cohort_; }
		std::string	getCoalition() const { return coalition_; }
	};

	std::ostream& operator<<(std::ostream& os, const Hiver& obj)
	{
		os << "Hiver " << obj.getName() << " from cohort " << obj.getCohort() << " and coalition: " << obj.getCoalition(); 
		return os;
	}

	void printNumSquare(int num) {
		cout << num * num << endl;
	}

	void strToUpper(std::string& str) {
		for (char& c : str) {
			c = std::toupper(c);
		}
		cout << str << endl;
	}


	/*	 ========== TESTS ==========	*/


	void hiverClassTest() {
		cout << "hiverClassTest() - iter with printer" << endl;
		
		int n = 10;
		Hiver hivers[10];
		for (int i = 0; i < n; i++) {
			(i % 2) ? hivers[i].setCoalition("Guardian") : hivers[i].setCoalition("Builders");
			(i % 3) ? hivers[i].setCohort(5) :
				(i % 2) ? hivers[i].setCohort(6) : hivers[i].setCohort(7);
			hivers[i].setName(std::string("'peop" + std::to_string(i) + "_" + hivers[i].getCoalition() + std::to_string(hivers[i].getCohort())) + "'");
		}

		iter(hivers, n, printer<Hiver>);
	}

	void numTest1() {
		cout << "numTest1() - iter with printNumSquare" << endl;
		
		int n = 10;
		int arr[10];
		for (int i = 0; i < n; i++) {
			arr[i] = i;
		}

		iter(arr, n, printNumSquare);
	}

	void stringTest1() {
		
		int n = 10;
		std::string strings[10];
		std::srand(std::time(nullptr));
		cout << "init values of strings[]:" << endl;
		for (int i = 0; i < n; i++) {
			strings[i] = "rando_" + std::to_string(std::rand());
			cout << *(strings + i) << endl;
		}

		cout << "\nafter iter with strToUpper:" << endl;
		iter(strings, n, strToUpper);
	}

	void	charTest() {

		const char charArray[] = {'a', 'b', 'c', 'd', 'e'};
		iter(charArray, sizeof(charArray), printer<char>);
	}
}

int main (void) {
	try {

		hiverClassTest();
		cout << "\n---------------------------------\n" << endl;
		numTest1();
		cout << "\n---------------------------------\n" << endl;
		stringTest1();
		cout << "\n---------------------------------\n" << endl;
		charTest();

	} catch (std::exception& e) {
		cout << "exception:" << e.what() << endl;
	}

	return 0;
}
