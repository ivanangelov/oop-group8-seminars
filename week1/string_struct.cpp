#include <iostream>
#include <cstring>

// StringStruct
// Functions manage correctly the memory so that string-related functions are
// memory-safe, e.g. concat never accesses memory outside of the allocated range

struct StringStruct {
    char* data;
    int len;
    int capacity;
};

StringStruct* createString(const char* str) {
    StringStruct* result = new StringStruct;
    result->data = new char[strlen(str) + 1];
    strcpy(result->data, str);
    result->len = strlen(str);
    result->capacity = result->len + 1;
    return result;
}

void destroy(StringStruct* str) {
    delete [] str->data;
}

void myConcat(StringStruct* str1, const StringStruct* str2) {
    if (str1->capacity < str1->len + str2->len) {
        // we need more memory to fit both strings
        int newCapacity = str1->len + str2->len + 1;
        char* newData = new char[newCapacity];
        for (int i = 0; i < str1->len; i++) {
            newData[i] = str1->data[i];
        }
        delete [] str1->data;
        str1->data = newData;
        str1->capacity = newCapacity;
    }
    for (int i = 0; i < str2->len; i++) {
        str1->data[i + str1->len] = str2->data[i];
    }
    str1->data[str1->len + str2->len] = 0;
    str1->len = str1->len + str2->len;
}

void myStrcpy(StringStruct* to, const StringStruct* from) {
    if (to->capacity < from->len + 1) {
        char* newData = new char[from->len + 1];
        delete [] to->data;
        to->data = newData;
        to->capacity = from->len + 1;
    }
    // <= so that the '\0' will be copied as well
    for (int i = 0; i <= from->len; i++) {
        to->data[i] = from->data[i];
    }
    to->len = from->len;
}

int myStrlen(StringStruct* str) {
    return str->len;
}

void print (StringStruct* str) {
    std::cout << str->data;
}

int main () {
    StringStruct* str = createString("Hello ");
    StringStruct* str2 = createString("World!");
    std::cout << "Initial str: ";
    print(str);
    myConcat(str, str2);
    std::cout << std::endl << "After concat: ";
    print(str);
    myStrcpy(str, str2);
    std::cout << std::endl << "After copy: ";
    print(str);
    std::cout << std::endl <<"Final len: " << myStrlen(str) << std::endl;

    // remember to delete allocated memory!
    destroy(str);
    destroy(str2);
    delete str;
    delete str2;
    return 0;
}
