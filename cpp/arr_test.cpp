#include<stdio.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))
int array[] = {23,34,12,17,204,99,16};

int main() {
    for(int d=-1; d <= sizeof(array[0]); d++) {
        printf("%d\n",array[d+1]);
    }


    return 0;
}
