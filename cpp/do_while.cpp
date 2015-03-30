#include <iostream>
int main() {
    int i=1;
    do {
        std::cout << i << std::endl;
        i++;
        if(i < 15) {
            continue;
        }
    } while(false);
    return 0;
}
