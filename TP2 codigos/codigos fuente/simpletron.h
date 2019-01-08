#ifndef SIMPLETRON__H
#define SIMPLETRON__H

#include "vectores.h"
#include "comun.h"
#include "lectores.h"
#include "idiomas.h"
#include <stdlib.h>

typedef int palabra_t;
typedef enum{
    OP_LEER = 10,
    OP_ESCRIBIR,
    OP_CARGAR = 20,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR = 30,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP = 40,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
}opcode_t;
typedef struct simpletron{
    palabra_t instruccion, acumulador, operando;
    opcode_t opcode;
    size_t program_counter;
    vector_t * memoria;
}simpletron_t;
typedef simply_retval_t (*pfx_lms)(simpletron_t *);
bool_t palabra_es_valida(palabra_t palabra);
palabra_t get_opcode(palabra_t palabra, formato_t formato);
palabra_t get_operando(palabra_t palabra, formato_t formato);
palabra_t aplicar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD, palabra_t MSB);
palabra_t quitar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD);
palabra_t cambiar_fmt_palabra(palabra_t palabra, formato_t destino);
simpletron_t * SIMPLETRON_crear(void);
void SIMPLETRON_destruir(simpletron_t ** simply);
simply_retval_t SIMPLETRON_ejecutar(simpletron_t * simpletron);
simply_retval_t lms_leer(simpletron_t * simpletron);
simply_retval_t lms_escribir(simpletron_t * simpletron);
simply_retval_t lms_cargar(simpletron_t * simpletron);
simply_retval_t lms_guardar(simpletron_t * simpletron);
simply_retval_t lms_pcargar(simpletron_t * simpletron);
simply_retval_t lms_pguardar(simpletron_t * simpletron);
simply_retval_t lms_sumar(simpletron_t * simpletron);
simply_retval_t lms_restar(simpletron_t * simpletron);
simply_retval_t lms_dividir(simpletron_t * simpletron);
simply_retval_t lms_multiplicar(simpletron_t * simpletron);
simply_retval_t lms_jmp(simpletron_t * simpletron);
simply_retval_t lms_jmpneg(simpletron_t * simpletron);
simply_retval_t lms_jmpzero(simpletron_t * simpletron);
simply_retval_t lms_jnz(simpletron_t * simpletron);
simply_retval_t lms_djnz(simpletron_t * simpletron);
simply_retval_t lms_halt(simpletron_t * simpletron);

#endif