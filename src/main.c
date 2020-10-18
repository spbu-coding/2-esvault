#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ELEMENTS_IN_ARRAY 100

#define error(...) (fprintf(stderr, __VA_ARGS__))

typedef enum {
    FROM,
    TO
} PARAMETER;

typedef struct {
    PARAMETER type;
    int value;
} parameter_t;

parameter_t read_parameter(char *parameter, int *is_from_correct, int *is_to_correct);
int set_parameters_values(int argv, char **argc, int *from, int *to);

int read_array(int *array, size_t *array_size);
int create_new_array(int const *array, size_t array_size, int *new_array, size_t *new_size, int from, int to);
void copy_array(int *dest, int const *src, size_t array_size);
size_t count_swap(int const *first_array, int const *second_array, size_t arrays_size);

void sort_array(int *array, size_t array_size);

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
    return swap_count;
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
        } else if (array[i] >= to) {
            if (fprintf(stderr, "%d ", array[i]) < 0) {
                error("Cannot write to stderr");
                return -5;
            }
        }
    }
    *new_size = new_array_iterator;
    return 0;
}

parameter_t read_parameter(char *parameter, int *is_from_correct, int *is_to_correct) {
    char *token = strtok(parameter, "=");
    char *val = strtok(NULL, "=");
    parameter_t param;
    if (strcmp(token, "--from") == 0) {
        param.type = FROM;
        int tmp = strtol(val, &val, 10);
        if (tmp || val[0] == '0') {
            param.value = tmp;
            *is_from_correct = 1;
        } else {
            param.value = 0;
            *is_from_correct = 0;
        }
        return param;
    } else if (strcmp(token, "--to") == 0) {
        param.type = TO;
        int tmp = strtol(val, &val, 10);
        if (tmp || val[0] == '0') {
            param.value = tmp;
            *is_to_correct = 1;
        } else {
            param.value = 0;
            *is_to_correct = 0;
        }

        return param;
    } else {
        error( "Wrong parameter!!!");
        parameter_t p = {FROM, INT_MAX};
        return p;
    }
}

int set_parameters_values(int argv, char **argc, int *from, int *to) {
    if (argv < 2) {
        return -1;
    }
    if (argv > 3) {
        return -2;
    }
    int from_parameter_count = 0;
    int to_parameter_count = 0;
    int is_from_correct = 1;
    int is_to_correct = 1;
    for (int i = 1; i < argv; ++i) {
        parameter_t param = read_parameter(argc[i], &is_from_correct, &is_to_correct);
        switch (param.type) {
            case FROM:
                from_parameter_count++;
                *from = param.value;
                break;
            case TO:
                to_parameter_count++;
                *to = param.value;
                break;
        }
    }
    if (from_parameter_count > 1 || to_parameter_count > 1) {
        return -3;
    }
    if (is_from_correct || is_to_correct) {
        if (is_from_correct && !is_to_correct) {
            *to = INT_MAX;
        } else if (!is_from_correct && is_to_correct) {
            *from = INT_MIN;
        }
    } else {
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
