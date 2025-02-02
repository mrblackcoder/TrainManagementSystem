
#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct {
    char name[50];
    float weight;
    int quantity;
    int loaded_units;
} Material;

extern Material materials[3];

void initialize_materials(void);

#endif
