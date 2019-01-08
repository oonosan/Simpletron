#ifndef VECTORES__H
#define VECTORES__H

#include "tipos.h"
#include <stdlib.h>

typedef struct vector vector_t;
void VECTOR_destruir(vector_t ** vector);
vct_retval_t VECTOR_crear(vector_t ** vector, size_t n);
vct_retval_t VECTOR_redimensionar(vector_t * vector, size_t n);
vct_retval_t VECTOR_guardar_entero(vector_t * vector, size_t posicion, int dato);
int VECTOR_obtener_dato(vector_t * v, size_t i);
int VECTOR_obtener_memoria_usada(vector_t * v);
int VECTOR_obtener_memoria_pedida(vector_t * v);

#endif