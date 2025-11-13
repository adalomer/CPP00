/* ************************************************************************** */
/*                       CPP00 SYNTAX EXAMPLES & DEEP DIVE                    */
/*                          Practical Code Snippets                           */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <iomanip>

// =============================================================================
// 1. CLASS BASICS - Memory Layout Example
// =============================================================================

class SimpleClass {
private:
    int value;           // 4 bytes
    char letter;         // 1 byte + 3 bytes padding
    double number;       // 8 bytes
    // Total: 16 bytes (with padding)
    
public:
    SimpleClass() : value(0), letter('A'), number(0.0) {
        std::cout << "Constructor called" << std::endl;
    }
    
    ~SimpleClass() {
        std::cout << "Destructor called" << std::endl;
    }
    
    void display() const {
        std::cout << "Value: " << value << ", Letter: " << letter 
                  << ", Number: " << number << std::endl;
    }
};

void testClassMemory() {
    std::cout << "\n=== CLASS MEMORY TEST ===" << std::endl;
    std::cout << "Size of SimpleClass: " << sizeof(SimpleClass) << " bytes" << std::endl;
    
    SimpleClass obj;  // Stack allocation
    // Constructor otomatik çağrılır
    
    SimpleClass* ptr = new SimpleClass();  // Heap allocation
    delete ptr;  // Destructor manuel çağrılır
    
    // Scope bitince obj için destructor otomatik çağrılır
}

// =============================================================================
// 2. THIS POINTER - What Really Happens
// =============================================================================

class ThisExample {
private:
    int value;
    
public:
    ThisExample(int value) {
        // this pointer kullanarak member ve parameter ayırt ediyoruz
        this->value = value;  // this->value = member, value = parameter
    }
    
    // Method chaining için this pointer return
    ThisExample& setValue(int value) {
        this->value = value;
        return *this;  // Current object'i return et
    }
    
    ThisExample& increment() {
        this->value++;
        return *this;
    }
    
    void display() const {
        std::cout << "Value: " << this->value << std::endl;
    }
    
    // this pointer'ın gerçek hali (compiler tarafından eklenen):
    // void display(const ThisExample* this) {
    //     std::cout << "Value: " << this->value << std::endl;
    // }
};

void testThisPointer() {
    std::cout << "\n=== THIS POINTER TEST ===" << std::endl;
    
    ThisExample obj(10);
    
    // Method chaining (this pointer sayesinde):
    obj.setValue(5).increment().increment().display();
    // Output: Value: 7
    
    // Arka planda ne oluyor:
    // obj.setValue(&obj, 5).increment(&obj).increment(&obj).display(&obj);
}

// =============================================================================
// 3. CONSTRUCTOR TYPES & INITIALIZATION
// =============================================================================

class ConstructorExample {
private:
    int x;
    const int y;
    int& ref;
    
public:
    // Default Constructor
    ConstructorExample() : x(0), y(0), ref(x) {
        std::cout << "Default constructor" << std::endl;
    }
    
    // Parameterized Constructor
    ConstructorExample(int val, int& r) : x(val), y(val * 2), ref(r) {
        std::cout << "Parameterized constructor" << std::endl;
    }
    
    // Copy Constructor
    ConstructorExample(const ConstructorExample& other) 
        : x(other.x), y(other.y), ref(other.ref) {
        std::cout << "Copy constructor" << std::endl;
    }
    
    // NEDEN INITIALIZATION LIST?
    // const ve reference members initialization list'te initialize edilmeli
    // Çünkü bunlar construct edilirken set edilmeli, sonra değil
    
    void display() const {
        std::cout << "x: " << x << ", y: " << y << ", ref: " << ref << std::endl;
    }
};

void testConstructors() {
    std::cout << "\n=== CONSTRUCTOR TEST ===" << std::endl;
    
    ConstructorExample obj1;  // Default constructor
    
    int temp = 100;
    ConstructorExample obj2(10, temp);  // Parameterized constructor
    
    ConstructorExample obj3 = obj2;  // Copy constructor
    ConstructorExample obj4(obj2);   // Copy constructor (alternative syntax)
    
    obj3.display();
}

// =============================================================================
// 4. CONST CORRECTNESS
// =============================================================================

class ConstExample {
private:
    int value;
    mutable int cacheHits;  // mutable: const function'da değiştirilebilir
    
public:
    ConstExample(int v) : value(v), cacheHits(0) {}
    
    // const member function: object'i değiştirmez
    int getValue() const {
        cacheHits++;  // mutable olduğu için const function'da değiştirilebilir
        return value;
    }
    
    // non-const member function
    void setValue(int v) {
        value = v;
    }
    
    // const object sadece const member functions çağırabilir
};

void testConstCorrectness() {
    std::cout << "\n=== CONST CORRECTNESS TEST ===" << std::endl;
    
    ConstExample obj1(10);
    obj1.setValue(20);      // ✓ OK
    obj1.getValue();        // ✓ OK
    
    const ConstExample obj2(30);
    // obj2.setValue(40);   // ✗ ERROR: const object, non-const function
    obj2.getValue();        // ✓ OK: const function
}

// =============================================================================
// 5. REFERENCE vs POINTER
// =============================================================================

void referenceVsPointer() {
    std::cout << "\n=== REFERENCE VS POINTER TEST ===" << std::endl;
    
    int x = 10;
    
    // REFERENCE
    int& ref = x;           // Must initialize
    ref = 20;               // x değişir
    std::cout << "x after ref: " << x << std::endl;  // 20
    
    // int& ref2;           // ✗ ERROR: reference must be initialized
    // ref = another;       // ref başka şeye bind olamaz (x'e bound kalır)
    
    // POINTER
    int* ptr = &x;          // Can be NULL
    *ptr = 30;              // x değişir
    std::cout << "x after ptr: " << x << std::endl;  // 30
    
    int y = 40;
    ptr = &y;               // ptr başka yere point edebilir
    
    // NULL pointer
    int* nullPtr = NULL;    // C++98
    if (nullPtr == NULL)
        std::cout << "Null pointer is NULL" << std::endl;
    // int* nullPtr = nullptr; // C++11
    
    // MEMORY VIEW:
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Address stored in ptr: " << ptr << std::endl;
    std::cout << "Address of ptr itself: " << &ptr << std::endl;
}

// =============================================================================
// 6. PASS BY VALUE vs REFERENCE vs POINTER
// =============================================================================

// Pass by value (copy)
void passByValue(int x) {
    x = 100;  // Original değişmez
}

// Pass by reference
void passByReference(int& x) {
    x = 100;  // Original değişir
}

// Pass by pointer
void passByPointer(int* x) {
    *x = 100;  // Original değişir
}

// Pass by const reference (efficient, safe)
void passByConstReference(const std::string& str) {
    // str değiştirilemez
    std::cout << "Length: " << str.length() << std::endl;
    // Copy yok, efficient
}

void testPassingMethods() {
    std::cout << "\n=== PASSING METHODS TEST ===" << std::endl;
    
    int a = 10, b = 10, c = 10;
    
    passByValue(a);
    std::cout << "After pass by value: " << a << std::endl;  // 10 (değişmez)
    
    passByReference(b);
    std::cout << "After pass by reference: " << b << std::endl;  // 100
    
    passByPointer(&c);
    std::cout << "After pass by pointer: " << c << std::endl;  // 100
    
    // Large object için const reference kullan (efficient)
    std::string bigString(10000, 'x');
    passByConstReference(bigString);  // Copy yok!
}

// =============================================================================
// 7. OPERATOR OVERLOADING (<<)
// =============================================================================

class Point {
private:
    int x, y;
    
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    // Friend function: class'ın private members'a erişebilir
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    
    // Arithmetic operator overload
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    // Comparison operator
    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};

// << operator overload (friend function)
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;  // Chain için stream return
}

void testOperatorOverloading() {
    std::cout << "\n=== OPERATOR OVERLOADING TEST ===" << std::endl;
    
    Point p1(10, 20);
    Point p2(5, 15);
    
    std::cout << "p1: " << p1 << std::endl;  // operator<< kullanıldı
    std::cout << "p2: " << p2 << std::endl;
    
    Point p3 = p1 + p2;  // operator+ kullanıldı
    std::cout << "p1 + p2: " << p3 << std::endl;
    
    // Chaining:
    std::cout << "Chain: " << p1 << " " << p2 << " " << p3 << std::endl;
    // operator<<(operator<<(operator<<(cout, p1), p2), p3)
}

// =============================================================================
// 8. STATIC IN DIFFERENT CONTEXTS
// =============================================================================

// Static in file scope (internal linkage)
// static int fileStaticVar = 0;  // Sadece bu dosyada görünür (commented for unused warning)

// static void fileStaticFunc() {  // Sadece bu dosyada görünür
//     std::cout << "File static function" << std::endl;
// }

class StaticExample {
private:
    static int count;  // Static member (class'ın tüm instances'ı paylaşır)
    int instanceId;
    
public:
    StaticExample() {
        instanceId = ++count;  // Her instance için unique ID
    }
    
    // Static member function
    static int getCount() {
        // this pointer yok!
        // return this->count;  // ✗ ERROR
        return count;  // ✓ OK
    }
    
    void display() const {
        std::cout << "Instance " << instanceId << " of " << count << std::endl;
    }
};

// Static member initialization (class dışında!)
int StaticExample::count = 0;

void testStatic() {
    std::cout << "\n=== STATIC TEST ===" << std::endl;
    
    StaticExample obj1;
    StaticExample obj2;
    StaticExample obj3;
    
    obj1.display();  // Instance 1 of 3
    obj2.display();  // Instance 2 of 3
    obj3.display();  // Instance 3 of 3
    
    std::cout << "Total count: " << StaticExample::getCount() << std::endl;
}

// =============================================================================
// 9. STD::STRING INTERNALS
// =============================================================================

void testStringInternals() {
    std::cout << "\n=== STRING INTERNALS TEST ===" << std::endl;
    
    // SSO (Small String Optimization)
    // Küçük string'ler object içinde tutulur (heap allocation yok)
    std::string small = "Hi";  // Likely no heap allocation
    std::string large = "This is a very long string that will definitely need heap allocation";
    
    std::cout << "Small string address: " << (void*)&small << std::endl;
    std::cout << "Small string data address: " << (void*)small.c_str() << std::endl;
    
    std::cout << "Large string address: " << (void*)&large << std::endl;
    std::cout << "Large string data address: " << (void*)large.c_str() << std::endl;
    
    // String operations
    std::string s1 = "Hello";
    std::string s2 = " World";
    
    std::string s3 = s1 + s2;  // operator+ → new string
    s1 += s2;                  // operator+= → modify s1
    
    // Substring
    std::string sub = s3.substr(0, 5);  // "Hello"
    
    // Length vs Capacity
    std::cout << "Length: " << s3.length() << std::endl;
    std::cout << "Capacity: " << s3.capacity() << std::endl;
}

// =============================================================================
// 10. IOMANIP & FORMATTING
// =============================================================================

void testIOManip() {
    std::cout << "\n=== IOMANIP TEST ===" << std::endl;
    
    // setw - width (sadece bir sonraki output için geçerli)
    std::cout << std::setw(10) << "Hello" << std::endl;  // "     Hello"
    std::cout << "World" << std::endl;                   // "World" (normal)
    
    // setfill - fill character
    std::cout << std::setfill('*') << std::setw(10) << "Hi" << std::endl;
    // Output: "********Hi"
    
    // setprecision - floating point precision
    double pi = 3.14159265359;
    std::cout << std::setprecision(3) << pi << std::endl;  // 3.14
    
    // fixed - fixed notation
    std::cout << std::fixed << std::setprecision(2) << pi << std::endl;  // 3.14
    
    // left, right - alignment
    std::cout << std::left << std::setw(10) << "Left" << "|" << std::endl;
    std::cout << std::right << std::setw(10) << "Right" << "|" << std::endl;
    
    // Table example
    std::cout << std::setfill(' ') << std::right;
    std::cout << std::setw(10) << "Name" << "|"
              << std::setw(10) << "Age" << "|"
              << std::setw(10) << "City" << std::endl;
    std::cout << std::setw(10) << "John" << "|"
              << std::setw(10) << "25" << "|"
              << std::setw(10) << "NYC" << std::endl;
}

// =============================================================================
// 11. MEMORY ALLOCATION PATTERNS
// =============================================================================

void testMemoryPatterns() {
    std::cout << "\n=== MEMORY PATTERNS TEST ===" << std::endl;
    
    // 1. Stack allocation
    int stackVar = 10;
    std::cout << "Stack variable address: " << &stackVar << std::endl;
    
    // 2. Heap allocation (single object)
    int* heapVar = new int(20);
    std::cout << "Heap variable address: " << heapVar << std::endl;
    delete heapVar;
    
    // 3. Array allocation
    int* array = new int[10];
    for (int i = 0; i < 10; i++)
        array[i] = i * 10;
    delete[] array;  // Array için delete[]
    
    // 4. Object allocation
    SimpleClass* obj = new SimpleClass();
    delete obj;
    
    // 5. Array of objects
    SimpleClass* objArray = new SimpleClass[3];
    // Constructor 3 kere çağrılır
    delete[] objArray;
    // Destructor 3 kere çağrılır
}

// =============================================================================
// 12. SCOPE & LIFETIME
// =============================================================================

int globalVar = 100;  // Program boyunca yaşar

void scopeExample() {
    std::cout << "\n=== SCOPE & LIFETIME TEST ===" << std::endl;
    
    int outerScope = 10;
    std::cout << "Outer scope: " << outerScope << std::endl;
    
    {
        int innerScope = 20;
        std::cout << "Inner scope: " << innerScope << std::endl;
        std::cout << "Outer from inner: " << outerScope << std::endl;
        
        // Inner scope bitince innerScope destroy edilir
    }
    
    // std::cout << innerScope << std::endl;  // ✗ ERROR: out of scope
    
    // Static local variable (function boyunca yaşar, değeri korunur)
    static int staticLocal = 0;
    staticLocal++;
    std::cout << "Static local: " << staticLocal << std::endl;
}

// =============================================================================
// 13. CIRCULAR BUFFER IMPLEMENTATION
// =============================================================================

template<typename T, int SIZE>
class CircularBuffer {
private:
    T buffer[SIZE];
    int head;
    int tail;
    int count;
    
public:
    CircularBuffer() : head(0), tail(0), count(0) {}
    
    void push(const T& item) {
        buffer[tail] = item;
        tail = (tail + 1) % SIZE;  // Wrap around
        
        if (count < SIZE)
            count++;
        else
            head = (head + 1) % SIZE;  // Overwrite oldest
    }
    
    bool pop(T& item) {
        if (count == 0)
            return false;
        
        item = buffer[head];
        head = (head + 1) % SIZE;
        count--;
        return true;
    }
    
    void display() const {
        std::cout << "Buffer [";
        int idx = head;
        for (int i = 0; i < count; i++) {
            std::cout << buffer[idx];
            if (i < count - 1) std::cout << ", ";
            idx = (idx + 1) % SIZE;
        }
        std::cout << "]" << std::endl;
    }
};

void testCircularBuffer() {
    std::cout << "\n=== CIRCULAR BUFFER TEST ===" << std::endl;
    
    CircularBuffer<int, 5> cb;
    
    for (int i = 0; i < 8; i++) {
        cb.push(i);
        cb.display();
    }
    
    int item;
    while (cb.pop(item)) {
        std::cout << "Popped: " << item << std::endl;
    }
}

// =============================================================================
// MAIN - RUN ALL TESTS
// =============================================================================

int main() {
    std::cout << "╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║      CPP00 SYNTAX EXAMPLES & DEEP DIVE          ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;
    
    testClassMemory();
    testThisPointer();
    testConstructors();
    testConstCorrectness();
    referenceVsPointer();
    testPassingMethods();
    testOperatorOverloading();
    testStatic();
    testStringInternals();
    testIOManip();
    testMemoryPatterns();
    
    // Scope test'i birkaç kez çağır (static variable'ı görmek için)
    scopeExample();
    scopeExample();
    scopeExample();
    
    testCircularBuffer();
    
    std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              ALL TESTS COMPLETED!               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;
    
    return 0;
}

/* 
COMPILE & RUN:
c++ -Wall -Wextra -Werror -std=c++98 cpp00_syntax_examples.cpp -o syntax_test
./syntax_test

MEMORY CHECK:
valgrind --leak-check=full ./syntax_test

ASSEMBLY VIEW:
c++ -S -O0 cpp00_syntax_examples.cpp
cat cpp00_syntax_examples.s
*/
