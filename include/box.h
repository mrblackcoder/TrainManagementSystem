#ifndef BOX_H
#define BOX_H

typedef enum {
    SMALL = 1,
    MEDIUM,
    LARGE
} BoxSize;



typedef struct Box {
    int box_id;
    float weight; 
    BoxSize size;
} Box;


Box* create_box(int box_id, BoxSize size);


void print_box(const Box* box);

#endif
