#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "train.h"


float recalc_wagon_weight(Wagon* wagon);


void save_train_to_file(const Train* train, const char* filename);

void load_train_from_file(Train* train, const char* filename);

#endif
