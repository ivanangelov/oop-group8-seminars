#include <iostream>
#include <cstring>

/*
 * StringClass
 * Manages correctly the memory so that string-related functions are
 * memory-safe, e.g. concat never accesses memory outside of the allocated range
 * The same as the StringStruct example, but here we join together the data
 * (string, length, capacity) and the operation we want to invoke on it
 * (creation, concatenation, copying, finding the length, destroying)
 * All the functions from the StringStruct example are the same, except the first argument:
 * We know that the first string is now the object we are applying the operation on.
 * It is not available as a function parameter - instead it is accessible from the body
 * of the function using the keyword "this".
 */
class StringClass {
    char* data;
    int len;
    int capacity;
public:
    // constructor == create
    StringClass(const char* str) {
        this->data = new char[strlen(str) + 1];
        strcpy(this->data, str);
        this->len = strlen(str);
        this->capacity = this->len + 1;
        // return this - not necessary anymore, it is done by default
    }

    // destructor == destroy
    ~StringClass() {
        delete [] this->data;
    }

    void myConcat(const StringClass* str2) {
        if (this->capacity < this->len + str2->len) {
            // we need more memory to fit both strings
            int newCapacity = this->len + str2->len + 1;
            char* newData = new char[newCapacity];
            for (int i = 0; i < this->len; i++) {
                newData[i] = this->data[i];
            }
            delete [] this->data;
            this->data = newData;
            this->capacity = newCapacity;
        }
        for (int i = 0; i < str2->len; i++) {
            this->data[i + this->len] = str2->data[i];
        }
        this->data[this->len + str2->len] = 0;
        this->len = this->len + str2->len;
    }

    void myStrcpy(const StringClass* from) {
        if (this->capacity < from->len + 1) {
            char* newData = new char[from->len + 1];
            delete [] this->data;
            this->data = newData;
            this->capacity = from->len + 1;
        }
        // <= so that the '\0' will be copied as well
        for (int i = 0; i <= from->len; i++) {
            this->data[i] = from->data[i];
        }
        this->len = from->len;
    }

    int myStrlen() {
        return this->len;
    }

    void print () {
        std::cout << this->data;
    }
};

int main () {
    StringClass* str = new StringClass("Hello ");
    StringClass* str2 = new StringClass("World!");
    std::cout << "Initial str: ";
    str->print();
    str->myConcat(str2);
    std::cout << std::endl << "After concat: ";
    str->print();
    str->myStrcpy(str2);
    std::cout << std::endl << "After copy: ";
    str->print();
    std::cout << std::endl <<"Final len: " << str->myStrlen() << std::endl;

    // remember to delete allocated memory!
    // the destructor is automatically called
    // when we delete the object
    delete str;
    delete str2;
    return 0;
}
