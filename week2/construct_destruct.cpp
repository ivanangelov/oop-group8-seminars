#include <iostream>
#include <stdlib.h>
#include <cstring>

class String {
    char* data;
    int len;
    int capacity;
public:
    // default constructor
    String();
    // constructor with parameters
    String(const char*);
    // constructor from number in a specified base
    // if the base argument is skipped, it will be 10 by default
    String(int number, int base=10);
    // copy constructor
    String(const String&);
    // destructor
    ~String();
};

String::String() {
    // default capacity
    this->capacity = 10;
    this->data = new char[this->capacity];
    // empty string by default
    this->data[0] = 0;
    this->len = 0;
    std::cout << "Default constructed string" << std::endl;
}

String::String(const char* data) {
    int len = strlen(data);
    this->capacity = len + 1;
    this->len = len;
    this->data = new char[this->capacity];
    // copy the data
    strcpy(this->data, data);
    std::cout << "Constructed string from char*: " << this->data << std::endl;
}

String::String(int number, int base) {
    // first calculate number of digits
    // so that we can allocate enough memory
    int numDigits = 0, temp = number;
    do {
        numDigits++;
        temp /= base;
    } while (temp != 0);
    this->capacity = numDigits + 1;
    this->data = new char[this->capacity];
    // a standard function to convert a number to a char*
    itoa(number, this->data, base);
    this->len = numDigits;
    std::cout << "Constructed string from number: " << this->data << std::endl;
}

String::String(const String& other) {
    this->capacity = other.capacity;
    this->len = other.len;
    // Do NOT write this->data = other.data
    // It will create shared memory - when one string is changed, the other will be changed too.
    // We want the strings to be independent, so allocate new memory and copy all the values
    this->data = new char[this->capacity];
    strcpy(this->data, other.data);
    std::cout << "Constructed string from other string: " << this->data << std::endl;
}

String::~String() {
    std::cout << "Destructing string " << this->data << std::endl;
    delete [] this->data;
}

void testConstructors () {
    // default construct
    // on the heap
    String *s1 = new String();
    // on the stack
    String s2;
    // construct with parameters
    // on the heap
    String *s3 = new String("Hello"), *s4 = new String(255, 16);
    // on the stack
    String s5 = "World", s6 = 1234;
    // construct from another string
    String *s7 = new String(s6);
    String s8 = *s3;
    std::cout << "End creating objects" << std::endl << std::endl;
    // everything allocated on the heap should be manually deleted
    std::cout << "Deleting objects on the heap" << std::endl;
    delete s7;
    delete s4;
    delete s3;
    delete s1;
    std::cout << std::endl << "Now deleting automatically objects allocated on the stack: "<< std::endl;
}

void fByRef (String& t) {
    std::cout << "In f" << std::endl;
    std::cout << "Exiting f" << std::endl;
}

void fByVal (String t) {
    std::cout << "In f" << std::endl;
    std::cout << "Exiting f" << std::endl;
}

void testPassByValueAndRef() {
    String testString = "Test";
    std::cout << "Before fByVal" << std::endl;
    // testString will now be copied
    // and the copied value will be used in fByVal
    fByVal(testString);
    // the copy of testString is destroyed upon exiting fByVal
    std::cout << "After fByVal" << std::endl;
    std::cout << "Before fByRef" << std::endl;
    // no copying when calling fByRef
    fByRef(testString);
    std::cout << "After fByRef" << std::endl;
}

void displayExampleStart (const char* exampleId) {
    std::cout << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Start example " << exampleId << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << std::endl;
}

int main()
{
    displayExampleStart("Test Constructors and Destructors");
    testConstructors();
    displayExampleStart("Test function calling");
    testPassByValueAndRef();
    return 0;
}
