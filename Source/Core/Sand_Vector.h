//
// Created by frazor on 26/07/2020.
//

#ifndef SAND_ROGUE_SAND_VECTOR_H
#define SAND_ROGUE_SAND_VECTOR_H

#include "Source/Common.h"



void Vector_Init(
    Vector *vector
);

void Vector_Append(
    Vector *vector,
    int value
);

//void Vector_Prepend(Vector *vector, int value);

//void Vector_Delete(
//    Vector *vector,
//    int index
//);

//void Vector_Delete_Value(Vector *vector, int value);
//void Vector_Set(Vector *vector, int index, int value);

void Vector_Resize(
    Vector *vector
);

void Vector_Free_Memory(
    Vector *vector
);

int Vector_Get(
    Vector *vector, int value
);

//int Vector_Pop(Vector *vector);
//int Vector_Find_Value(Vector *vector, int value);

int Vector_Size(
    Vector *vector
);

//int Vector_Capacity(Vector *vector);
//bool Vector_Is_Empty(Vector *vector);

#endif //SAND_ROGUE_SAND_VECTOR_H
