#include <iostream>
using std::string;
using std::cout;
using std::endl;


class Entity {
	string Name_;
	unsigned int age_;
	
public:
	Entity() {
		cout << "def ctor" << endl;
	}

	Entity(const string& name) : Name_(name), age_(-1) {//string param. ctor
		cout << "str ctor" << endl;
	}

	explicit Entity(unsigned int age) : Name_("Unknown"), age_(age) {//age param. ctor
		cout << "age " + std::to_string(age_) + " ctor" << endl;
	}

	Entity (const Entity& other) : Name_(other.Name_), age_(other.age_) {
		cout << "copy ctor" << endl;
	}

	string getName() {return Name_;}
	unsigned int getAge() const {return age_;}
};

void	PrintEntity(const Entity& entity) {
	cout << entity.getAge() << endl;
	(void)entity;
}


int main (void)
{
	// Entity a("Hellokitty");
	// Entity b = 21;

	// Entity a = "hello";
	// Entity b = 21;
Entity c = (Entity)22;
	PrintEntity(Entity (23));
	// PrintEntity(Entity("Kitty"));

	return 0;
}