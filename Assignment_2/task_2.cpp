// Implementing Swap Function in C++

#include<stdio.h>
#include<stdlib.h>


void swapByValue(int x, int y) {

    int swap = x;
    x = b;
    b = swap;

}


void swapByReference(int *x, int *y) {

    int swap = *x;
    *x = *y;
    *y = swap;
}

void swapByPointer(int &x, int &y) {

    int swap = x;
    x = y;
    y = swap;
}



int main() {

    int a = 3, b = 4;

    printf("Before Swap");

    printf("a = %d, b = %d \n", a, b);

    printf("After Swap by Value ");

    swapByValue(a,b);

    printf("a = %d, b = %d \n", a, b);

    printf("After Swap by Reference ");

    swapByReference(a,b);

    printf("a = %d, b = %d \n", a, b);

    printf("After Swap by Pointer ");

    swapByPointer(a,b);

    printf("a = %d, b = %d \n", a, b);
}

