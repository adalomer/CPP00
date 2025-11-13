# 🎯 C++ Quick Reference Card - CPP00-CPP04

## 📌 CPP00 - Essential Syntax Cheatsheet

### Class Declaration & Definition
```cpp
// Header (.hpp)
class MyClass {
private:
    int privateVar;
protected:
    int protectedVar;
public:
    MyClass();                    // Constructor
    MyClass(int value);           // Parameterized constructor
    MyClass(const MyClass& other); // Copy constructor
    ~MyClass();                   // Destructor
    void method();
    int getValue() const;         // Const method
};

// Implementation (.cpp)
MyClass::MyClass() : privateVar(0) {}
MyClass::~MyClass() {}
void MyClass::method() { /* ... */ }
```

### Memory Allocation
```cpp
// Stack
MyClass obj;                  // Auto destructor

// Heap
MyClass* ptr = new MyClass(); // Manual delete needed
delete ptr;

// Array
int* arr = new int[10];
delete[] arr;                 // Array delete!
```

### This Pointer
```cpp
class MyClass {
    int value;
public:
    void setValue(int value) {
        this->value = value;  // Disambiguate
    }
    MyClass& returnSelf() {
        return *this;         // Return current object
    }
};
```

### Const Correctness
```cpp
const int x = 10;            // Const variable
const int* ptr = &x;         // Pointer to const
int* const ptr2 = &y;        // Const pointer
const int* const ptr3 = &x;  // Both const

// Const method (doesn't modify object)
int getValue() const { return value; }
```

### Reference vs Pointer
```cpp
int x = 10;

// Reference (alias)
int& ref = x;                // Must initialize
ref = 20;                    // x becomes 20
// Can't rebind to another variable

// Pointer
int* ptr = &x;               // Can be NULL
*ptr = 30;                   // x becomes 30
ptr = &y;                    // Can point elsewhere
```

### Pass by Value/Reference/Pointer
```cpp
void byValue(int x);              // Copy (slow for large objects)
void byReference(int& x);         // Original modified
void byConstRef(const int& x);    // Read-only, efficient
void byPointer(int* x);           // Can be NULL, original modified
```

### Initialization List
```cpp
class MyClass {
    const int x;
    int& ref;
public:
    // Must use initialization list for const/reference
    MyClass(int val, int& r) : x(val), ref(r) {
        // Constructor body
    }
};
```

---

## 📌 CPP01 - Memory & References

### New vs Delete
```cpp
// Single object
int* p = new int(10);
delete p;

// Array
int* arr = new int[10];
delete[] arr;  // MUST use []

// Object
MyClass* obj = new MyClass();
delete obj;    // Calls destructor
```

### Reference Types
```cpp
int x = 10;
int& ref = x;        // lvalue reference
const int& cref = x; // const reference

// Can't do:
int& ref;            // ERROR: must initialize
int& ref = 5;        // ERROR: can't bind to temporary (C++98)
```

### Pointer to Member Function
```cpp
class MyClass {
public:
    void method1() { std::cout << "M1"; }
    void method2() { std::cout << "M2"; }
};

// Pointer to member function
void (MyClass::*funcPtr)() = &MyClass::method1;

MyClass obj;
(obj.*funcPtr)();    // Call via object
```

### File Streams
```cpp
#include <fstream>

// Read
std::ifstream infile("input.txt");
std::string line;
while (std::getline(infile, line)) {
    // Process line
}
infile.close();

// Write
std::ofstream outfile("output.txt");
outfile << "Hello World" << std::endl;
outfile.close();
```

---

## 📌 CPP02 - Operator Overloading

### Orthodox Canonical Form (Rule of Three)
```cpp
class MyClass {
private:
    int* data;
public:
    // 1. Default Constructor
    MyClass() : data(NULL) {}
    
    // 2. Copy Constructor (Deep Copy!)
    MyClass(const MyClass& other) {
        data = new int(*other.data);
    }
    
    // 3. Copy Assignment Operator
    MyClass& operator=(const MyClass& other) {
        if (this != &other) {  // Self-assignment check
            delete data;        // Clean old
            data = new int(*other.data);  // Deep copy
        }
        return *this;
    }
    
    // 4. Destructor
    ~MyClass() {
        delete data;
    }
};
```

### Operator Overloading Examples
```cpp
class Number {
    int value;
public:
    // Arithmetic
    Number operator+(const Number& other) const {
        return Number(value + other.value);
    }
    
    // Compound assignment
    Number& operator+=(const Number& other) {
        value += other.value;
        return *this;
    }
    
    // Comparison
    bool operator==(const Number& other) const {
        return value == other.value;
    }
    
    // Increment (prefix)
    Number& operator++() {
        ++value;
        return *this;
    }
    
    // Increment (postfix)
    Number operator++(int) {  // int = dummy parameter
        Number temp(*this);
        ++value;
        return temp;
    }
    
    // Stream insertion (friend function)
    friend std::ostream& operator<<(std::ostream& os, const Number& n) {
        os << n.value;
        return os;
    }
};
```

### Fixed Point Numbers
```cpp
class Fixed {
private:
    int rawBits;
    static const int fractionalBits = 8;
public:
    Fixed() : rawBits(0) {}
    
    Fixed(const int value) {
        rawBits = value << fractionalBits;  // value * 256
    }
    
    Fixed(const float value) {
        rawBits = roundf(value * (1 << fractionalBits));
    }
    
    float toFloat() const {
        return (float)rawBits / (1 << fractionalBits);
    }
    
    int toInt() const {
        return rawBits >> fractionalBits;  // rawBits / 256
    }
};
```

---

## 📌 CPP03 - Inheritance

### Basic Inheritance
```cpp
class Base {
protected:
    int protectedValue;
private:
    int privateValue;
public:
    Base() : protectedValue(0), privateValue(0) {}
    virtual ~Base() {}  // ALWAYS virtual in base class!
    
    void baseMethod() { /* ... */ }
};

class Derived : public Base {
public:
    Derived() : Base() {  // Call base constructor
        protectedValue = 10;  // Can access protected
        // privateValue = 20;  // ERROR: can't access private
    }
    
    void derivedMethod() {
        baseMethod();  // Can call public base methods
    }
};
```

### Inheritance Types
```cpp
// Public inheritance (most common)
class Derived : public Base { };
// Base's public → Derived's public
// Base's protected → Derived's protected

// Protected inheritance
class Derived : protected Base { };
// Base's public → Derived's protected
// Base's protected → Derived's protected

// Private inheritance
class Derived : private Base { };
// Base's public → Derived's private
// Base's protected → Derived's private
```

### Multiple Inheritance
```cpp
class Base1 {
public:
    void method1() { }
};

class Base2 {
public:
    void method2() { }
};

class Derived : public Base1, public Base2 {
public:
    void method() {
        method1();  // From Base1
        method2();  // From Base2
    }
};
```

### Diamond Problem & Virtual Inheritance
```cpp
class Base {
public:
    int value;
};

// Without virtual: Base is duplicated!
class Left : virtual public Base { };
class Right : virtual public Base { };
class Diamond : public Left, public Right {
    // Only ONE copy of Base thanks to virtual inheritance
};
```

### Constructor/Destructor Order
```cpp
// Construction: Base → Derived
// Destruction: Derived → Base (reverse)

class Base {
public:
    Base() { std::cout << "Base Constructor\n"; }
    ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "Derived Constructor\n"; }
    ~Derived() { std::cout << "Derived Destructor\n"; }
};

// Output when creating Derived:
// Base Constructor
// Derived Constructor
// Derived Destructor
// Base Destructor
```

---

## 📌 CPP04 - Polymorphism

### Virtual Functions
```cpp
class Animal {
public:
    virtual void makeSound() const {  // Virtual = runtime polymorphism
        std::cout << "Animal sound\n";
    }
    virtual ~Animal() {}  // Virtual destructor ESSENTIAL!
};

class Dog : public Animal {
public:
    void makeSound() const {  // Override (implicit)
        std::cout << "Woof!\n";
    }
};

// Polymorphism
Animal* animal = new Dog();
animal->makeSound();  // Calls Dog::makeSound() (runtime binding)
delete animal;        // Calls Dog::~Dog() then Animal::~Animal()
```

### Pure Virtual Functions (Abstract Classes)
```cpp
class AbstractShape {
public:
    virtual double area() const = 0;  // Pure virtual
    virtual ~AbstractShape() {}
    
    // Can have non-pure virtual
    virtual void display() const {
        std::cout << "Area: " << area() << std::endl;
    }
};

// Cannot instantiate:
// AbstractShape shape;  // ERROR!

class Circle : public AbstractShape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    // MUST implement pure virtual
    double area() const {
        return 3.14159 * radius * radius;
    }
};
```

### Interface Pattern
```cpp
// Pure interface (all pure virtual)
class IDrawable {
public:
    virtual ~IDrawable() {}
    virtual void draw() const = 0;
    virtual void move(int x, int y) = 0;
};

class ISerializable {
public:
    virtual ~ISerializable() {}
    virtual std::string serialize() const = 0;
};

// Implement multiple interfaces
class Shape : public IDrawable, public ISerializable {
public:
    void draw() const { /* ... */ }
    void move(int x, int y) { /* ... */ }
    std::string serialize() const { /* ... */ }
};
```

### Virtual Table (vtable) - Behind the Scenes
```cpp
/*
Compile time:
┌─────────────────────┐
│  Animal vtable      │
├─────────────────────┤
│ makeSound() ─────→  │ Animal::makeSound()
│ ~Animal()   ─────→  │ Animal::~Animal()
└─────────────────────┘

┌─────────────────────┐
│  Dog vtable         │
├─────────────────────┤
│ makeSound() ─────→  │ Dog::makeSound()     (override!)
│ ~Dog()      ─────→  │ Dog::~Dog()
└─────────────────────┘

Runtime:
Object memory:
┌──────────────┐
│ vptr  ────→  │ Points to Dog vtable
├──────────────┤
│ member data  │
└──────────────┘

Function call:
animal->makeSound()
  → Follow vptr to vtable
  → Find makeSound() entry
  → Call Dog::makeSound()
*/
```

### Shallow vs Deep Copy
```cpp
class Brain {
    std::string* ideas;
public:
    Brain() { ideas = new std::string[100]; }
    
    // Shallow copy (BAD!)
    Brain(const Brain& other) {
        ideas = other.ideas;  // SAME pointer!
    }
    
    // Deep copy (GOOD!)
    Brain(const Brain& other) {
        ideas = new std::string[100];
        for (int i = 0; i < 100; i++)
            ideas[i] = other.ideas[i];
    }
    
    ~Brain() { delete[] ideas; }
};
```

---

## 🔧 Common Patterns

### RAII (Resource Acquisition Is Initialization)
```cpp
class FileHandler {
private:
    std::ifstream file;
public:
    FileHandler(const std::string& filename) {
        file.open(filename.c_str());  // Acquire in constructor
        if (!file.is_open())
            throw std::runtime_error("Can't open file");
    }
    
    ~FileHandler() {
        if (file.is_open())
            file.close();  // Release in destructor
    }
    
    // Prevent copying
private:
    FileHandler(const FileHandler&);
    FileHandler& operator=(const FileHandler&);
};

// Usage:
{
    FileHandler fh("data.txt");
    // Use file...
}  // Automatically closed when fh goes out of scope
```

### Singleton Pattern
```cpp
class Singleton {
private:
    static Singleton* instance;
    
    // Private constructor
    Singleton() {}
    
    // Prevent copying
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
    
public:
    static Singleton* getInstance() {
        if (instance == NULL)
            instance = new Singleton();
        return instance;
    }
};

Singleton* Singleton::instance = NULL;
```

---

## 🐛 Common Mistakes

### ❌ Forgetting Virtual Destructor
```cpp
class Base {
public:
    ~Base() {}  // NOT virtual
};

class Derived : public Base {
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() { delete[] data; }
};

Base* ptr = new Derived();
delete ptr;  // Only ~Base() called, memory leak!
```

### ❌ Self-Assignment
```cpp
MyClass& operator=(const MyClass& other) {
    delete data;                    // Delete first...
    data = new int(*other.data);    // If this == &other, CRASH!
    return *this;
}

// CORRECT:
MyClass& operator=(const MyClass& other) {
    if (this != &other) {  // Check self-assignment
        delete data;
        data = new int(*other.data);
    }
    return *this;
}
```

### ❌ Returning Reference to Local
```cpp
int& getLocal() {
    int x = 10;
    return x;  // DANGLING REFERENCE!
}
```

### ❌ Array Delete
```cpp
int* arr = new int[10];
delete arr;    // WRONG! Memory leak
delete[] arr;  // CORRECT
```

---

## 📚 Compilation & Debugging

### Compile Commands
```bash
# Basic
c++ -Wall -Wextra -Werror -std=c++98 main.cpp -o program

# Multiple files
c++ -Wall -Wextra -Werror -std=c++98 main.cpp class1.cpp class2.cpp -o program

# Debug symbols
c++ -g -Wall -Wextra -Werror -std=c++98 main.cpp -o program

# Optimization
c++ -O2 -Wall -Wextra -Werror -std=c++98 main.cpp -o program
```

### Debugging
```bash
# GDB
gdb ./program
(gdb) break main
(gdb) run
(gdb) step
(gdb) print variable
(gdb) continue
(gdb) quit

# Valgrind
valgrind --leak-check=full --show-leak-kinds=all ./program
```

---

## 💡 Pro Tips

1. **Always use initialization lists** for member variables
2. **Make destructors virtual** in base classes
3. **Use const correctness** everywhere
4. **Prefer references** over pointers when possible
5. **Check self-assignment** in operator=
6. **Delete[] for arrays**, delete for single objects
7. **RAII**: Acquire resources in constructor, release in destructor
8. **Rule of Three**: If you need one of (destructor, copy constructor, copy assignment), you need all three
9. **Don't return references** to local variables
10. **Test with Valgrind** for memory leaks

---

**Created for 42 School CPP Modules** 🚀
