#include <iostream>

void basicHeapAllocationExample () {
    double *doubleOnHeap = new double(5.5);
    std::cout << "Value stored on the heap: " << *doubleOnHeap << std::endl;
    // delete it manually when it is not needed anymore
    delete doubleOnHeap;
    // using it after delete leads to undefined behavior!
    std::cout << "Accessing deleted memory: " << *doubleOnHeap << std::endl;
}

void addressSpaceExample () {
    // Note that the addresses of variables allocated on the stack
    // are close to each other, but the addresses of things allocated
    // on the heap are somewhere else
    // all of these are allocated on the stack
    int onStack = 5;
    int *pStack = &onStack;
    int anotherOnStack = 6;
    int *pStack2 = &anotherOnStack;

    // new allocates blocks of memory in the heap
    int *pHeap = new int(5);
    int *pHeap2 = new int(6);

    std::cout << "Addresses on stack: " << std::endl;
    std::cout << "int onStack: " << &onStack <<
        " (value: " << onStack << ")" << std::endl;
    std::cout << "int *pStack: " << &pStack <<
        " (value: " << pStack << ")" << std::endl;
    std::cout << "int anotherOnStack: " << &anotherOnStack <<
        " (value: " << anotherOnStack << ")" << std::endl;
    std::cout << "int *pStack2: " << &pStack2 <<
        " (value: " << pStack2 << ")" << std::endl;
    // note that the pointers to the pointers are on the stack
    // but the values are in a different part of the memory
    std::cout << "int *pHeap: " << &pHeap <<
        " (value: " << pHeap << ")" << std::endl;
    std::cout << "int *pHeap2: " << &pHeap2 <<
        " (value: " << pHeap2 << ")" << std::endl;

    std::cout << std::endl;
    std::cout << "Values in the heap: " << std::endl;
    std::cout << "value at " << pHeap << ": " << *pHeap << std::endl;
    std::cout << "value at " << pHeap2 << ": " << *pHeap2 << std::endl;

    // Must have a delete for each new!
    delete pHeap;
    delete pHeap2;
}

/**
 * Bad attempt to create an array and fill it with the numbers from 0 to 99
 * Do not try to return pointers or references to local variables!
 * They are allocated on the stack and the memory used by arr will be released
 * at the end of this function.
 */
int* badArrayAlloc () {
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    return arr;
}

/**
 * The correct way to return an array with a dynamic size and populated with some data.
 * new allocates the data on the heap and the programmer is responsible to release it
 * when it is not needed anymore.
 */
int* goodArrayAlloc (int n) {
    // note the square brackets []
    int* arr = new int[n];
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    return arr;
}

void dynamicAllocationExample() {
    int *badArr = badArrayAlloc();
    int *goodArr = goodArrayAlloc(100);
    // undefined behavior!
    std::cout << "In bad array: " << badArr[3] << std::endl;
    // normal behavior - goodArr is allocated on the heap
    std::cout << "In good array: " << goodArr[3] << std::endl;

    // delete arrays allocated on the heap!
    delete [] goodArr;
}

void displayExampleStart (int exampleId) {
    std::cout << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "Start example " << exampleId << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << std::endl;
}

int main()
{
    displayExampleStart(0);
    basicHeapAllocationExample();
    displayExampleStart(1);
    addressSpaceExample();
    displayExampleStart(2);
    dynamicAllocationExample();
    return 0;
}
