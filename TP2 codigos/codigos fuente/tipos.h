#ifndef TIPOS__H
#define TIPOS__H

#include <stdio.h>

typedef enum{
    FALSE = 0,
    TRUE
}bool_t;
typedef unsigned char uchar;
typedef enum{
	/*validacion de argumentos*/
	ST_AYUDA = -1,
    ST_OK = 0,
    ST_ERROR_STDIN_INVALIDO = 1,
    ST_ERROR_PTR_NULO = 2,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO = 3, 	/*Si falta por abrir algun archivo*/
    ST_ERROR_MEMORIA = 4,				/*No pudo alocar memoria*/
    ST_ERROR_MEMORIA_INGRESADA_INVALIDA = 5,
    ST_ERROR_FORMATO_ARCHIVO_INVALIDO = 6,
    /*lectura de archivos*/
    ST_ERROR_PALABRA_NO_VALIDA = 7,		/*Palabra no cumple con el formato txt para ingreso de codigo*/
    ST_ERROR_LEER_PALABRA = 8,			/*Error de lectura al procesar los datos fgets == NULL etc*/	
    ST_ERROR_MEMORIA_INSUFICIENTE = 9,	/*Memoria ingresada por consola*/
    ST_ERROR_VECTOR = 10 	/*Error al operar con TDA Vector*/
}status_t;
typedef enum{
    SMP_RV_SUCCESS = 0,
    SMP_RV_SEGMENTATION_FAULT = 11,
    SMP_RV_PALABRA_NO_LEIDA,
    SMP_RV_ERROR,
    SMP_RV_PALABRA_FORMATO_INVALIDO, /*La palabra en formato txt es invalida*/
    SMP_RV_PALABRA_FUERA_DE_RANGO,
    SMP_RV_PALABRA_NO_ES_ENTERO,
    SMP_RV_OVERFLOW,
    SMP_RV_OPCODE_INVALIDO,
    SMP_RV_ERROR_MEMORIA,
    SMP_RV_ILLEGAL,
    SMP_RV_HALT
} simply_retval_t;
typedef enum{
    VCT_RV_SUCCESS = 0,
    VCT_RV_ILLEGAL = 22,
    VCT_RV_NOSPACE,
    VCT_RV_ERROR,
    VCT_RV_NOTIMPLEMENTED,
    VCT_RV_MISSING_ARGS,
    VCT_RV_INVALID_ARGS
} vct_retval_t;
typedef enum{
    RV_SUCCESS = 0,
    RV_ILLEGAL = 28,
    RV_NOSPACE,
    RV_ERROR,
    RV_NOTIMPLEMENTED,
    RV_MISSING_ARGS,
    RV_INVALID_ARGS
} retval_t;
typedef enum{
    FMT_TXT,
    FMT_BIN        
} formato_t;
typedef struct archivo{
    char * nombre;
    formato_t formato;
    FILE * stream;
} archivo_t;

#endif