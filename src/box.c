#include "../include/box.h"
#include <stdio.h>
#include <stdlib.h>

Box* create_box(int box_id, BoxSize size) {
    float weight = 0.0f;
    switch (size) {
        case SMALL:  weight = 100.0f; break;
        case MEDIUM: weight = 150.0f; break;
        case LARGE:  weight = 200.0f; break;
        default:
            fprintf(stderr, "[ERROR] Unknown box size.\n");
    }

    Box* b = malloc(sizeof(Box));
    if (!b) {
        fprintf(stderr, "[ERROR] Allocation failed for Box.\n");
        return NULL;
    }
    b->box_id = box_id;
    b->weight = weight;
    b->size   = size;
    return b;
}

void print_box(const Box* box) {
    if (!box) {
        fprintf(stderr, "[WARN] Trying to print a NULL box.\n");
        return;
    }
    printf("Box(ID=%d, Weight=%.1f, Size=", box->box_id, box->weight);
    switch (box->size) {
        case SMALL:  printf("SMALL");  break;
        case MEDIUM: printf("MEDIUM"); break;
        case LARGE:  printf("LARGE");  break;
        default:     printf("UNKNOWN");break;
    }
    printf(")\n");
}
