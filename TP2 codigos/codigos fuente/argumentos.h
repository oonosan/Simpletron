#ifndef ARGUMENTOS__H
#define ARGUMENTOS__H

#include "tipos.h"

#define DEFAULT_MEMORIA 50
#define DEFAULT_CANT_ARCHIVOS 1
#define ARG_POS_AYUDA 2
#define FLAG_CLA_AYUDA_CORTO "-h"
#define FLAG_CLA_AYUDA_LARGO "--help"
#define FLAG_CLA_MEMORIA_CORTO "-m"
#define FLAG_CLA_MEMORIA_LARGO "--memoria"
#define FLAG_CLA_FORMATO_CORTO "-f"
#define FLAG_CLA_FORMATO_LARGO "--formato"
#define FLAG_CLA_STDIN_CORTO "-"
#define FLAG_CLA_FORMATO_OPCION_BIN "bin"
#define FLAG_CLA_FORMATO_OPCION_TXT "txt"
#define DEFAULT_ARCHIVO_SALIDA "dump"
#define DEFAULT_ARCHIVO_ENTRADA NULL
#define FMT_DELIMITER_LENGTH 2
#define FMT_BIN_DELIMITER "b:"
#define FMT_TXT_DELIMITER "t:"
typedef struct param{
    size_t cant_memoria;
    size_t cant_archivos;
    archivo_t * archivo_salida;
    archivo_t * archivo_entrada;
}params_t;
status_t validacion_cla(int argc, char** argv, params_t *param);
char * get_name_lmsfile(char* name);
formato_t get_fmt_lmsfile(char* name);
void destruir_params(params_t * param);

#endif