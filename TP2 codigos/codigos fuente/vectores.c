#include "vectores.h"
#include "tipos.h"



typedef struct vector{
    size_t usado, pedido;
    int * datos;
} vector_t;
/*Destruye un vector creado por VECTOR_crear. Inicializa todos los punteros a NULL*/
void VECTOR_destruir(vector_t ** vector){
    if(vector != NULL && *vector != NULL){
        if((*vector)->datos != NULL){
            free((*vector)->datos);
            (*vector)->datos = NULL;
        }
        free(*vector);
        *vector = NULL;
    }   
}
/*Crea un TDA Vector con capacidad para n elementos*/
/*Retorna el estado de la operación por el nombre*/
vct_retval_t VECTOR_crear(vector_t ** vector, size_t n){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    if((*vector = (vector_t *)calloc(1, sizeof(vector_t))) == NULL)
        return VCT_RV_NOSPACE;
    if(((*vector)->datos = (int *)calloc(n, sizeof(int))) == NULL){
        VECTOR_destruir(vector);
        return VCT_RV_NOSPACE;
    }
    /*v->usado inicializado con calloc*/
    (*vector)->pedido = n;
    return VCT_RV_SUCCESS;
}
/*Redimensiona el vector de elementos del TDA Vector y modifica adecuadamente la memoria pedida*/
/*Retorna el estado de la operación por el nombre*/
vct_retval_t VECTOR_redimensionar(vector_t * vector, size_t n){
    int * aux;
    
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(n <= 0)
        return VCT_RV_INVALID_ARGS;
    
    if(n == vector->pedido)
        return VCT_RV_SUCCESS;

    aux = (int*)realloc(vector->datos, n * sizeof(int));
    if(aux == NULL)
    	return VCT_RV_NOSPACE;
    vector->datos = aux;

    vector->pedido = n;
    if(vector->usado > vector->pedido)
        vector->usado = vector->pedido;

    return VCT_RV_SUCCESS;
}
/*Guarda un dato entero en el TDA Vector pasado por puntero en la posición señalada (empieza a contar desde 1)*/
/*Retorna el estado de la operación por el nombre*/
vct_retval_t VECTOR_guardar_entero(vector_t * vector, size_t posicion, int dato){
    if(vector == NULL)
        return VCT_RV_ILLEGAL;
    if(posicion > vector->pedido || posicion < 1)
        return VCT_RV_INVALID_ARGS;
    
    (vector->datos)[posicion - 1] = dato;
    
    if(vector->usado < posicion)
        vector->usado = posicion;
    
    return VCT_RV_SUCCESS;  
}

/*Funciones para obtener los distintos parametros de un TDA Vector*/
int VECTOR_obtener_dato(vector_t * v, size_t i){
    return v->datos[i - 1];
}
int VECTOR_obtener_memoria_usada(vector_t * v){
    return v == NULL ? -1 : v->usado;
}
int VECTOR_obtener_memoria_pedida(vector_t * v){
    return v == NULL ? -1 : v->pedido;
}