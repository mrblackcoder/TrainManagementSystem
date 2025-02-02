#include "../include/wagon.h"
#include "../include/material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Wagon* create_wagon(float max_weight) {
    Wagon* w = (Wagon*)malloc(sizeof(Wagon));
    if (!w) {
        fprintf(stderr, "[ERROR] Failed to allocate wagon.\n");
        return NULL;
    }
    w->wagon_id = 0;
    w->max_weight = max_weight;
    w->current_weight = 0.0f;
    w->num_boxes = 0;
    for (int i = 0; i < MAX_BOXES; i++) {
        w->boxes[i] = NULL;
    }
    w->next = NULL;
    w->prev = NULL;
    return w;
}

/**
 * Vagon boşsa 0 döndürüyoruz. 
 * Değilse kutuların boyutlarına bakarak en küçük boyutu buluyoruz.
 */
BoxSize get_smallest_box_size(const Wagon* wagon) {
    if (!wagon || wagon->num_boxes == 0) {
        return 0; // wagon boş => 0
    }
    BoxSize minSize = LARGE;
    for (int i = 0; i < wagon->num_boxes; i++) {
        Box* b = wagon->boxes[i];
        if (b && b->size < minSize) {
            minSize = b->size;
        }
    }
    return minSize;
}
extern Material materials[3];

int add_box_to_wagon(Wagon* wagon, Box* box) {
    if (!wagon || !box) return 0;

    // Kapasite
    if (wagon->current_weight + box->weight > wagon->max_weight) {
        fprintf(stderr, "[WARN] Wagon %d capacity (%.1f) exceeded.\n",
                wagon->wagon_id, wagon->max_weight);
        return 0;
    }

    // Dizide yer var mı?
    if (wagon->num_boxes >= MAX_BOXES) {
        fprintf(stderr, "[WARN] Wagon %d is full (max %d boxes).\n",
                wagon->wagon_id, MAX_BOXES);
        return 0;
    }

    // stacking rule
    BoxSize smallest = get_smallest_box_size(wagon);
    if (smallest == 0) {
        // Vagon boş -> her boyuta izin var
    }
    else if (smallest == SMALL) {
        // Vagonda SMALL varsa, MEDIUM veya LARGE eklenemez
        if (box->size != SMALL) {
            fprintf(stderr, "[WARN] Wagon %d has SMALL => can't add MEDIUM or LARGE.\n",
                    wagon->wagon_id);
            return 0;
        }
    }
    else if (smallest == MEDIUM) {
        // Vagonda MEDIUM veya SMALL varsa, LARGE eklenemez
        if (box->size == LARGE) {
            fprintf(stderr, "[WARN] Wagon %d has MEDIUM => can't add LARGE.\n",
                    wagon->wagon_id);
            return 0;
        }
    }
    else if (smallest == LARGE) {
        // kısıtlama yok yani LARGE altına SMALL veya MEDIUM gelebilir
    }

      wagon->boxes[wagon->num_boxes] = box;
    wagon->num_boxes++;
    wagon->current_weight += box->weight;

    // Material loaded_units güncellemesi
    if (box->size == LARGE) {
        materials[0].loaded_units++; 
    } else if (box->size == MEDIUM) {
        materials[1].loaded_units++;
    } else if (box->size == SMALL) {
        materials[2].loaded_units++;
    }

    printf("[INFO] Box %d added. Material loaded_units updated.\n", box->box_id);
    return 1;
}

void print_wagon(const Wagon* wagon) {
    if (!wagon) {
        printf("No wagon.\n");
        return;
    }
    printf("Wagon %d => max=%.1f, current=%.1f, boxes=%d\n",
           wagon->wagon_id, wagon->max_weight, wagon->current_weight, wagon->num_boxes);
    for (int i = 0; i < wagon->num_boxes; i++) {
        Box* b = wagon->boxes[i];
        if (b) {
            printf("   [Box ID=%d, Weight=%.1f, Size=%d]\n",
                   b->box_id, b->weight, b->size);
        }
    }
}
