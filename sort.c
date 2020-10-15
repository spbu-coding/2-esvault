#include<stddef.h>

void swap(int *first, int *second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
}

void sort_array(int *array, size_t array_size) {
    for (size_t i = 0; i < array_size; ++i) {
        for (size_t j = i + 1; j < array_size; ++j) {
            if (array[i] > array[j]) {
                swap(array + i, array + j);
            }
        }
    }
}