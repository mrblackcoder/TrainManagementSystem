#include "../include/utils.h"
#include <stdio.h>

void print_error(const char* msg) {
    fprintf(stderr, "[ERROR] %s\n", msg);
}

void print_info(const char* msg) {
    fprintf(stdout, "[INFO] %s\n", msg);
}
