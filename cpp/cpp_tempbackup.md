------ in ex=========
ENDIANNESS ==
Endianness defines how multi-byte data (like integers) are stored in memory (Little-endian has Least significant byte first	07 00 00 00, and Big-endian has Most significant byte first	00 00 00 07).
BigEndian is the dominant order in any network protocols, and is referred to as network order, for example. On the other hand, most PC's are little-endian.
Little-Endian (LE) Example (storing 0x12345678): Memory: 78 56 34 12

C++ principles/to do list for good code:
=========
-RAII (Resource Acquisition Is Initialization): C++ emphasizes the RAII pattern, where resources like memory and file handles are acquired during object creation and automatically released when objects go out of scope.

cpp oop principles: encapsulation, inheritance, polymorphism, and abstraction

== resources:
-slowly readding: Programming: Principles and Practice Using C++ by the creator of c++
-https://theswissbay.ch/pdf/Gentoomen%20Library/Programming/C%2B%2B/Addison%20Wesley%20-%20C%2B%2B%20by%20Dissection.pdf


'#pragma once' is the same as '#ifndef CPP_H \n #define CPP_H \n #endif'
pragma once does have one drawback (other than being non-standard) and that is if you have the same file in different locations (we have this because our build system copies files around) then the compiler will think these are different files.//stack_overflow

#include <stdio.h> vs #include <iostream> C headers ususally have .h and Cpp headers usually don't have any extension. C standard lib vs C++ standard lib difference. 

===== value catagories ======
Every C++ expression has a type, and belongs to a value category. The value categories are the basis for rules that compilers must follow when creating, copying, and moving temporary objects during expression evaluation.

The C++17 standard defines expression value categories as follows:

    A glvalue is an expression whose evaluation determines the identity of an object, bit-field, or function.
    A prvalue is an expression whose evaluation initializes an object or a bit-field, or computes the value of the operand of an operator, as specified by the context in which it appears.
    An xvalue is a glvalue that denotes an object or bit-field whose resources can be reused (usually because it is near the end of its lifetime). Example: Certain kinds of expressions involving rvalue references (8.3.2) yield xvalues, such as a call to a function whose return type is an rvalue reference or a cast to an rvalue reference type.
    An lvalue is a glvalue that isn't an xvalue.
    An rvalue is a prvalue or an xvalue.

The following diagram illustrates the relationships between the categories:

Diagram of C++ expression value categories.

The diagram begins with a box labeled expression, which has two children: glvalue and rvalue. glvalue has two children: lvalue and xvalue. rvalue has two children: prvalue and xvalue; xvalue is also a child of glvalue.

An lvalue has an address that your program can access. Examples of lvalue expressions include variable names, including const variables, array elements, function calls that return an lvalue reference, bit-fields, unions, and class members.

A prvalue expression has no address that is accessible by your program. Examples of prvalue expressions include literals, function calls that return a nonreference type, and temporary objects that are created during expression evaluation but accessible only by the compiler.

An xvalue expression has an address that no longer accessible by your program but can be used to initialize an rvalue reference, which provides access to the expression. Examples include function calls that return an rvalue reference, and the array subscript, member and pointer to member expressions where the array or object is an rvalue reference.
https://learn.microsoft.com/en-us/cpp/cpp/lvalues-and-rvalues-visual-cpp?view=msvc-170



"An lvalue refers to an object that persists beyond a single expression. An rvalue is a temporary value that does not persist beyond the expression that uses it."


Uniform (brace) initialization:
instead of using braces or assignment, you can use curly braces to initialize any object. Prevents narrowing✅
Consistent for all types✅ Safer than = or ()✅ Picks initializer_list when has option ⚠️
https://stackoverflow.com/questions/18222926/what-are-the-advantages-of-list-initialization-using-curly-braces



" Why would you use const& on a method?

The reference qualifier (& or &&) controls what kind of object (lvalue or rvalue) the method can be called on.
Signature	Can be called on...	Typical use
foo() const	lvalues and rvalues	General-purpose getter
foo() const &	only lvalues	Avoid temporary overhead
foo() &&	only rvalues	Optimized for temporaries (e.g. move)
foo() const &&	rvalues only, const	Safe move from temporaries "


===== names ======

- '::' scope resolution operator - highest precedance operator in cpp

-Translation unit:According to standard C++ (wayback machine link) : A translation unit is the basic unit of compilation in C++. It consists of the contents of a single source file, plus the contents of any header files directly or indirectly included by it, minus those lines that were ignored using conditional preprocessing statements.
A single translation unit can be compiled into an object file, library, or executable program.
The notion of a translation unit is most often mentioned in the contexts of the One Definition Rule, and templates

One mac i checked has c++ version that supports c17, and clang version that supports c14. Carlos later told me our school PCs use c++ as an alias for clang, so i guess by default we use C++ 14 standard here. But the Macs support C++17 fully as well, and mostly C++20 but with incomplete features. On other non-hive computers, c++ compiles with gcc or g++? 
```
% c++ --version
Ubuntu clang version 12.0.1-19ubuntu3
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

====== "using" and 'namespaces' =======
https://learn.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=msvc-170
A namespace is a declarative region that provides a scope to the identifiers (the names of types, functions, variables, etc) inside it. Namespaces are used to organize code into logical groups and to prevent name collisions that can occur especially when your code base includes multiple libraries. All identifiers at namespace scope are visible to one another without qualification. Identifiers outside the namespace can access the members by using the fully qualified name for each identifier, for example std::vector<std::string> vec;, or else by a using Declaration for a single identifier (using std::string), or a using Directive for all the identifiers in the namespace (using namespace std;). Code in header files should always use the fully qualified namespace name.
"Use a using directive in an implementation file (i.e. *.cpp) if you are using several different identifiers in a namespace; if you are just using one or two identifiers, then consider a using declaration to only bring those identifiers into scope and not all the identifiers in the namespace. "
A using directive can be placed at the top of a .cpp file (at file scope), or inside a class or function definition.

In general, avoid putting using directives in header files (*.h) because any file that includes that header will bring everything in the namespace into scope, which can cause name hiding and name collision problems that are very difficult to debug. Always use fully qualified names in a header file. If those names get too long, you can use a namespace alias to shorten them.


string	getType() const; <-- the 'trailing' const means the object calling the getType will not be modified. 


Grok about access specifiers:
In C++, access specifiers control the visibility and accessibility of class members (data and functions). Here’s a succinct breakdown:

    public:
        Accessible from anywhere (inside the class, derived classes, and external code).
        Example: public: void func(); → Callable via object (e.g., obj.func()).
    protected:
        Accessible within the class and its derived classes, but not from outside.
        Example: protected: int x; → Derived class can use x, but obj.x fails in main().
    private:
        Accessible only within the class itself, not in derived classes or externally.
        Example: private: int y; → Only class methods can access y.

Key Points

    Default: In a class, members are private unless specified; in a struct, they’re public.
    Inheritance: Affects how base class members are accessed in derived classes (e.g., public inheritance keeps public members public).
    Purpose: Enforces encapsulation—public for interface, protected for inheritance, private for implementation details.


=================================================
CPP 00 - Namespaces, classes, member functions, stdio streams, initialization lists, static, const, etc
=================================================


======= basic meanings - ex00 ========

- namespaces limit identically named variables' scopes
- Classes are an expanded concept of data structures: like data structures, they can contain data members, but they can also contain functions as members.
- An object is an instantiation of a class. In terms of variables, a class would be the type, and an object would be the variable.
- classes and structs are similar
- struct member functions are called just that, but often reffered to as 'methods', and methods get struct member variables passed to them implicitly. There is more to real methods, i guess?
- everything in a struct after 'private:' cannot be accessed from outside the struct but needs a method to touch it.
- A class is the same as a cpp struct, technically, but by default everything in a class is private. As a difference to C structs, classes can have functions. The important difference is the usage: "Basically all existing coding-standards agree that everything that consists of more than a few trivial public members and maybe some simple methods should be a class. Since it is generally considered a good idea to put the public interface first this ends up with the somewhat ironic situation that most classes start with public:."
 
-A constructor is a function that is called upon the construction of an object to initialize it's state correctly. Many languages have this feature. C++ is however one of the relatively few languages that also have the opposite: A destructor.

A destructor is a function that will run whenever an object ceases to exist. It's main purpose is to clean up any resources that the object might own in.

- character output cout include <iostream> std::cout << "Hello world\n" part of global namespace (::) std. std::cerr - prints to stderr. << std::endl is a portable way to add a newline, and this one should also flush the buffer. 

- "As we see the objects that are constructed first get destructed last. This is guaranteed by the standard and quite important: Assume we want acquiring multiple resources, where some cannot exist without others already existing; thanks to the guaranteed order of destruction no object will cease to exist while other, later constructed ones, might still need it. This technique is called “Resource Acquisition Is Initialization” (RAII) and that it is one the most important techniques of C++. Some people call it C++'s greatest feature"

-Member attributes are just member variables in a class.

-this-> is a pointer to the current instance

Practical, related to exercise:
https://en.cppreference.com/w/cpp/string/byte/toupper
- Tidbit: i don't think i need to use counter overflow protection for int i and k counters as the arg_max of the ubuntu is set to 2 million arguments, and likely bash has another limit before that. 

---- ---- 
Encapsulation pros:
-Data Hiding: Internal data is kept private, preventing direct modification from outside the class.
-Controlled Access: Public methods (getters and setters) are used to interact with the private data, ensuring data integrity and validation.
-Improved Maintenance: Changes to the internal structure of the class don't affect external code as long as the public interface remains the same.
---- ---- 


========= ex01 ==========

- initialization list is the : after a class constructor, and it uses direct initialization, instead of by default the class constructor with empty init. list, which would use initialization by value twice? So supposedly more efficient than initializing inside the constructor body. 
- Members are always initialized in the order they are declared in the class, not the order they appear in the initialization list, so careful! Bc this can lead to undefined behavior if init.list is in wrong order.
-Only constructors have initialization lists.
- type specifier is 'int', 'double' etc in front of variable. Type modifiers are 'signed', 'unsigned', 'long', 'short'; Type qualifiers are 'const', 'mutable', 'volatile'. A SPECIFIER SEQUENCE combines keywords (like const, volatile, unsigned, etc.) and type specifiers (like int, char, float, etc.) to describe the exact nature of the type being declared.
-"A class in C++ is an extension of the idea of struct found in C. A class packages a data type with its associated functions and operators. This in turn can be used to implement abstract data types (ADTs). An abstract data type, such as a stack, is a set of values and operations that define the type A large part of the object-oriented programming (OOP) design process involves thinking up the appropriate ADTs for a problem."


===
Eval lessons:
-Must not print to stderr!
-Use string or upper in ex00 instead of toupper and going char by char!
-Default constructor can be totally omitted from the class. I knew it can be omitted from the class definitino if I specify it as Contact() = default; but it can actually fully be omitted (obviously in case there are no primitive members and there is another constructor for the string members).
--"You should be able to use each of your headers independently from others. Thus,
they must include all the dependencies they need. However, you must avoid the
problem of double inclusion by adding include guards"
-When i saw the "extra" Account files on intra, I went to google to research the names and people coding that, and then posted a question in Discord. I could have simply revisited the subject and noticed the exercise I did not do which was not mandatory. 
-I think i did not equip the ex01 program to take in redirection from /dev/random or another infinite stream. I guess that could have been handled by handling the instream in chunks (using std::cin.read)
===





=================================================
CPP 01
=================================================

-if newZombie() doesn't need to access any instance-specific data (like _name), it should be declared as a static member function. Static member functions belong to the class rather than any specific instance, so you can call them using the class name.

-class members are by default private; if not explicitly set to protected or public. This behaviour promotes encapsulation. 

-Most implementations of std::string can store small strings (typically up to 15–23 characters, depending on the platform) in a statically allocated internal buffer. For small values of int, this optimization means no dynamic memory allocation is required, so exceptions like std::bad_alloc are avoided. So, I don't check for 'malloc failures' in std::to_upper(int) if i am using ints. 

-Calling delete[] on a nullptr is safe in C++, and it does nothing. Although it is safer to call delete[] when there is a validly allocated pointer to mallocd memory.

-huh, funny. When i write : ```Zombie z; z = Zombie("John")```, there is two objects, and the first 'z' gets destroyed when we assign it the constructor Zombie(name).

------References a la GPT: Alias for a variable:
    -A reference acts as an alternative name for a variable.
    	Any operation on the reference directly affects the original variable.
	-Must be initialized at declaration:
	    You must assign a reference to an existing variable when you declare it.
	-Cannot be null:
	    Unlike pointers, references must always refer to a valid object.
	-No reseating:
    	A reference cannot be changed to refer to another variable after initialization.



------------the main practical difference between a struct and a class in cpp is its access control:
	-the struct has members public by default, inheriting also public by default
	-class has private by default, inheriting private as well. 
	Use struct when you primarily want a simple, data-holding object without requiring encapsulation
	or advanced features (although you can use access control and functions in structs.
	Use class when you want to define a more complex type with encapsulation, access control,
	or when you're implementing object-oriented features like inheritance or polymorphism.


------ in ex04 i had class private memnber variables string& type, instead of just string. That caused issues where the scope wouild exit and i'd be using dangling string pointers with garbage values. 







=================================================
CPP 02 - Ad-hoc polymorphism, operator overloading, and Orthodox Canonical class form
=================================================







====================================================
CPP 03 - Inheritance
====================================================
--------Inheritance - The capability of a class to derive properties and characteristics from another class 
class  derived_class_name : access-specifier  base_class_name
{
       //    body ....
};

Inheritance Modes:
-If we derive a subclass from a public base class. Then the public member of the base class will become public in the derived class and protected members of the base class will become protected in the derived class.

-If we derive a subclass from a Protected base class. Then both public members and protected members of the base class will become protected in the derived class.

-If we derive a subclass from a Private base class. Then both public members and protected members of the base class will become private in the derived class. They can only be accessed by the member functions of the derived class. Private mode is the default mode that is applied when we don’t specify any mode.



-------Virtuality- Geeks for geeks -
A virtual function (also known as virtual methods) is a member function that is declared within a base class and is re-defined (overridden) by a derived class. When you refer to a derived class object using a pointer or a reference to the base class, you can call a virtual function for that object and execute the derived class’s version of the method.

    Virtual functions ensure that the correct function is called for an object, regardless of the type of reference (or pointer) used for the function call.
    They are mainly used to achieve Runtime polymorphism.
    Functions are declared with a virtual keyword in a base class.
    The resolving of a function call is done at runtime.

Rules for Virtual Functions:
    Virtual functions cannot be static.
    A virtual function can be a friend function of another class.
    Virtual functions should be accessed using a pointer or reference of base class type to achieve runtime polymorphism.
    The prototype of virtual functions should be the same in the base as well as the derived class.
    They are always defined in the base class and overridden in a derived class. It is not mandatory for the derived class to override (or re-define the virtual function), in that case, the base class version of the function is used.
    A class may have a virtual destructor but it cannot have a virtual constructor.
    
    Grok: Virtuality in Inheritance: The classic OOP approach. You define a base class with virtual methods, and derived classes inherit and override. It’s intuitive for modeling “is-a” relationships (e.g., Dog is-an Animal).
    


Grok3:
Key Rule in C++: If a base class destructor is virtual, all derived class destructors are automatically virtual, regardless of whether the virtual keyword is used in the derived class declaration. This is because the virtual nature of the destructor is inherited.


====================================================
CPP 04 - Subtype polymorphism, abstract classes, interfaces
====================================================

-Subtype polymorphism - Base class pointers/references can use derived class methods dynamically. *Uses virtual functions* and vtable (makes it have the slight overhead of looking up from the lookup table)

-Abstract class - A class that cannot be instantiated and is meant to be a blueprint for derived classes, by containing *at least one pure virtual function (= 0)*; Why It’s Useful: It’s a way to define “what” (interface) without dictating “how” (implementation), ensuring consistency across subclasses.

-Interface - A class where *all methods are pure virtual (= 0)*. Purpose: Defines a contract for derived classes without any implementation. Difference from Abstract Classes? No concrete methods or member variables (except possibly static ones)

Grok: When to Use What:
    Interface: Define a capability (e.g., Serializable, Comparable) across unrelated classes.
    Abstract Class: Share code and enforce some structure (e.g., Shape with a default describe()).
    Polymorphism: Whenever you need runtime flexibility with either.



---Copying can be done via copy constructor or assinment operator. Depending upon the resources like dynamic memory held by the object, either we need to perform Shallow Copy or Deep Copy in order to create a replica of the object.

Grok:
---Shallow Copy: Copies an object’s values, but shares references/pointers to nested data. Cheap, fast, but changes to the original’s nested data affect the copy (e.g., obj = other; in C++ with pointers).

---Deep Copy: Copies an object and recursively duplicates all nested data. Expensive, slower, but the copy is fully independent (e.g., custom copy constructor cloning a pointer’s data).





---------EVAL cpp04
Iurii (Juri) H6:
We delved into handling exceptions and Iurii was masterful in testing and asking the right questions. Iurii noticed an issue despite not being experienced with cpp yet: the catch{} block of my try-catch did not have explicit deletes, so we spent a good amount of time trying to test for leaks by limiting the virtual memory (ulimit -v) and changing the main to allocate __INTMAX__, but we were not clearly and fully confident in valgrind's output as the exceptions and running out of memory interfered. Iurii gave me great tips about writing better testable code, as my mains were low quality. After the eval we learned the best practice is to use smart pointers for allocations, as otherwise the catch block requires manual cleanup of resources. We also noticed the visibility of two member functions could have been private. I am grateful for the massive patience Iurii demonstrated and for a rich and rigorous eval and discussion where I learned about programming in general and ways to improve my testing skills.
ChatGPT: "Heap allocation (new): memory must be freed manually
If the object is created on the heap (new), you must delete it in catch, otherwise there will be a memory leak"





====================================================
CPP 05 - Repetition and Exceptions
====================================================

If declaring class inside a class, pls make it private as it shan't become part of the API in case some user uses it. You want to hide them and have them able to change swiftly internally with a persistent interface. 
class List
{
    public:
        List(): head(nullptr), tail(nullptr) {}
        int i;
    private:
        class Node
        {
              public:
                  int   data;
                  Node* next;
                  Node* prev;
        };
    private:
        Node*     head;
        Node*     tail;
};


=== Static_assert, a la StackOverflow: ===
"static_assert is used to make assertions at compile time. When the static assertion fails, the program simply doesn't compile. This is useful in various situations. For example, if you implement some functionality that critically depends on an unsigned int object having exactly 32 bits. You can add a static_assert to your code like this:

static_assert(sizeof(unsigned int) * CHAR_BIT == 32);

On platforms with differently sized unsigned int type, the compilation will fail, drawing attention of the developer to the problematic portion of code."

static_assert works only with static constants (known at compile time), apparently. There is nifty tricks to replicate its behaviour for purposes of pre C++11 but none are as verbose.


================== ex00 ================
-if name is const, it mandates logically the Bureaucrat class cannot have a copy assignment operator, bc they would be changing the name. (?)

-"class std::exception Provides consistent interface to handle errors through the throw expression."
-"Throwing an exception transfers control to a handler.
An exception can be thrown from throw expressions, the following contexts may also throw exceptions:
    allocation functions
    dynamic_cast
    typeid
    new expressions
    standard library functions "

==Exceptions==
"
Exception handling provides a way of transferring control and information from some point in the execution of a program to a handler associated with a point previously passed by the execution (in other words, exception handling transfers control up the call stack).

Evaluating a throw expression will throw an exception. Exceptions can also be thrown in other contexts.

In order for an exception to be caught, the throw expression has to be inside a try block, and the try block has to contain a handler that matches the type of the exception object. 

Throwing an exception initializes an object with dynamic storage duration, called the exception object.
Once the exception object is constructed, the control flow works backwards (up the call stack) until it reaches the start of a try block, at which point the parameters of all associated handlers are compared, in order of appearance, with the type of the exception object to find a match. If no match is found, the control flow continues to unwind the stack until the next try block, and so on. If a match is found, the control flow jumps to the matching handler.

As the control flow moves up the call stack, destructors are invoked for all objects with automatic storage duration that are constructed, but not yet destroyed, since the corresponding try block was entered, in reverse order of completion of their constructors. If an exception is thrown from a destructor of a local variable or of a temporary used in a return statement, the destructor for the object returned from the function is also invoked. 
"

-noexcept specifier: Specifies whether a function could throw exceptions.
-noexcept operator: The noexcept operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions. 

==enum class===
-There are two distinct kinds of enumerations: unscoped enumeration (declared with the enum-key enum) and scoped enumeration (declared with the enum-key enum class or enum struct)
-enum class is not a real class:
    It cannot have constructors or member functions.
    It cannot have instance variables.
    It is just an integer type with stronger type safety than a normal enum.


Defining the GradeTooLowException class so that it inherits from the std::exception and overrides the what() virtual base class' function.




====================================================
CPP 06 - Casts
====================================================

-there are pseudo-literals e.g. for floats they are +inff, -inff, nanf (not-a-number undefined math results)

Stack overflow types in C++:
  =  Object types
        - Scalars
            arithmetic (integral, float)
            pointers: T * for any type T
            enum
            pointer-to-member
            nullptr_t
        - Arrays: T[] or T[N] for any complete, non-reference type T
        - Classes: class Foo or struct Bar
            Trivial classes
            Aggregates
            POD classes
            (etc. etc.)
        - Unions: union Zip
   = References types: T &, T && for any object or free-function type T
   = Function types
        Free functions: R foo(Arg1, Arg2, ...)
        Member functions: R T::foo(Arg1, Arg2, ...)
   = void



Apparently the system/compiler might have different char types: signed or unsigned, and their min/max are not guaranteed to be the same across implementations.


-Apparently it is bad practice to use underscores or double underscores as start to variable names, as they are reserved by the standard for global use, e.g. libraries, and can therefore cause hard-to-debug bugs. (*_vptr was one variable for a lookup table IIRC)

-Data serialization is the process of converting an object into a stream of bytes to more easily save or transmit it. The reverse process—constructing a data structure or object from a series of bytes—is deserialization

-uintptr_t is An integer big enough to hold a pointer safely

-const_cast conversion 		adds or removes const (good e.g. for making pointers const, or in legacy APIs when it is necessary to modify consts)
-static_cast conversion 	performs basic conversions (Compile time)
-dynamic_cast conversion 	performs checked polymorphic conversions
-reinterpret_cast conversion 	performs general low-level conversions
-standard conversions 		implicit conversions from one type to another

-reinterpret_cast lets you treat some memory as a different type, even if it makes no logical sense.

-dynamic_cast conversion - Safely converts pointers and references to classes up, down, and sideways along the inheritance hierarchy. Runtime

========================= ex02 =========================
-Why dynamic_cast? Used only for polymorphic types
    Ensures Safe Downcasting:
        Base is the parent class, and A, B, and C are derived classes.
        dynamic_cast checks at runtime whether a Base* or Base& actually refers to an A, B, or C.
        If the cast fails, dynamic_cast:
            Returns nullptr for pointers.
            Throws an exception for references.
    Prevents Undefined Behavior:
        If you use static_cast<A*>(p), the compiler assumes the cast is valid but does not check.
        If p actually points to a B or C object, but you force static_cast<A*>(p), you'll get undefined behavior.
        dynamic_cast prevents accidental misinterpretation of types.
When Could static_cast Work?
    If you are sure about the object's type (e.g., converting a Base* that was originally created as A*), then static_cast might work.
    But here, identify(Base*) must handle unknown types at runtime, so dynamic_cast is safer.





====================================================
CPP 07 - Templates
====================================================
-typename
-In the template parameter list of a template declaration, typename can be used as an alternative to class to declare type template parameters and template template parameters(since C++17).
-Inside a declaration or a definition of a template, typename can be used to declare that a dependent qualified name is a type. 









------------------------------------------
Pablo's notes

06/12/2024
In honor of **@Mike the Greek** I instantiate this note.

He review my code and give some tips on which is the proper way to write cpp, as my code looks good but is clear that is not written by someone that codes in cpp.

For example the for loop here to append the strings works, but we shall always avoid using overload operators like `+=`. Seem simple code, but using this type of operators has a lot of work behind and is not the recommended way, because depend what you are appending the results can be not as you expect.

> [!info] **What is Operator Overloading?**  
> 
> Operator overloading in C++ is the ability to redefine the behavior of operators (like `+`, `-`, `*`, `+=`, etc.) for custom types, such as classes or structs. By overloading an operator, you can specify how it works with objects of your class.  
>  
> For example, instead of using the `+` operator to add two integers, you could use it to combine two objects of a custom class (e.g., adding two `Point` objects). This allows you to write cleaner, more intuitive code.
> 
> In simpler terms, **overloading** means you give new functionality to operators for your specific data types, so that the same operator can behave differently depending on the type of the operands.

**The correct cpp way is always to use the methods for the class and concatenating them if needed.**

``` cpp
// C way
std::string str;
for (int i = 1; i < argc; i++)
{
	str += argv[i];
	if (i < argc - 1)
		str += " ";
}

// Cpp way
std::string str;
for (int i = 1; i < argc; i++)
	str.append(argv[i]).push_back(' ');
str.pop_back(); // remove the trailing whitespace

```

Another example of overworking. The wrong example calls the constructor, the destructor of the old string and a lot of things are happening under the hood. The clear +  append example is more efficient and controled.

``` cpp
// wrong
str = std::string("NewString");

// good
str.clear();
str.append("NewString");

// more optimization
//use reserve if you know before hand the amount of data you need after all the appends, so you don't realloc continuosly.
std::string str;
str.reserve(120);
std::string str(argv[0]); //changes during runtime
std::string str{"Hello"}; //never changes, can be optimised during compile time
```

Always when starting with a new class, use the [cppreference](https://en.cppreference.com/w/cpp/string/basic_string) page to see which methods are available for it.

**Use modularity as much as possible, that the cpp way. Even for small functions**

``` cpp
// C way
for (char& c : str)
	c = std::toupper(c);

// Cpp way
static inline void stringToUpper(std::string &str)
{
	for (char& c : str)
			c = std::toupper(c);
}

// C98 way
for (size_t i = 0; i < str.length(); i++)
	str.at(i) = std::toupper(str.at(i));
```

We can use `exceptions` to catch any error we define. If we call it on the main, any thing downstream will be cached and returned into main directly.

**We use exception flags so we don't need to add error handling repetitively in any scenario that might fail.**

``` cpp
int main(int argc, char **argv)
{
	std::cin.exceptions(std::ios_base::iostate::_S_eofbit | std::ios_base::iostate::_S_failbit);
   
   PhoneBook phonebook;

	if(argc != 1)
    {
        std::cout << "Usage: ./awesome_phonebook" << std::endl;
        exit(1);
    }
	try{
		phonebook.choiceAction();
	}
	catch(std::exception e)
	{
	 	std::cout << "EOF found" << e.what();
	}
    // cleanup code
    return 0;
}
```

Another example can be the use of exceptions with expected data

``` cpp
std::cin.exceptions(std::ios_base::iostate::_S_failbit);
// we define input as int, so if cin get anything that is not an int, it will catch the fail ane exit
int input;
std::cin >> input;
```

**Almost all we use are classes**. A string is a class, with it's own methods. If we use `ifstream`, is a class. So it has also constructors that we call "without noticing".

``` cpp
// here we are calling the constructor
// that also opens the file
std::ifstream file(infile);
if (!file.is_open())
		std::cerr << "Failed to open the file!" << std::endl;

// is the equivalent to this
std::ifstream file;
fileopen("something");
if (!file.is_open())
		std::cerr << "Failed to open the file!" << std::endl;
```
