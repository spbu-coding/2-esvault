#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ELEMENTS_IN_ARRAY 100

#define error(...) (fprintf(stderr, __VA_ARGS__))

int set_parameters_values(int argc, char **argv, int *from, int *to);

int read_array(int *array, size_t *array_size);
int create_new_array(int const *array, size_t array_size, int *new_array, size_t *new_size, int from, int to);
void copy_array(int *dest, int const *src, size_t array_size);
size_t count_swap(int const *first_array, int const *second_array, size_t arrays_size);

void sort_array(int *array, int array_size);

int main(int argv, char *argc[]) {
    int from = INT_MIN;
    int to = INT_MAX;
    int parameters_correctness = set_parameters_values(argv, argc, &from, &to);
    if (parameters_correctness != 0) {
        return parameters_correctness;
    }
    size_t array_size = 0;
    int *array = (int *)malloc(MAX_ELEMENTS_IN_ARRAY * sizeof(int));
    if (array == NULL) {
        error("Cannot allocate array");
        return -5;
    }
    int reading_result = read_array(array, &array_size);
    if (reading_result != 0) {
        return reading_result;
    }
    size_t new_array_size = 0;
    int *new_array = (int *)malloc(MAX_ELEMENTS_IN_ARRAY * sizeof(int));
    if (new_array == NULL) {
        error("Cannot allocate new array");
        return -5;
    }
    int creating_status = create_new_array(array, array_size, new_array, &new_array_size, from, to);
    if (creating_status != 0) {
        return creating_status;
    }
    int *new_array_copy = (int *)malloc(new_array_size * sizeof(int));
    if (new_array_copy == NULL) {
        error("Cannot allocate new array copy");
        return -5;
    }
    copy_array(new_array_copy, new_array, new_array_size);
    sort_array(new_array, new_array_size);
    int swap_count = count_swap(new_array, new_array_copy, new_array_size);
    free(array);
    free(new_array);
    free(new_array_copy);
    return swap_count;
}

int set_parameters_values(int argc, char **argv, int *from, int *to) {
    if (argc < 2) {
        return -1;
    }
    if (argc > 3) {
        return -2;
    }
    int from_parameter_count = 0;
    int to_parameter_count = 0;
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--from=", 7) == 0) {
            from_parameter_count++;
            *from = (int)strtoll(argv[i] + 7, NULL, 10);
        }
        if (strncmp(argv[i], "--to=", 5) == 0) {
            to_parameter_count++;
            *to = (int)strtoll(argv[i] + 5, NULL, 10);
        }
    }
    if (from_parameter_count > 1 || to_parameter_count > 1) {
        return -3;
    }
    if (from_parameter_count == 0 && to_parameter_count == 0) {
        return -4;
    }
    return 0;
}

int read_array(int *array, size_t *array_size) {
    char div = ' ';
    size_t array_iterator = 0;
    while (div == ' ') {
        if(scanf("%d%c", &array[array_iterator++], &div) < 2) {
            error("Cannot read element");
            return -5;
        }
    }
    *array_size = array_iterator;
    return 0;
}

int create_new_array(int const *array, size_t array_size, int *new_array, size_t *new_size, int from, int to) {
    size_t new_array_iterator = 0;
    for (size_t i = 0; i < array_size; ++i) {
        if (array[i] > from && array[i] < to) {
            new_array[new_array_iterator++] = array[i];
        } else if (array[i] <= from) {
            if (fprintf(stdout, "%d ", array[i]) < 0) {
                error("Cannot write to stdout");
                return -5;
            }
            if (array[i] >= to) {
                if (fprintf(stderr, "%d ", array[i]) < 0) {
                    error("Cannot write to stderr");
                    return -5;
                }
            }
        } else if (array[i] >= to) {
            if (fprintf(stderr, "%d ", array[i]) < 0) {
                error("Cannot write to stderr");
                return -5;
            }
            if (array[i] <= from) {
                if (fprintf(stdout, "%d ", array[i]) < 0) {
                    error("Cannot write to stdout");
                    return -5;
                }
            }
        }
    }
    *new_size = new_array_iterator;
     return 0;
}

void copy_array(int *dest, int const *src, size_t array_size) {
    for (size_t i = 0; i < array_size; ++i) {
        dest[i] = src[i];
    }
}

size_t count_swap(int const *first_array, int const *second_array, size_t arrays_size) {
    size_t swap_count = 0;
    for (size_t i = 0; i < arrays_size; ++i) {
        if (first_array[i] != second_array[i]) {
            swap_count++;
        }
    }
    return swap_count;
}
