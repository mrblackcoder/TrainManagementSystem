#ifndef TRAIN_H
#define TRAIN_H

#include "wagon.h"

typedef struct Train {
    char name[100];
    Wagon* wagons; // trenin baş vagonuna işaret eder (doubly linked list)
} Train;

/**
 * Yeni bir tren oluştur burada da işte daha sonra mainde kullanacağımız ismi belirtiyoruz (T123 yazıldı).
 */
Train* create_train(const char* name);

/**
 * Belirli miktarda kutu boşaltma (örnek):
 * wagon_id'den 'quantity' adet 'size' kutuyu boşalt,
 * vagon boşalırsa sil, önceki vagona devam et.
 */
int unload_boxes_from_wagon(Train* train, int wagon_id, int quantity, BoxSize size);

/**
 * Trene yeni wagon ekle (sona ekliyor).
 */
void add_wagon_to_train(Train* train, Wagon* wagon);

/**
 * Treni ekrana yazdır.
 */
void display_train(const Train* train);

int unload_boxes_from_tail(Train* train, int quantity, BoxSize size);

int load_box_into_specific_wagon(Train* train, Box* box, int wagon_id);


/**
 * Tüm vagonları (ve kutuları) serbest bırak, en sonda treni free et.
 */
void free_train(Train* train);


void reset_train(Train* train);
/**
 * load_box_into_train:
 *   - mevcut vagonlara bak, eğer eklenemiyorsa yeni wagon yarat, oraya ekle
 */
int load_box_into_train(Train* train, Box* box, float new_wagon_capacity);

#endif
