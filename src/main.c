#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return -1;
    } else if (argc == 2) {
        fprintf(stdout, "%d %d", 2, 1);
        return 3;
    } else if (argc == 3) {
        fprintf(stdout, "%d ", 1);
        fprintf(stderr, "%d ", 10);
        return 3;
    } else {
        return -2;
    }
}
