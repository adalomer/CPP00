# 🚀 C++ Öğrenme Rehberi - 42 CPP Modülleri

## 📚 CPP00'da Kullanılan Syntax'lar ve Detaylı Açıklamaları

---

## 1. 🏗️ CLASS (Sınıf) Yapısı

### Temel Syntax:
```cpp
class ClassName {
private:
    // Private members
public:
    // Public members
};
```

### Arka Planda Ne Oluyor?
- **Class**, bir veri yapısıdır (C'deki struct'ın gelişmişi)
- Compiler, class tanımını gördüğünde bir **blueprint** (taslak) oluşturur
- Memory allocation **henüz yapılmaz** (sadece tanım)
- Class tanımı **stack**'te değil, **code segment**'inde tutulur

### Örnek - CPP00'dan:
```cpp
class Contact {
private:
    std::string firstName;  // Bu alanlar sadece class içinden erişilebilir
    std::string lastName;
    
public:
    Contact();              // Constructor
    ~Contact();             // Destructor
    void displayFull();     // Member function
};
```

### Memory Layout:
```
Stack üzerinde Contact nesnesi:
┌─────────────────┐
│  firstName      │ → std::string (heap'te data)
│  lastName       │ → std::string (heap'te data)
│  nickname       │
│  phoneNumber    │
│  darkestSecret  │
└─────────────────┘
```

---

## 2. 🎯 THIS Pointer

### Syntax:
```cpp
this->memberVariable
```

### Arka Planda Ne Oluyor?
- `this` bir **hidden parameter**'dır (gizli parametre)
- Her member function çağrısında **otomatik olarak** iletilir
- Object'in **memory adresini** tutar (`Contact* this`)
- Compiler tarafından otomatik eklenir

### Gerçek Hali:
```cpp
// Yazdığımız:
void Contact::setContact(std::string fn) {
    this->firstName = fn;
}

// Compiler'ın gördüğü:
void Contact::setContact(Contact* this, std::string fn) {
    this->firstName = fn;
}
```

### Memory Gösterimi:
```
Stack:
┌──────────────┐
│ contact1     │ → 0x1000 adresinde
└──────────────┘

contact1.setContact("John");
// Aslında: setContact(&contact1, "John")
// this = 0x1000
```

---

## 3. 🏁 Constructor & Destructor

### Syntax:
```cpp
class MyClass {
public:
    MyClass();   // Constructor
    ~MyClass();  // Destructor
};
```

### Constructor - Ne Zaman Çağrılır?
```cpp
Contact c1;              // Stack'te → Constructor otomatik çağrılır
Contact* c2 = new Contact(); // Heap'te → Constructor çağrılır
```

### Arka Planda:
1. **Memory allocate edilir** (stack veya heap)
2. **Constructor çağrılır**
3. Member değişkenler **initialize** edilir

### Destructor - Ne Zaman Çağrılır?
```cpp
{
    Contact c1;  // Constructor
}                // Scope bitince Destructor otomatik çağrılır

Contact* c2 = new Contact();
delete c2;       // Manuel destructor çağrısı
```

### Memory Lifecycle:
```
Stack Allocation:
┌──────────────────────────────┐
│ Scope başlangıcı             │
│   → Memory allocate          │
│   → Constructor çağrılır     │
│                              │
│ Scope sonu                   │
│   → Destructor çağrılır      │
│   → Memory deallocate        │
└──────────────────────────────┘
```

---

## 4. 📦 std::string

### C String vs std::string:
```cpp
// C Style:
char str[100];
strcpy(str, "Hello");
strcat(str, " World");

// C++ Style:
std::string str = "Hello";
str += " World";
```

### Arka Planda std::string:
```cpp
class string {
private:
    char* data;      // Heap'te data
    size_t length;   // Uzunluk
    size_t capacity; // Kapasite
    
public:
    string(const char* str);
    ~string();
    // ...
};
```

### Memory Layout:
```
Stack (string object):
┌─────────────┐
│ data*       │ ──→ Heap: ['H','e','l','l','o','\0']
│ length: 5   │
│ capacity: 15│
└─────────────┘
```

### Neden std::string Kullanmalıyız?
✅ **Automatic memory management** (destructor deallocate eder)
✅ **Buffer overflow yok**
✅ **Dynamic resizing**
✅ **RAII (Resource Acquisition Is Initialization)** prensibi

---

## 5. 🎨 std::cout & std::endl

### Syntax:
```cpp
std::cout << "Hello" << std::endl;
```

### Arka Planda:
```cpp
// << operator'ü overload edilmiş:
std::ostream& operator<<(std::ostream& os, const char* str);

// Gerçekte:
operator<<(operator<<(std::cout, "Hello"), std::endl);
```

### std::endl vs '\n':
```cpp
std::cout << "Line1" << std::endl;  // Buffer'ı flush eder
std::cout << "Line2" << '\n';       // Sadece newline ekler
```

### Buffer Mekanizması:
```
Program → Output Buffer → Terminal
          └──────┬──────┘
            std::endl
            flush eder
```

---

## 6. 🔄 std::setw (iomanip)

### Syntax:
```cpp
#include <iomanip>
std::cout << std::setw(10) << "Hello";
```

### Arka Planda Ne Oluyor?
```cpp
// setw() bir manipulator'dır:
std::ostream& setw(int n) {
    // Stream'in width field'ını set eder
    stream.width(n);
    return stream;
}
```

### Çalışma Prensibi:
```cpp
std::cout << std::setw(10) << "Hi";
// Output: "        Hi" (8 space + 2 char)

// Sadece bir sonraki output için geçerli!
std::cout << std::setw(10) << "Hi" << "World";
//          └─────────────┘     └──────┘
//           10 char wide      normal width
```

### Memory'de:
```
Stream object'i:
┌──────────────┐
│ width: 10    │ ← setw() bunu değiştirir
│ precision: 6 │
│ flags: ...   │
└──────────────┘
```

---

## 7. 🔄 Operator Overloading (<<)

### std::cout << nasıl çalışır?

```cpp
// << operator'ü:
std::ostream& operator<<(std::ostream& os, const std::string& str);

// Kullanım:
std::cout << "Hello";
// Aslında:
operator<<(std::cout, "Hello");
```

### Chain (Zincirleme) Nasıl Çalışır?
```cpp
std::cout << "A" << "B" << "C";

// Adım adım:
1. operator<<(std::cout, "A")  → returns std::cout
2. operator<<(std::cout, "B")  → returns std::cout
3. operator<<(std::cout, "C")  → returns std::cout
```

---

## 8. 📝 std::getline

### Syntax:
```cpp
std::string input;
std::getline(std::cin, input);
```

### cin >> vs getline():
```cpp
// cin >> (whitespace'te durur):
std::string name;
std::cin >> name;  // "John Doe" → sadece "John" alır

// getline (newline'da durur):
std::getline(std::cin, name);  // "John Doe" → tamamını alır
```

### Arka Planda:
```cpp
// getline internal implementation (simplified):
std::istream& getline(std::istream& is, std::string& str) {
    str.clear();
    char c;
    while (is.get(c) && c != '\n') {
        str += c;
    }
    return is;
}
```

### Input Buffer:
```
Keyboard → Input Buffer → Program
           ['J','o','h','n','\n']
            └──getline reads──┘
```

---

## 9. 🔢 Array vs Circular Buffer

### CPP00'da Kullanımımız:
```cpp
class PhoneBook {
private:
    Contact contacts[8];  // Fixed size array
    int contactCount;     // Mevcut contact sayısı
    int oldestIndex;      // Circular buffer için index
};
```

### Circular Buffer Logic:
```cpp
void addContact() {
    contacts[oldestIndex] = newContact;
    oldestIndex = (oldestIndex + 1) % 8;  // 0,1,2,3,4,5,6,7,0,1,2...
}
```

### Memory Visual:
```
contacts array (size 8):
┌───┬───┬───┬───┬───┬───┬───┬───┐
│ 0 │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │
└───┴───┴───┴───┴───┴───┴───┴───┘
  ↑
  oldestIndex

9. contact eklendiğinde:
oldestIndex = (8) % 8 = 0  → İlk eleman üzerine yazar
```

---

## 10. 🎭 const Keyword

### Member Function'da const:
```cpp
class Contact {
public:
    std::string getFirstName() const;  // Bu function object'i değiştirmez
};
```

### Arka Planda:
```cpp
// const keyword:
std::string Contact::getFirstName() const {
    // this pointer: const Contact* this
    // this->firstName = "X";  ← COMPILER ERROR!
    return this->firstName;  // ✓ OK (read-only)
}
```

### const Object'ler:
```cpp
const Contact c;
c.getFirstName();   // ✓ OK (const function)
c.setContact(...);  // ✗ ERROR (non-const function)
```

---

## 11. 🔍 isdigit() Function

### Syntax:
```cpp
#include <cctype>
if (isdigit(ch)) { /* ... */ }
```

### Arka Planda:
```cpp
// ASCII tablosunu kullanır:
int isdigit(int ch) {
    return (ch >= '0' && ch <= '9');
}
```

### ASCII Değerler:
```
'0' = 48
'1' = 49
...
'9' = 57

isdigit('5')  → 48 <= 53 <= 57 → true
isdigit('a')  → 48 <= 97 <= 57 → false
```

---

## 12. 🎨 ANSI Color Codes

### Nasıl Çalışır?
```cpp
#define RED "\033[31m"
std::cout << RED << "Error!" << RESET;
```

### Terminal Escape Sequences:
```
\033 = ESC character (27 in decimal)
[31m = Red color code

Terminal emulator, bu kod'u gördüğünde:
→ Text color'ı kırmızı yapar
```

### Color Code Breakdown:
```
\033[1;31m
  ↓   ↓  ↓
  |   |  └─ Color (31 = Red)
  |   └──── Style (1 = Bold)
  └──────── ESC sequence starter
```

---

## 13. 🔄 Reference (&) vs Pointer (*)

### Reference:
```cpp
void func(std::string& str) {  // Reference
    str += "!";  // Original değişir
}
```

### Pointer:
```cpp
void func(std::string* str) {  // Pointer
    *str += "!";  // Original değişir
}
```

### Farkları:
```cpp
// Reference:
std::string s = "Hello";
std::string& ref = s;  // Must initialize
ref = "World";         // s değişir
// ref = another;      // ref başka şeye point edemez

// Pointer:
std::string* ptr = &s;  // Can be NULL
*ptr = "World";         // s değişir
ptr = &another;         // ptr başka yere point edebilir
```

### Memory'de:
```
Stack:
┌──────────┐
│ s        │ → "Hello" (heap)
└──────────┘
     ↑
     │
┌──────────┐
│ ref      │ → Same address (alias)
└──────────┘

┌──────────┐
│ ptr      │ → Stores address of s
└──────────┘
```

---

## 14. 🎯 Static Keyword (Function Scope)

### CPP00'daki Kullanım:
```cpp
static std::string getInput(const std::string& prompt) {
    // ...
}
```

### Ne Anlama Geliyor?
- Function **sadece bu dosyada** (translation unit) görünür
- **Internal linkage** (external linkage değil)
- Başka .cpp dosyasından erişilemez

### Neden Kullanırız?
```cpp
// Phonebook.cpp:
static std::string getInput(...) {  // Bu dosyaya özel
    // ...
}

// Contact.cpp:
static std::string getInput(...) {  // Başka implementation
    // Conflict yok!
}
```

---

## 15. 🔄 Member Initialization List

### Syntax:
```cpp
PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {}
```

### Normal Initialization vs Initialization List:

```cpp
// Method 1: Constructor body
PhoneBook::PhoneBook() {
    contactCount = 0;     // Assignment (not initialization)
    oldestIndex = 0;
}

// Method 2: Initialization list
PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {
    // Already initialized!
}
```

### Arka Planda Ne Fark Var?

**Method 1 (Assignment):**
```
1. Memory allocate
2. Default constructor çağrılır (contactCount = garbage)
3. Constructor body'de assignment yapılır
```

**Method 2 (Initialization List):**
```
1. Memory allocate
2. Directly initialize edilir (daha efficient)
```

### Zorunlu Kullanım Durumları:
```cpp
class MyClass {
private:
    const int value;      // const → MUST use init list
    int& ref;            // reference → MUST use init list
    
public:
    MyClass(int v, int& r) : value(v), ref(r) {}
    // Constructor body'de yapılamazdı!
};
```

---

## 16. 🔍 Scope Resolution Operator (::)

### Kullanım Yerleri:

```cpp
// 1. Class member tanımı:
void Contact::displayFull() { }
//   ↑
//   Class::Function

// 2. Namespace:
std::cout
// ↑
// namespace::identifier

// 3. Global scope:
::globalVariable
// ↑
// Global scope operator
```

### Arka Planda:
```cpp
// Header (.hpp):
class Contact {
    void displayFull();  // Declaration
};

// Source (.cpp):
void Contact::displayFull() {  // Definition
    // Compiler: "Bu displayFull, Contact class'ının member'ı"
}
```

---

# 🎯 42 CPP MODÜLLERİ ÇALIŞMA PLANI

---

## 📅 CPP00 - CPP04 Çalışma Çizelgesi (8 Haftalık Plan)

### 🗓️ HAFTA 1-2: CPP00 (Ad-Hoc Polymorphism, Namespace, Class)

#### Gün 1-2: Temel Syntax
- [ ] Namespace kavramı
- [ ] Class vs Struct farkı
- [ ] Member functions
- [ ] Constructor/Destructor
- [ ] this pointer

#### Gün 3-4: Memory Management
- [ ] Stack vs Heap
- [ ] new/delete operatörleri
- [ ] Memory leaks nasıl tespit edilir
- [ ] Valgrind kullanımı

#### Gün 5-7: Pratik
- [ ] ex00: megaphone (string manipulation)
- [ ] ex01: PhoneBook (class, array, input handling)
- [ ] ex02: Account (class, static members)

#### 📚 Öğrenilecek Konular:
```cpp
// 1. Namespace
namespace MyNamespace {
    void func();
}

// 2. Class basics
class MyClass {
private:
    int value;
public:
    MyClass();
    ~MyClass();
    void setValue(int v);
    int getValue() const;
};

// 3. stdio streams
std::cin, std::cout, std::cerr
```

---

### 🗓️ HAFTA 3: CPP01 (Memory Allocation, References, Pointers)

#### Gün 1-2: Reference & Pointer
- [ ] Reference vs Pointer farkları
- [ ] When to use which?
- [ ] Pass by value/reference/pointer
- [ ] Return by reference

#### Gün 3-4: Dynamic Memory
- [ ] new/delete arrays
- [ ] Memory leaks
- [ ] RAII prensibi

#### Gün 5-7: Pratik
- [ ] ex00: Zombie (stack vs heap)
- [ ] ex01: Zombie horde (array allocation)
- [ ] ex02: String references
- [ ] ex03: Weapon class
- [ ] ex04: File manipulation (sed replacement)
- [ ] ex05: Harl (switch to function pointers)

#### 📚 Öğrenilecek Konular:
```cpp
// 1. Reference
void swap(int& a, int& b);

// 2. Pointer to member function
class MyClass {
    void (MyClass::*funcPtr)();
};

// 3. File streams
std::ifstream, std::ofstream
```

---

### 🗓️ HAFTA 4-5: CPP02 (Ad-Hoc Polymorphism, Operator Overload, Orthodox Canonical Form)

#### Gün 1-3: Operator Overloading
- [ ] Arithmetic operators (+, -, *, /)
- [ ] Comparison operators (==, !=, <, >)
- [ ] Assignment operator (=)
- [ ] Stream operators (<<, >>)
- [ ] Increment/Decrement (++, --)

#### Gün 4-5: Orthodox Canonical Form (OCF)
- [ ] Default constructor
- [ ] Copy constructor
- [ ] Copy assignment operator
- [ ] Destructor

#### Gün 6-7: Fixed Point
- [ ] Fixed point numbers nedir?
- [ ] Floating point vs Fixed point
- [ ] Bit manipulation

#### Gün 8-10: Pratik
- [ ] ex00: Orthodox Canonical Form
- [ ] ex01: Fixed point class
- [ ] ex02: Operator overloading (comparison, arithmetic)
- [ ] ex03: BSP (Binary Space Partitioning)

#### 📚 Öğrenilecek Konular:
```cpp
// 1. Orthodox Canonical Form
class MyClass {
public:
    MyClass();                          // Default constructor
    MyClass(const MyClass& other);      // Copy constructor
    MyClass& operator=(const MyClass& other);  // Copy assignment
    ~MyClass();                         // Destructor
};

// 2. Operator Overloading
class Fixed {
    Fixed operator+(const Fixed& other);
    bool operator>(const Fixed& other);
    friend std::ostream& operator<<(std::ostream& os, const Fixed& f);
};

// 3. Fixed Point
int fixedValue = floatValue * (1 << fractionalBits);
```

---

### 🗓️ HAFTA 6: CPP03 (Inheritance)

#### Gün 1-3: Inheritance Basics
- [ ] Base class & Derived class
- [ ] protected keyword
- [ ] Constructor/Destructor order
- [ ] Member access (public, protected, private inheritance)

#### Gün 4-5: Diamond Problem
- [ ] Multiple inheritance
- [ ] Virtual inheritance
- [ ] Diamond problem solution

#### Gün 6-7: Pratik
- [ ] ex00: ClapTrap
- [ ] ex01: ScavTrap (single inheritance)
- [ ] ex02: FragTrap (multiple inheritance)
- [ ] ex03: DiamondTrap (diamond problem)

#### 📚 Öğrenilecek Konular:
```cpp
// 1. Basic Inheritance
class Base {
protected:
    int value;
public:
    Base();
    virtual ~Base();
};

class Derived : public Base {
public:
    Derived();
    ~Derived();
};

// 2. Virtual Inheritance (Diamond Problem)
class Base { };
class Left : virtual public Base { };
class Right : virtual public Base { };
class Diamond : public Left, public Right { };
```

---

### 🗓️ HAFTA 7-8: CPP04 (Polymorphism, Abstract Classes, Interfaces)

#### Gün 1-3: Virtual Functions & Polymorphism
- [ ] Virtual functions
- [ ] Pure virtual functions
- [ ] Abstract classes
- [ ] Virtual destructor
- [ ] vtable nasıl çalışır?

#### Gün 4-5: Interfaces
- [ ] Interface design
- [ ] Pure virtual functions
- [ ] Multiple interface implementation

#### Gün 6-7: Deep Copy vs Shallow Copy
- [ ] Copy constructor deep copy
- [ ] Assignment operator deep copy
- [ ] Polymorphic copy

#### Gün 8-14: Pratik
- [ ] ex00: Animal class (virtual functions)
- [ ] ex01: Brain class (deep copy)
- [ ] ex02: Abstract Animal
- [ ] ex03: Interfaces (ICharacter, IMateriaSource)

#### 📚 Öğrenilecek Konular:
```cpp
// 1. Virtual Function
class Animal {
public:
    virtual void makeSound() = 0;  // Pure virtual
    virtual ~Animal();
};

// 2. Polymorphism
Animal* animal = new Dog();
animal->makeSound();  // Dog's sound (runtime polymorphism)

// 3. Abstract Class
class AbstractClass {
public:
    virtual void pureVirtual() = 0;  // Cannot instantiate
};

// 4. Interface
class IInterface {
public:
    virtual ~IInterface() {}
    virtual void method() = 0;
};

// 5. vtable (Virtual Function Table)
/*
Compile time'da her class için bir vtable oluşturulur:

Animal vtable:
┌──────────────────┐
│ makeSound()  →   │ → Animal::makeSound()
│ destructor   →   │ → Animal::~Animal()
└──────────────────┘

Dog vtable:
┌──────────────────┐
│ makeSound()  →   │ → Dog::makeSound()  (override)
│ destructor   →   │ → Dog::~Dog()
└──────────────────┘

Object memory:
┌──────────────┐
│ vptr →       │ → Points to Dog vtable
│ data members │
└──────────────┘
*/
```

---

# 📊 GÜNLÜK ÇALIŞMA RUTINI

## 🌅 Sabah (2-3 saat)
1. **Teori** (45 min)
   - Yeni bir konsept öğren
   - Notlar al
   - Örnekleri incele

2. **Mini Practice** (45 min)
   - Küçük kod snippets yaz
   - Konsepti test et
   - Compiler hataları ile oyna

3. **Break** (15 min)

4. **Deep Dive** (45 min)
   - Arka plan detaylarını araştır
   - Memory layout'u çiz
   - Assembly'ye bak (optional)

## 🌆 Öğleden Sonra (3-4 saat)
1. **Exercise** (2-3 saat)
   - 42 exercise'ı çöz
   - Önce kağıt üzerinde plan yap
   - Sonra kod yaz

2. **Break** (30 min)

3. **Debug & Test** (1 saat)
   - Valgrind ile test et
   - Memory leaks kontrol
   - Edge cases test et

## 🌙 Akşam (1-2 saat)
1. **Review** (30 min)
   - Gün boyunca öğrendiklerini gözden geçir
   - Notlarını düzenle

2. **Code Reading** (30 min)
   - Başkalarının C++ kodunu oku
   - GitHub'da projeler incele
   - CPP reference documentation oku

3. **Extra Practice** (optional, 30 min)
   - LeetCode/HackerRank C++ problems
   - Kendi mini projeler

---

# 🛠️ KULLANILACAK ARAÇLAR

## Compiler & Debugger
```bash
# Compile
c++ -Wall -Wextra -Werror -std=c++98 file.cpp

# Debug symbols ile compile
c++ -g -Wall -Wextra -Werror -std=c++98 file.cpp

# GDB debug
gdb ./a.out

# Valgrind memory check
valgrind --leak-check=full ./a.out
```

## Useful Commands
```bash
# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./program

# Generate assembly (arka planı görmek için)
c++ -S -O0 file.cpp

# Preprocessor output görmek için
c++ -E file.cpp

# Object file symbols görmek için
nm -C file.o

# Vtable görmek için
c++ -fdump-class-hierarchy file.cpp
```

---

# 📖 KAYNAKLAR

## Websites
- [cplusplus.com](http://www.cplusplus.com/) - Reference
- [cppreference.com](https://en.cppreference.com/) - Detailed reference
- [learncpp.com](https://www.learncpp.com/) - Tutorial
- [isocpp.org](https://isocpp.org/) - Official C++ site

## Books (Önerilen)
1. **"C++ Primer" (5th Edition)** - Stanley B. Lippman
2. **"Effective C++" (3rd Edition)** - Scott Meyers
3. **"The C++ Programming Language" (4th Edition)** - Bjarne Stroustrup

## Video Tutorials
- **TheCherno C++ Series** (YouTube)
- **Bo Qian C++ Tutorials** (YouTube)

---

# ⚠️ COMMON PITFALLS (Dikkat Edilecekler)

## 1. Memory Management
```cpp
// ❌ YANLIŞ:
class MyClass {
    int* ptr;
public:
    MyClass() { ptr = new int(10); }
    // Destructor yok → Memory leak!
};

// ✅ DOĞRU:
class MyClass {
    int* ptr;
public:
    MyClass() { ptr = new int(10); }
    ~MyClass() { delete ptr; }  // Clean up
};
```

## 2. Copy Constructor & Assignment
```cpp
// ❌ YANLIŞ (Shallow Copy):
class MyClass {
    int* ptr;
public:
    MyClass(const MyClass& other) {
        ptr = other.ptr;  // Same pointer!
    }
};

// ✅ DOĞRU (Deep Copy):
class MyClass {
    int* ptr;
public:
    MyClass(const MyClass& other) {
        ptr = new int(*other.ptr);  // New memory
    }
};
```

## 3. Virtual Destructor
```cpp
// ❌ YANLIŞ:
class Base {
public:
    ~Base() {}  // Non-virtual
};

class Derived : public Base {
    int* ptr;
public:
    ~Derived() { delete ptr; }
};

Base* obj = new Derived();
delete obj;  // Only Base destructor called → Memory leak!

// ✅ DOĞRU:
class Base {
public:
    virtual ~Base() {}  // Virtual destructor
};
```

## 4. Reference Return
```cpp
// ❌ YANLIŞ:
int& getLocal() {
    int x = 10;
    return x;  // Dangling reference!
}

// ✅ DOĞRU:
int& getMember() {
    return this->memberVar;  // OK (member outlives function)
}
```

---

# 🎯 HER MODÜL İÇİN CHECKPOINT

## CPP00 Checklist
- [ ] Class yazabiliyorum
- [ ] Constructor/Destructor anlıyorum
- [ ] this pointer kullanabiliyorum
- [ ] std::string ile çalışabiliyorum
- [ ] Input/Output stream kullanabiliyorum

## CPP01 Checklist
- [ ] Reference vs Pointer farkını biliyorum
- [ ] new/delete kullanabiliyorum
- [ ] Memory leaks tespit edebiliyorum
- [ ] File stream kullanabiliyorum
- [ ] Function pointer kullanabiliyorum

## CPP02 Checklist
- [ ] Orthodox Canonical Form yazabiliyorum
- [ ] Operator overload yapabiliyorum
- [ ] Copy constructor/assignment farkını anlıyorum
- [ ] Shallow vs Deep copy biliyorum
- [ ] Friend functions kullanabiliyorum

## CPP03 Checklist
- [ ] Inheritance yapabiliyorum
- [ ] protected/public/private inheritance farkını biliyorum
- [ ] Constructor/Destructor order anlıyorum
- [ ] Diamond problem çözebiliyorum
- [ ] Virtual inheritance kullanabiliyorum

## CPP04 Checklist
- [ ] Virtual function yazabiliyorum
- [ ] Abstract class oluşturabiliyorum
- [ ] Interface design yapabiliyorum
- [ ] Polymorphism anlıyorum
- [ ] vtable nasıl çalışır biliyorum
- [ ] Virtual destructor önemini anlıyorum

---

# 🚀 MOTİVASYON & İPUÇLARI

## Günlük Hedefler
- ✅ Her gün **en az 1 exercise** bitir
- ✅ Anlamadığın bir şeyi **kağıda çiz**
- ✅ **Memory layout'ları** görselleştir
- ✅ Valgrind'den **0 errors 0 leaks** al

## Haftalık Review
- 📝 Hafta sonunda **özet çıkar**
- 🎯 **Weak points** belirle
- 🔄 Gerekirse **konuyu tekrar et**
- 💪 Bir önceki hafta ile **karşılaştır**

## Motivasyon
> "C++ öğrenmek maraton gibidir, sprint değil. Sabırlı ol!"

- 🎯 Her exercise bir **başarı**
- 💡 Her hata bir **öğrenme fırsatı**
- 🚀 Her modül seni bir adım daha **ileri götürüyor**

---

# 📌 ÖZET

CPP00-CPP04 modülleri, C++'ın temellerini ve Object Oriented Programming'in core concepts'lerini öğretir:

1. **CPP00**: OOP basics, classes, namespaces
2. **CPP01**: Memory, pointers, references
3. **CPP02**: Operator overloading, canonical form
4. **CPP03**: Inheritance
5. **CPP04**: Polymorphism, abstract classes, interfaces

Bu rehberi takip edersen, **8 hafta** içinde solid bir C++ temeline sahip olacaksın! 💪

---

**Son Tavsiye**: 
> "Kodu çalıştırmadan önce ne yapacağını tahmin et. Sonra çalıştır ve karşılaştır. Bu şekilde öğrenme en hızlı gerçekleşir!"

Good luck! 🍀
