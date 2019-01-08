#include "listas.h"
#include "tipos.h"
#include <stdlib.h>

typedef struct nodo {
  struct nodo * siguiente;
  void * dato;
} nodo_t, * lista_t;


/*Retorna un booleando indicando si la lista está vacia*/
bool_t LISTA_esta_vacia(lista_t lista) {
    return lista == NULL;
}
/*Inicializa una lista vacía en el puntero plista recibido como argumento*/
retval_t LISTA_crear(lista_t * plista) {
    if(plista == NULL)
        return RV_ILLEGAL;

    *plista = NULL;

    return RV_SUCCESS;
}
/*Crea un nodo en el puntero pnodo pasado como argumento e inserta una dirección void* dato en el nodo*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_crear_nodo(nodo_t ** pnodo, void * dato) {
    if(pnodo == NULL)
        return RV_ILLEGAL;

    if((*pnodo = (nodo_t *)calloc(1, sizeof(nodo_t))) == NULL)
        return RV_NOSPACE;

    (*pnodo)->siguiente = NULL;
    (*pnodo)->dato = dato;

    return RV_SUCCESS;
}
/*Destruye un nodo apuntado por pnodo, liberando toda la memoria pedida y se le da un tratamiento especial
para liberar el contenido de puntero guardado en cada nodo.*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_destruir_nodo(nodo_t ** pnodo, retval_t (*destructor_dato)(void *)) {
    void * dato;

    if(pnodo == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*pnodo))
        return RV_SUCCESS;

    dato = (*pnodo)->dato;

    (*pnodo)->siguiente = NULL;
    (*pnodo)->dato = NULL;
    free(*pnodo);
    *pnodo = NULL;

    return (destructor_dato != NULL) ? (*destructor_dato)(&dato) : RV_SUCCESS;
}
/*Destruye el primer nodo de la lista y desplaza la lista hacia el siguiente elemento*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_destruir_primero(lista_t * plista, retval_t (*destructor_dato)(void *)) {
    nodo_t * primero;

    if(plista == NULL)
        return RV_ILLEGAL;

    if(*plista == NULL)/* es equivalente a LISTA_esta_vacia(*plista) */
        return RV_SUCCESS;

    primero = *plista;
    *plista = (*plista)->siguiente;

    return LISTA_destruir_nodo(&primero, destructor_dato);
}
/*Destruye todos los nodos de la listas, permitiendo realizar la destrucción del dato con una función aparte*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_destruir(lista_t * plista, retval_t (*destructor_dato)(void *)) {
    nodo_t * siguiente;
    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista))
        return RV_SUCCESS;

    siguiente = (*plista)->siguiente;

    LISTA_destruir_nodo(plista, destructor_dato );
    return LISTA_destruir(&siguiente, destructor_dato);
}
/*Inserta un nodo al prinicipio de la lista apuntada por plista, en la que se inserta void * dato*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_insertar_al_ppio(lista_t * plista, void * dato) {
    nodo_t * nuevo;
    retval_t rv;

    if(plista == NULL)
        return RV_ILLEGAL;

    if((rv = LISTA_crear_nodo(&nuevo, dato)) != RV_SUCCESS)
        return rv;

    nuevo->siguiente = *plista;
    *plista = nuevo;

    return RV_SUCCESS;
}
/*Inserta un nodo al final de la lista apuntada por plista, en la que se inserta void * dato*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_insertar_al_final(lista_t * plista, void * dato) {
    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista))
        return LISTA_insertar_al_ppio(plista, dato);

    return LISTA_insertar_al_final(&((*plista)->siguiente), dato);
}
/*Permite guardar void * datos en los nodos de forma ordenada, segun los criterios que utilice la funcion
*cmp pasada por argumento*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_insertar_decreciente(lista_t * plista, void * dato, int (*cmp)(void *, void *)) {
    retval_t rv;
    nodo_t * nuevo;

    if(plista == NULL)
        return RV_ILLEGAL;

    if(LISTA_esta_vacia(*plista) || (*cmp)( (*plista)->dato, dato) < 0 ) {
        if((rv = LISTA_crear_nodo(&nuevo, dato)) != RV_SUCCESS)
            return rv;

        nuevo->siguiente = *plista;
        *plista = nuevo;

        return RV_SUCCESS;
    }

    return LISTA_insertar_decreciente(&((*plista)->siguiente), dato, cmp);
}
/*Busca un void * t a lo largo de la lista pnodo. Para ello utiliza una función *es_igual
para poder realizar las comparaciones*/
/*Si lo encuentra, devuelve un puntero al dato, sino NULL*/
void * LISTA_buscar(lista_t pnodo, void * t, int (*es_igual)(void *, void *)) {
    if(pnodo == NULL)
        return NULL;

    if((*es_igual)(t, pnodo->dato))
        return pnodo->dato;

    return LISTA_buscar(pnodo->siguiente, t, es_igual);
}
/*Imprime una lista pnodo dentro del stream FILE * ofile usando la fucnion *impresor pasado como argumento*/
/*Retorna el estado de la operación por el nombre*/
retval_t LISTA_imprimir(lista_t pnodo, FILE * ofile, retval_t (*impresor)(void *, FILE *)) {
    if(pnodo == NULL)
        return RV_SUCCESS;

    (*impresor)(pnodo->dato, ofile);
    LISTA_imprimir(pnodo->siguiente, ofile, impresor);

    return RV_SUCCESS;
}
/*Itera sobre la lista, aplicando la función *funcion a cada elemento de cada nodo, se incluye un argumento
adicional para poder pasar a *funcion.
Retorna RV_SUCCESS si nunca hubo fallos. De lo contrario, retorna el estado de operación de funcion*/
retval_t LISTA_recorrer(lista_t pnodo, retval_t (*funcion)(void *, void *), void * argumento) {
    if(pnodo == NULL)
        return RV_SUCCESS;

    (*funcion)(pnodo->dato, argumento);
    return LISTA_recorrer(pnodo->siguiente, funcion, argumento);
}
/*Itera sobre la lista, aplicando la función *funcion a cada elemento de cada nodo*/
/*Retorna RV_SUCCESS si nunca hubo fallos. De lo contrario, retorna el estado de operación de *funcion*/
retval_t LISTA_aplicar(lista_t pnodo, retval_t (*funcion)(void*)){
	retval_t st;

    if(pnodo == NULL)
        return RV_SUCCESS;

    if((st = (*funcion)(pnodo->dato)) != RV_SUCCESS)
    	return st;
    return LISTA_aplicar(pnodo->siguiente, funcion);
}