#include <stdio.h>

// void swap(int *pa, int *pb) {
//     int tmp = *pa;
//     *pa = *pb;
//     *pb = tmp;
// }

// void BubbleSort(int *ptr, int n) {
//     if (n > 1) {
//         for (int i = 0; i <= n - 2; i++) {
//             if (ptr[i] > ptr[i + 1]) {
//                 swap(ptr + i, ptr + i + 1);
//             }
//         }
//         BubbleSort(ptr, n - 1);
//     }
// }

// void printArray(int *arr, int n) {
//     for (int i = 0; i < n; i++) {
//         printf("%d,",arr[i]);
//     }
//     printf("\n");
// }

// int main(void) {
//     int arr[] = {3, 5, 2 ,1, 6, 4};
//     int n = sizeof(arr)/sizeof(arr[0]);
//     printArray(arr, n);
//     BubbleSort(arr, n);
//     printArray(arr, n);
    
// }

int getSum(int *ptr, int n) {
    if (n == 1) {
        return ptr[0];
    } else {
        return ptr[n-1] + getSum(ptr, n-1);
    }
}

int main(void) {
    int nums[] = {3, 5, 2 ,1, 6, 4};
    int len = sizeof(nums)/sizeof(nums[0]);
    printf("%d\n", getSum(nums, len));
    
}

