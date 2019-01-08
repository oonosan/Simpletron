#include <stdio.h>
#include <stdlib.h>
#include "argumentos.h"
#include "tipos.h"
#include "listas.h"
#include "simpletron.h"
#include "errores.h"
#include "dump.h"

int main(int argc, char** argv) {
    params_t argumentos;
    int status;
    size_t i;
    simpletron_t * simply;
    lista_t lista = NULL;

    if((status = validacion_cla(argc,argv, &argumentos)) != ST_OK){
    	imprimir_estado(status);
    	return EXIT_FAILURE;
    }
    if((status = abrir_archivos(&argumentos)) !=  ST_OK){
    	imprimir_estado(status);
    	destruir_params(&argumentos);
    	return EXIT_FAILURE;
    }
    for(i = 0; i < argumentos.cant_archivos; i++){
        if((simply = SIMPLETRON_crear()) == NULL){
        	imprimir_estado(SMP_RV_ERROR_MEMORIA);
        	cerrar_archivos(&argumentos);
        	destruir_params(&argumentos);
        	return EXIT_FAILURE;
        }
        if((status = leer_archivo(&simply->memoria, &argumentos.archivo_entrada[i], argumentos.cant_memoria)) != ST_OK){
        	imprimir_estado(status);
        	cerrar_archivos(&argumentos);
        	SIMPLETRON_destruir(&simply);
        	destruir_params(&argumentos);
        	return EXIT_FAILURE;
        }
        if((status = LISTA_insertar_al_final(&lista,simply)) != RV_SUCCESS){
        	imprimir_estado(status);
        	cerrar_archivos(&argumentos);
        	LISTA_destruir(&lista, (retval_t (*)(void*))SIMPLETRON_destruir);
        	destruir_params(&argumentos);
        	return EXIT_FAILURE;
        }
    }

    fprintf(stdout, "%s\n", MSJ_COMIENZO_EJECUCION);
    if((status = LISTA_aplicar(lista, (retval_t (*)(void*))SIMPLETRON_ejecutar)) != RV_SUCCESS){
    	fprintf(stdout, "%s\n", MSJ_FIN_EJECUCION);
    	imprimir_estado(status);
    	cerrar_archivos(&argumentos);
    	LISTA_destruir(&lista, (retval_t (*)(void*))SIMPLETRON_destruir);
    	destruir_params(&argumentos);
    	return EXIT_FAILURE;
    }
    fprintf(stdout, "%s\n", MSJ_FIN_EJECUCION);

    if((status = LISTA_recorrer(lista, (retval_t (*)(void*,void*))imprimir_dump, argumentos.archivo_salida)) != RV_SUCCESS){
    	imprimir_estado(status);
    	cerrar_archivos(&argumentos);
    	LISTA_destruir(&lista, (retval_t (*)(void*))SIMPLETRON_destruir);
    	destruir_params(&argumentos);
    	return EXIT_FAILURE;
    }
    cerrar_archivos(&argumentos);
    LISTA_destruir(&lista, (retval_t (*)(void*))SIMPLETRON_destruir);
    destruir_params(&argumentos);
	 
    return EXIT_SUCCESS;
}