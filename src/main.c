#include <stdio.h>
#include <getopt.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

#define MAX_NUMBER_OF_ELEMENTS 100
#define DECIMAL_NOTATION 10
#define MIN_NUMBER_OF_PARAMETERS 2
#define MAX_NUMBER_OF_PARAMETERS 3

#define MEMORY_ALLOCATION_ERROR_CODE -5
#define SCANF_ERROR_CODE -6
#define FPRINTF_ERROR_CODE -7

extern int selection_sort(long long *, int);

int parsing_and_checking_parameters(const int *argc, char **argv, long long *from, long long *to) {
    bool first_parameter_is_entered = false, second_parameter_is_entered = false;
    if (*argc < MIN_NUMBER_OF_PARAMETERS)
        return -1;
    if (*argc > MAX_NUMBER_OF_PARAMETERS)
        return -2;

    const struct option long_options[] = {
            {"from", optional_argument, NULL, 'f'},
            {"to",   optional_argument, NULL, 't'},
            {NULL,   0,                 NULL, 0}
    };
    int option_index = 0;

    opterr = 0; // Disabling getopt() error messages
    optind = 1; // Setting the index on the first element of parameters

    int result_of_reading = getopt_long(*argc, argv, "", long_options, &option_index);
    while (result_of_reading != -1) {
        switch (result_of_reading) {
            case 'f':
                if (first_parameter_is_entered)
                    return -3;
                *from = strtoll((optarg ? optarg : "0"), NULL, DECIMAL_NOTATION);
                first_parameter_is_entered = true;
                break;

            case 't':
                if (second_parameter_is_entered)
                    return -3;
                *to = strtoll((optarg ? optarg : "0"), NULL, DECIMAL_NOTATION);
                second_parameter_is_entered = true;
                break;

            case '?':
                break;

            default:
                return -4;
        }
        result_of_reading = getopt_long(*argc, argv, "", long_options, &option_index);
    }
    if (!first_parameter_is_entered && !second_parameter_is_entered)
        return -4;
    return 0;
}

int parsing_the_input_array(long long *input_array, int *input_cardinality) {
    char separator = ' ';
    while (separator == ' ') {
        if (scanf("%lld%c", &input_array[*input_cardinality], &separator) < 2) {
            error("Cannot read the [%d] element of input array\n", *input_cardinality);
            return SCANF_ERROR_CODE;
        }
        *input_cardinality += 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    long long from = LLONG_MIN, to = LLONG_MAX;
    int parsing_parameters_result = parsing_and_checking_parameters(&argc, argv, &from, &to);
    if (parsing_parameters_result)
        return parsing_parameters_result;

    long long *input_array = (long long *) malloc(sizeof(long long) * MAX_NUMBER_OF_ELEMENTS);
    if (input_array == NULL) {
        error("Cannot allocate memory for input array\n");
        return MEMORY_ALLOCATION_ERROR_CODE;
    }

    int input_cardinality = 0;
    int parsing_array_result = parsing_the_input_array(input_array, &input_cardinality);
    if (parsing_array_result)
        return parsing_array_result;

    input_array = (long long *) realloc(input_array, sizeof(long long) * input_cardinality);
    if (input_array == NULL) {
        error("Cannot reallocate memory for input array\n");
        return MEMORY_ALLOCATION_ERROR_CODE;
    }

    int sorted_cardinality = 0;
    for (int i = 0; i < input_cardinality; ++i) {
        if (input_array[i] <= from)
            if (fprintf(stdout, "%lld ", input_array[i]) < 0) {
                error("Cannot write the %d element to stdout\n", i);
                return FPRINTF_ERROR_CODE;
            }
        if (input_array[i] >= to)
            if (fprintf(stderr, "%lld ", input_array[i]) < 0) {
                error("Cannot write the %d element to stderr\n", i);
                return FPRINTF_ERROR_CODE;
            }
        if (input_array[i] > from && input_array[i] < to)
            ++sorted_cardinality;
    }

    long long *sorted_array = (long long *) malloc(sizeof(long long) * sorted_cardinality);
    if (sorted_array == NULL) {
        error("Cannot allocate memory for sorted array\n");
        return MEMORY_ALLOCATION_ERROR_CODE;
    }

    int counter = 0;
    for (int i = 0; i < input_cardinality; ++i) {
        if (input_array[i] > from && input_array[i] < to) {
            sorted_array[counter] = input_array[i];
            ++counter;
        }
    }

    selection_sort(sorted_array, sorted_cardinality);
    int number_of_permutations = 0;
    counter = 0;
    for (int i = 0; i < input_cardinality; ++i) {
        if (input_array[i] > from && input_array[i] < to) {
            if (input_array[i] != sorted_array[counter])
                ++number_of_permutations;
            ++counter;
        }
    }

    free(input_array);
    free(sorted_array);
    return number_of_permutations;
}
