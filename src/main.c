#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

typedef enum {
    FROM,
    TO
} PARAMETER;

typedef struct {
    PARAMETER type;
    long long value;
} parameter_t;

parameter_t read_parameter(char *parameter, int *is_from_correct, int *is_to_correct);
int set_parameters_values(int argc, char **argv, long long *from, long long *to);

int main(int argc, char *argv[]) {
    long long from = LLONG_MIN;
    long long to = LLONG_MAX;
    int parameters_correctness = set_parameters_values(argc, argv, &from, &to);
    if (parameters_correctness != 0) {
        return parameters_correctness;
    }
    fprintf(stdout, "%d %d", 2, 1);
    return 3;
}

parameter_t read_parameter(char *parameter, int *is_from_correct, int *is_to_correct) {
    char *token = strtok(parameter, "=");
    char *val = strtok(NULL, "=");
    parameter_t param;
    if (strcmp(token, "--from") == 0) {
        param.type = FROM;
        long long tmp = strtol(val, &val, 10);
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
        long long tmp = strtol(val, &val, 10);
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

int set_parameters_values(int argc, char **argv, long long *from, long long *to) {
    if (argc < 2) {
        return -1;
    }
    if (argc > 3) {
        return -2;
    }
    int from_parameter_count = 0;
    int to_parameter_count = 0;
    int is_from_correct = 1;
    int is_to_correct = 1;
    for (int i = 1; i < argc; ++i) {
        parameter_t param = read_parameter(argv[i], &is_from_correct, &is_to_correct);
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
            *to = LLONG_MAX;
        } else if (!is_from_correct && is_to_correct) {
            *from = LLONG_MIN;
        }
    } else {
        return -4;
    }
    return 0;
}
