//
// Created by frazor on 26/07/2020.
//

#ifndef SAND_ROGUE_SAND_VECTOR_H
#define SAND_ROGUE_SAND_VECTOR_H

#include "Source/Common.h"



void Vector_init(Vector *vector);
void Vector_append(Vector *vector, int value);
void Vector_prepend(Vector *vector, int value);
void Vector_delete(Vector *vector, int index);
void Vector_delete_value(Vector *vector, int value);
void Vector_set(Vector *vector, int index, int value);
void Vector_resize(Vector *vector);
void Vector_free_memory(Vector *vector);

int Vector_get(Vector *vector, int value);
int Vector_pop(Vector *vector);
int Vector_find_value(Vector *vector, int value);
int Vector_size(Vector *vector);
int Vector_capacity(Vector *vector);

bool Vector_is_empty(Vector *vector);


#endif //SAND_ROGUE_SAND_VECTOR_H
