/* Sort Integers by The Number of 1 Bits
https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/description/ */

int count_bits(int num) {
    int count = 0;
    while (num > 0) {
        count += (num & 1);
        num >>= 1;
    }
    return count;
}


int compare(const void* a, const void* b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    
    int count_a = count_bits(int_a);
    int count_b = count_bits(int_b);
    
    if (count_a == count_b) {
        return int_a - int_b;
    }
    return count_a - count_b;
}

int* sortByBits(int* arr, int arrSize, int* returnSize) {
    int* result = (int*)malloc(arrSize * sizeof(int));
    if (!result) {
        *returnSize = 0;
        return 0;
    }
    
    for (int i = 0; i < arrSize; i++) {
        result[i] = arr[i];
    }
    
    qsort(result, arrSize, sizeof(int), compare);
    
    *returnSize = arrSize;
    return result;
}