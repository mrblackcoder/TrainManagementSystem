#include "../include/train.h"
#include "../include/wagon.h"
#include "../include/material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Train* create_train(const char* name) {
    Train* t = (Train*)malloc(sizeof(Train));
    if (!t) {
        fprintf(stderr, "[ERROR] Failed to allocate train.\n");
        return NULL;
    }
    strncpy(t->name, name, sizeof(t->name)-1);
    t->name[sizeof(t->name)-1] = '\0';
    t->wagons = NULL;
    return t;
}

// Tek wagonu listeden çıkarmak ve free etmek için helper:
static void remove_wagon_from_train(Train* train, Wagon* w) {
    if (!train || !w) return;

    // bağlantıları kopar
    Wagon* prev = w->prev;
    Wagon* nxt  = w->next;

    if (!prev) {
        // head'i siliyorsak
        train->wagons = nxt;
    } else {
        prev->next = nxt;
    }
    if (nxt) {
        nxt->prev = prev;
    }

    for (int i = 0; i < w->num_boxes; i++) {
        if (w->boxes[i]) {
            free(w->boxes[i]);
            w->boxes[i] = NULL;
        }
    }
    free(w);
}

extern Material materials[3]; // Large=0, Medium=1, Small=2


static int unload_from_single_wagon(Wagon* wagon, int quantity, BoxSize size) {
    int removed = 0;
    for (int i = wagon->num_boxes - 1; i >= 0 && removed < quantity; i--) {
        Box* b = wagon->boxes[i];
        if (b && b->size == size) {
            float wgt = b->weight;
            free(b);

            for (int j = i; j < wagon->num_boxes - 1; j++) {
                wagon->boxes[j] = wagon->boxes[j + 1];
            }
            wagon->boxes[wagon->num_boxes - 1] = NULL;
            wagon->num_boxes--;

            wagon->current_weight -= wgt;
            if (wagon->current_weight < 0) wagon->current_weight = 0;

            // Material loaded_units--
            if (size == LARGE)   materials[0].loaded_units--;
            if (size == MEDIUM)  materials[1].loaded_units--;
            if (size == SMALL)   materials[2].loaded_units--;

            removed++;
        }
    }
    return removed;
}

/**
 * Tren'in son vagonundan başlayarak miktarı kadar boyutu şu kadar olan kutuları boşaltır.
 * Eğer bir vagon tamamen boşalırsa, vagon tren listesinden çıkarılır.
 */
int unload_boxes_from_tail(Train* train, int quantity, BoxSize size) {
    if (!train || quantity <= 0) return 0;

    // Son vagona git
    Wagon* current = train->wagons;
    if (!current) {
        printf("[WARN] Train is empty.\n");
        return 0;
    }

    while (current->next) {
        current = current->next;
    }

    int total_unloaded = 0;

    // Son vagondan başlayarak malzemeleri boşalt
    while (current && quantity > 0) {
        int unloaded_here = unload_from_single_wagon(current, quantity, size);
        total_unloaded += unloaded_here;
        quantity -= unloaded_here;

        // Eğer vagon tamamen boşaldıysa sil
        if (current->num_boxes == 0) {
            printf("[INFO] Wagon %d became empty -> removing.\n", current->wagon_id);
            Wagon* prevW = current->prev;
            remove_wagon_from_train(train, current);
            current = prevW; // Önceki vagona geç
        } else {
            current = current->prev; // Henüz boşalmamışsa, bir önceki vagona geç
        }
    }

    if (quantity > 0) {
        printf("[INFO] Not enough boxes of size %d to unload. Remaining quantity: %d\n", size, quantity);
    }

    printf("[INFO] Total unloaded: %d boxes of size %d.\n", total_unloaded, size);
    return total_unloaded;
}

/**
 * wagon_id'den miktarı kadar boyutu şu kadar olan kutuyu boşalt.
 * buradaki de hocam eğer wagon boşalarısa siler, bitmediyse devam önceki vagona geçer.
 */
int unload_boxes_from_wagon(Train* train, int wagon_id, int quantity, BoxSize size) {
    if (!train || quantity <= 0) return 0;

    // ID'si eşleşen vagonu bul
    Wagon* w = train->wagons;
    while (w && w->wagon_id != wagon_id) {
        w = w->next;
    }
    if (!w) {
        printf("[WARN] No wagon found with ID=%d.\n", wagon_id);
        return 0;
    }

    int total_unloaded = 0;
    Wagon* current = w;
    while (current && quantity > 0) {
        int unloaded_here = unload_from_single_wagon(current, quantity, size);
        total_unloaded += unloaded_here;
        quantity       -= unloaded_here;

        if (current->num_boxes == 0) {
            printf("[INFO] Wagon %d became empty -> removing.\n", current->wagon_id);
            Wagon* prevW = current->prev;
            remove_wagon_from_train(train, current);
            current = prevW;
        } else {
            current = current->prev;
        }
    }

    return total_unloaded;
}

void add_wagon_to_train(Train* train, Wagon* wagon) {
    if (!train || !wagon) return;

    int next_available_id = 1;
    Wagon* current = train->wagons;

    int used_ids[1000] = {0};
    while (current) {
        if (current->wagon_id > 0 && current->wagon_id < 1000) {
            used_ids[current->wagon_id] = 1;
        }
        current = current->next;
    }

    // Find the first unused ID
    for (int i = 1; i < 1000; i++) {
        if (used_ids[i] == 0) {
            next_available_id = i;
            break;
        }
    }

    wagon->wagon_id = next_available_id;

    // Step 2: Add the new wagon to the end of the train
    if (!train->wagons) {
        train->wagons = wagon;
    } else {
        Wagon* temp = train->wagons;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = wagon;
        wagon->prev = temp;
    }

    printf("[INFO] Wagon %d added to train %s.\n", wagon->wagon_id, train->name);
}


void display_train(const Train* train) {
    if (!train) {
        fprintf(stderr, "[WARN] No train to display.\n");
        return;
    }
    printf("Train: %s\n", train->name);
    Wagon* w = train->wagons;
    while (w) {
        print_wagon(w);
        w = w->next;
    }
}

void free_train(Train* train) {
    if (!train) return;
    Wagon* w = train->wagons;
    while (w) {
        // kutuları free yapıyoruz
        for (int i = 0; i < w->num_boxes; i++) {
            if (w->boxes[i]) {
                free(w->boxes[i]);
                w->boxes[i] = NULL;
            }
        }
        Wagon* nextW = w->next;
        free(w);
        w = nextW;
    }
    free(train);
}

void reset_train(Train* train) {
    if (!train) return;

    // 1. Vagonları sıfırla
    Wagon* w = train->wagons;
    while (w) {
        // Kutuları serbest bırak
        for (int i = 0; i < w->num_boxes; i++) {
            if (w->boxes[i]) {
                free(w->boxes[i]);  // Kutuyu serbest bırak
                w->boxes[i] = NULL;
            }
        }
        w->current_weight = 0.0f; // Vagonun ağırlığını sıfırla
        w->num_boxes = 0;         // Vagon kutu sayısını sıfırla
        w = w->next;
    }

    // tüm vagonları sıfırlamak için;
    train->wagons = NULL;

    // Materiallerin ne kadar kullanıldığını gösteren değerleri sıfırlar
    for (int i = 0; i < 3; i++) {
        materials[i].loaded_units = 0;
    }

    printf("[INFO] Train '%s' and materials have been reset to their initial state.\n", train->name);
}
/**
 * Eğer mevcut vagonlar bu kutuyu kabul edemiyorsa yeni bir vagon ekle,
 * ve vagonu ilgili yere koy.
 */
int load_box_into_train(Train* train, Box* box, float new_wagon_capacity) {
    if (!train || !box) return 0;

    
    Wagon* w = train->wagons;
    while (w) {
        if (add_box_to_wagon(w, box)) {
            return 1;
        }
        w = w->next;
    }

    Wagon* newW = create_wagon(new_wagon_capacity);
    add_wagon_to_train(train, newW);
    if (!add_box_to_wagon(newW, box)) {
        fprintf(stderr, "[ERROR] Even new wagon can't accept box %d.\n", box->box_id);
        free(box);
        return 0;
    }
    return 1;
}

/**
 * Loads a box into a specific wagon by its ID.
 * If the wagon is full or does not exist, it prints an error message.
 */

int load_box_into_specific_wagon(Train* train, Box* box, int wagon_id) {
    if (!train || !box) return 0;

    Wagon* w = train->wagons;
    while (w && w->wagon_id != wagon_id) {
        w = w->next;
    }

    if (!w) {
        printf("[ERROR] Wagon with ID %d does not exist.\n", wagon_id);
        return 0;
    }

    if (add_box_to_wagon(w, box)) {
        printf("[INFO] Box %d successfully loaded into wagon %d.\n", box->box_id, wagon_id);
        return 1;
    } else {
        printf("[ERROR] Wagon %d is either full or exceeds weight capacity. Box %d not loaded.\n", wagon_id, box->box_id);
        return 0;
    }
}