#include "../include/file_ops.h"
#include "../include/material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// materials dizisinde: 
//  materials[0] => Large / Steel
//  materials[1] => Medium / Aluminium
//  materials[2] => Small / Wood
extern Material materials[3];

/**
 * Kutu dizisindeki gerçek ağırlığa bakarak
 * wagon->current_weight'i senkronize eder.
 */
float recalc_wagon_weight(Wagon* wagon) {
    if (!wagon) return 0.0f;
    float total = 0.0f;
    for (int i = 0; i < wagon->num_boxes; i++) {
        if (wagon->boxes[i]) {
            total += wagon->boxes[i]->weight;
        }
    }
    wagon->current_weight = total;
    return total;
}

void save_train_to_file(const Train* train, const char* filename) {
    if (!train || !filename) return;

    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open file %s for writing.\n", filename);
        return;
    }

    int wagon_count = 0;
    {
        const Wagon* tmp = train->wagons;
        while (tmp) {
            wagon_count++;
            tmp = tmp->next;
        }
    }
    fprintf(fp, "TRAIN:%s:%d\n", train->name, wagon_count);

    fprintf(fp, "M:Large Box:Steel:200.00:%d\n", materials[0].loaded_units);
    fprintf(fp, "M:Medium Box:Aluminium:150.00:%d\n", materials[1].loaded_units);
    fprintf(fp, "M:Small Box:Wood:100.00:%d\n", materials[2].loaded_units);

    const Wagon* w = train->wagons;
    while (w) {
        recalc_wagon_weight((Wagon*)w);

        fprintf(fp, "WAGON:%d:%.2f:%.2f\n",
                w->wagon_id, w->max_weight, w->current_weight);

        for (int i = 0; i < w->num_boxes; i++) {
            Box* bx = w->boxes[i];
            if (!bx) continue;

            if (bx->size == LARGE) {
                fprintf(fp, "L:Large Box\n");
            } else if (bx->size == MEDIUM) {
                fprintf(fp, "L:Medium Box\n");
            } else if (bx->size == SMALL) {
                fprintf(fp, "L:Small Box\n");
            }
        }
        w = w->next;
    }

    fclose(fp);
    printf("[INFO] Train data saved to %s\n", filename);
}


 
void load_train_from_file(Train* train, const char* filename) {
    if (!train || !filename) return;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open file %s for reading.\n", filename);
        return;
    }

    char line[256];
    Wagon* currentWagon = NULL;

    while (fgets(line, sizeof(line), fp)) {
        // satır sonu karakterlerini temizlemek için
        line[strcspn(line, "\r\n")] = '\0';

        if (strncmp(line, "TRAIN:", 6) == 0) {
            

        } else if (strncmp(line, "MATERIALS:", 10) == 0) {

        } else if (strncmp(line, "M:", 2) == 0) {
            
            
            char boxName[50];
            char matName[50];
            float wgt;
            int qty, loaded;
           
            sscanf(line, "M:%[^:]:%[^:]:%f:%d:%d", boxName, matName, &wgt, &qty, &loaded);

            if (strcmp(boxName, "Large Box") == 0) {
                materials[0].loaded_units = loaded;
            } else if (strcmp(boxName, "Medium Box") == 0) {
                materials[1].loaded_units = loaded;
            } else if (strcmp(boxName, "Small Box") == 0) {
                materials[2].loaded_units = loaded;
            }
        }
        else if (strncmp(line, "WAGON:", 6) == 0) {
            int wagon_id;
            float maxW, curW;
            sscanf(line, "WAGON:%d:%f:%f", &wagon_id, &maxW, &curW);

            Wagon* newW = create_wagon(maxW);
            newW->wagon_id       = wagon_id;
            newW->current_weight = curW; 
            add_wagon_to_train(train, newW);

            currentWagon = newW; 
        }
        else if (strncmp(line, "L:", 2) == 0) {
            char boxLabel[100];
            strcpy(boxLabel, line + 2);
            while (*boxLabel == ' ') {
                memmove(boxLabel, boxLabel+1, strlen(boxLabel));
            }
            // boyutu bulmak için
            BoxSize s = SMALL;
            if (strcmp(boxLabel, "Medium Box") == 0) s = MEDIUM;
            if (strcmp(boxLabel, "Large Box")  == 0) s = LARGE;

            static int box_id_counter = 1000;
            Box* bx = create_box(box_id_counter++, s);

            if (currentWagon) {
                add_box_to_wagon(currentWagon, bx);
            }
        }
        else {
        }
    }

    fclose(fp);
    printf("[INFO] Train data loaded from %s\n", filename);
}
