#ifndef LISTAS__H
#define LISTAS__H

#include "tipos.h"

typedef struct nodo nodo_t, *lista_t;
bool_t LISTA_esta_vacia(lista_t);
retval_t LISTA_crear(lista_t *);
retval_t LISTA_crear_nodo(nodo_t ** , void *);
retval_t LISTA_destruir_nodo(nodo_t **, retval_t (*destructor_dato)(void *));
retval_t LISTA_destruir(lista_t *, retval_t (*destructor_dato)(void *));
retval_t LISTA_insertar_al_ppio(lista_t *, void *);
retval_t LISTA_insertar_al_final(lista_t *, void *);
retval_t LISTA_insertar_decreciente(lista_t *, void *, int (*cmp)(void *, void *));

void * LISTA_buscar(nodo_t *, void *, int (*cmp)(void *, void *));
retval_t LISTA_imprimir(lista_t, FILE *, retval_t (*impresor)(void *, FILE *));
retval_t LISTA_recorrer(lista_t, retval_t (*pf)(void *, void *), void *);
retval_t LISTA_aplicar(lista_t, retval_t (*pf)(void*));

#endif