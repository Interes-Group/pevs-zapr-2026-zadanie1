#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
    printf("Usage: program [options]\n");
    printf("Options:\n");
    printf("  -h, --help      Display this help message\n");
}

int get_random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main(int argc, char *argv[]) {
    // spracovanie argumentov podľa návodu https://zapr.interes.group/guides/program_arguments/
    int help = 0;
    if (argc <= 1) {
        print_help();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        // TODO pridaj ďalšie argumenty alebo to prerob podľa seba
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help = 1;
            break;
        } else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }
    if (help) print_help();

    // TODO implementuj svoje riešenie

    return 0;
}
