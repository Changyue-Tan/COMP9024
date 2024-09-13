#include <stdio.h>

void Swap(int *pa, int *pb) {
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

int IsLess(int a, int b) {
    return a < b;
}

int IsLarger(int a, int b) {
    return a > b;
}

void PrintArray(int *ptr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}

// Define a function pointer type, which points to a function
typedef int (*ComparatorFuncPtr)(int, int);


/*
0 1 2 3 4 5 6 7 8 9
n       = 10
n - 1   = 9
n - 2   = 8
*/

void BubbleSort2(int *ptr, int n, ComparatorFuncPtr compare) {
    for (int iMax = n - 2; iMax >= 0; iMax--) {
        for (int i = 0; i < iMax; i++) {
            if (compare(ptr[i], ptr[i + 1])) {
                Swap(ptr + i, ptr + i + 1);
            }
        }       
    }
}

int main(void) {    
    int arr[] = {30, 50, 20, 10, 60, 40};
    int len = sizeof(arr) / sizeof(arr[0]);
    
    // a function pointer variable which points to the function IsLarger()
    ComparatorFuncPtr fptr = &IsLarger;    
    printf("Before sorting:\n");
    PrintArray(arr, len);
    BubbleSort2(arr, len, fptr);
    // in ascending order
    printf("After sorting:\n");
    PrintArray(arr, len);

    // a function pointer variable which points to the function IsLess()
    fptr = &IsLess;    
    printf("\nBefore sorting:\n");
    PrintArray(arr, len);
    BubbleSort2(arr, len, fptr);
    // in descending order
    printf("After sorting:\n");
    PrintArray(arr, len);
    return 0;
}
