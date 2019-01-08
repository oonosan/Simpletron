#include "tipos.h"
#include "argumentos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Recibe una los argumentos pasados por CLA, y un puntero a params_t
Valida todos los argumentos y los inicializa en la estrucutara de paramentros.
Retorna el estado de la operación por el nombre
*/

status_t validacion_cla(int argc, char** argv, params_t *param) {
    size_t i = 1, cant_archivos;
    bool_t stdin_flag = FALSE;
    long temp;
    archivo_t * aux = NULL;
    char * pc = NULL;
    /*---------------------------------VALIDACIONES---------------------------------*/
    if (argv == NULL || param == NULL)
        return ST_ERROR_PTR_NULO;

    /*-----------------------------DEFAULT-----------------------------*/
    param->cant_memoria = DEFAULT_MEMORIA;
    param->cant_archivos = DEFAULT_CANT_ARCHIVOS;
    if ((param->archivo_salida = (archivo_t*) malloc(sizeof (archivo_t))) == NULL)
        return ST_ERROR_MEMORIA;
    param->archivo_salida->formato = FMT_TXT;
    param->archivo_salida->nombre = DEFAULT_ARCHIVO_SALIDA;
    param->archivo_salida->stream = NULL;
    if ((param->archivo_entrada = (archivo_t*) malloc(sizeof (archivo_t))) == NULL){
        destruir_params(param);
        return ST_ERROR_MEMORIA;
    }
    param->archivo_entrada->formato = FMT_TXT;
    param->archivo_entrada->nombre = DEFAULT_ARCHIVO_ENTRADA;
    param->archivo_entrada->stream = NULL;

    /*Comienzo a recorrer argv[] hasta llegar a argv[argc]*/
    if(i == argc)
        return ST_OK;
    /*---------------------------------AYUDA---------------------------------*/
    /*Forma de ejecutar: ./simpletron -h o --help */
    if (argc == ARG_POS_AYUDA && (!strcmp(argv[i], FLAG_CLA_AYUDA_CORTO) || !strcmp(argv[i], FLAG_CLA_AYUDA_LARGO))){
        destruir_params(param);
        return ST_AYUDA;
    }
    /*---------------------------------MEMORIA---------------------------------*/
    if (!strcmp(argv[i], FLAG_CLA_MEMORIA_CORTO) || !strcmp(argv[i], FLAG_CLA_MEMORIA_LARGO)) {
        if(++i == argc){
            destruir_params(param);
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        }
        temp = strtol(argv[i], &pc, 10);
        /*En el caso de que el usuario ingrese caracter alfabetico o pida memoria con decimales*/
        if (temp <= 0 || pc == NULL || (*pc != '\n' && *pc != '\0')){
            destruir_params(param);
            return ST_ERROR_MEMORIA_INGRESADA_INVALIDA;
        }
        param->cant_memoria = temp;
        
        if(++i == argc)
            return ST_OK;
    }

    /*---------------------------------FORMATO SALIDA---------------------------------*/
    /*Indica el formato de la salida. Si FMT es txt , el formato debe ser texto. Si*/
    /*FMT es bin, el formato debe ser binario. Por omisión, el formato es texto.*/
    /*Busco el flag de formato*/
    if (!strcmp(argv[i], FLAG_CLA_FORMATO_CORTO) || !strcmp(argv[i], FLAG_CLA_FORMATO_LARGO)) {
        if(++i == argc){
            destruir_params(param);
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
        }
        if(!strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_BIN)){
            param->archivo_salida->formato = FMT_BIN;
        }
        else if(!strcmp(argv[i], FLAG_CLA_FORMATO_OPCION_TXT)){
            param->archivo_salida->formato = FMT_TXT;
        }
        else{
            destruir_params(param);
            return ST_ERROR_FORMATO_ARCHIVO_INVALIDO;
        }
        if(++i == argc)
            return ST_OK;
    }

    /*---------------------------------ARCHIVOS---------------------------------*/
    for (cant_archivos = 0; i < argc; i++){
        if ((aux = (archivo_t*) realloc(param->archivo_entrada, sizeof (archivo_t)*(++cant_archivos))) == NULL){
            destruir_params(param);
            return ST_ERROR_MEMORIA;
        }
        param->archivo_entrada = aux;
        param->archivo_entrada[cant_archivos - 1].nombre = get_name_lmsfile(argv[i]);
        param->archivo_entrada[cant_archivos - 1].formato = get_fmt_lmsfile(argv[i]);
        
        if(!stdin_flag && param->archivo_entrada[cant_archivos-1].nombre == NULL)
            stdin_flag = TRUE;
    }

    if (stdin_flag && (cant_archivos != 1 || param->archivo_entrada->formato == FMT_BIN)){
        destruir_params(param);
        return ST_ERROR_STDIN_INVALIDO;
    }
    param->cant_archivos = cant_archivos;
    
    return ST_OK;

/*Recibe una cadena de caracteres y devuelve el nombre del archivo correspodiente según las
especificaciones de los CLA
b:nombre t:nombre
*/
}
char * get_name_lmsfile(char* name){
    if(!strncmp(name, FMT_BIN_DELIMITER, FMT_DELIMITER_LENGTH) || !strncmp(name, FMT_TXT_DELIMITER, FMT_DELIMITER_LENGTH))
        return name + FMT_DELIMITER_LENGTH;
    if(!strcmp(name,FLAG_CLA_STDIN_CORTO))
        return NULL;
    return name;
}

/*Función análoga a la anterior para obtener los formatos. Recibe una cadena y la
decodifica para obtener su formato segun las especificaciones de los CLA
*/
formato_t get_fmt_lmsfile(char* name){
    return strncmp(name, FMT_BIN_DELIMITER, FMT_DELIMITER_LENGTH) ? FMT_TXT : FMT_BIN;
}

void destruir_params(params_t * param){
    if(param == NULL)
        return;
    free(param->archivo_entrada);
    free(param->archivo_salida);
    param->archivo_entrada = NULL;
    param->archivo_salida = NULL;
}