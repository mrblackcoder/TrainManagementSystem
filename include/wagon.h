#ifndef WAGON_H
extern int global_wagon_id_counter;
#define WAGON_H

#include "box.h"

#define MAX_BOXES 50

typedef struct Wagon {
    int wagon_id;
    float max_weight;      
    float current_weight;
    int num_boxes;
    Box* boxes[MAX_BOXES];

    struct Wagon* next;
    struct Wagon* prev;
} Wagon;

/**
 * Yeni bir wagon oluştur (1000 kg kapasite).
 */
Wagon* create_wagon(float max_weight);

/**
 * Vagonun içindeki kutuların en küçük boyutunu döndürür.
 * Eğer vagon boşsa 0 döndürür.
 */
BoxSize get_smallest_box_size(const Wagon* wagon);

/**
 * Kutuyu bu vagona eklemeye çalışır. 
 * (Kapasite + stacking rule)
 * Dönüş: 1 (başarılı), 0 (başarısız).
 */
int add_box_to_wagon(Wagon* wagon, Box* box);

/**
 * Vagon bilgisini ekrana yazdırır.
 */
void print_wagon(const Wagon* wagon);

#endif
