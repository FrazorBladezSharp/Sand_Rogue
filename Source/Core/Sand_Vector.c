//
// Created by frazor on 26/07/2020.
//

#include "Sand_Vector.h"

void Vector_Init(Vector *vector){
    vector->size = 0;
    vector->capacity = VECTOR_INITIAL_CAPACITY;
    vector->data = (int*) malloc(sizeof(int) * vector->capacity);
}

int Vector_Get(Vector *vector, int index){
    if(index > vector->capacity || index < 0){
        printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
        exit(1);
    }

    return vector->data[index];
}

//void Vector_Set(Vector *vector, int index, int value){
//    while(index >= vector->size){
//        Vector_append(vector, 0);
//    }
//
//    vector->data[index] = value;
//}

void Vector_Append(Vector *vector, int value){
    Vector_Resize(vector);

    vector->data[vector->size++] = value;
}

//void Vector_Prepend(Vector *vector, int value){
//    Vector_set(vector, 0, value);
//    vector->size++;
//}
//
//int Vector_Pop(Vector *vector){
//    int data = vector->data[vector->size - 2];
//    Vector_set(vector, vector->size - 1, 0);
//    vector->size = vector->size - 1;
//    return data;
//}

void Vector_Delete(Vector *vector, int index){
    for(int i = 0; i < index; i++){
        vector->data[index + i] = vector->data[index + i + 1];
    }
    vector->size = vector->size - 1;
}

void Vector_Delete_Value(Vector *vector, int value){
    for(int i = 0; i < vector->size; i++){
        if(vector->data[i] == value){
            Vector_Delete(vector, i);
        }
    }
}

int Vector_Find_Value(Vector *vector, int value){
    for(int i = 0; i < vector->size; i++){
        if(vector->data[i] == value){
            return i;
        }
    }

    return -1;
}

void Vector_Resize(Vector *vector){
    if(vector->size >= vector->capacity){
        vector->capacity *= 2;
        vector->data = (int*) realloc(vector->data, sizeof(int) * vector->capacity);
    }
}

int Vector_Size(Vector *vector){
    return vector->size;
}

//int Vector_Capacity(Vector *vector){
//    return vector->capacity;
//}
//
//bool Vector_Is_Empty(Vector *vector){
//    return vector->size == 0;
//}

void Vector_Free_Memory(Vector *vector) {
    free(vector->data);
}

