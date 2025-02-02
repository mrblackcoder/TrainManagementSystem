// material.c
#include "../include/material.h"
#include <string.h>

Material materials[3];

void initialize_materials(void) {
    // 0 -> Large
    strcpy(materials[0].name, "Steel");
    materials[0].weight       = 200.0f;
    materials[0].quantity     = 1;
    materials[0].loaded_units = 0;

    // 1 -> Medium
    strcpy(materials[1].name, "Aluminium");
    materials[1].weight       = 150.0f;
    materials[1].quantity     = 1;
    materials[1].loaded_units = 0;

    // 2 -> Small
    strcpy(materials[2].name, "Wood");
    materials[2].weight       = 100.0f;
    materials[2].quantity     = 1;
    materials[2].loaded_units = 0;
}
