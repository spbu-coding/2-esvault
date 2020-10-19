#include <stdio.h>

int do_something(int cool) {
    return ++cool;
}

int main(int argc, char *argv[]) {
    if (argv) {
        int cool = 0;
        do_something(cool);
    }
    if (argc == 1) {
        return -1;
    } else if (argc == 2) {
        fprintf(stdout, "%d ", 2);
        fprintf(stdout, "%d ", 1);
        return 3;
    } else if (argc == 3) {
        fprintf(stdout, "%d ", 1);
        fprintf(stderr, "%d ", 10);
        return 3;
    } else {
        return -2;
    }
}
