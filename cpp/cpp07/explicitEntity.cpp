#include <iostream>
using std::string;
using std::cout;
using std::endl;


class Entity {
	string Name_;
	int age_;
	
public:
	Entity() {
		cout << "def ctor" << endl;
	}

	Entity(const string& name) : Name_(name), age_(-1) {//string param. ctor
		cout << "str ctor" << endl;
	}
	 Entity(int age) : Name_("Unknown"), age_(age) {
		cout << "age " + std::to_string(age_) + " ctor" << endl;
	}

	string getName() {return Name_;}

};

void	PrintEntity(const Entity& entity) {
	// cout << entity.getName() << endl;
	(void)entity;
}


int main (void)
{
	// Entity a("Hellokitty");
	// Entity b(22);

	// Entity a = "hello";
	Entity b = 21;


	PrintEntity(42);
	PrintEntity(Entity("Kitty"));

	return 0;
}