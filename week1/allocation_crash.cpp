#include <iostream>

int main () {
    const int MAX_TRIES = 100000;
    // how much memory to try to allocate at once
    // 100000 bytes ~ 100kB
    const int SIZE = 100000;
    char *arr;
    for (int i = 0; i < MAX_TRIES; i++) {
        arr = new char[SIZE];
        if (i % 100 == 0) {
            std::cout << "Done iteration " << i << std::endl;
            // how much memory will be allocated before the program crashes?
            std::cout << "Total allocated: " << i * 100 << "kB" <<
                " (" << i/10 << "MB)" << std::endl;
        }
        // without the delete the memory will not be freed
        // and the program will eventually run out of memory
        // if the line below is not commented, the program will finish successfully
        // delete [] arr;
    }
    return 0;
}
