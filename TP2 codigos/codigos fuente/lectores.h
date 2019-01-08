#ifndef LECTORES__H
#define LECTORES__H

#include "tipos.h"
#include "argumentos.h"
#include "vectores.h"

#define MASK_PALABRA 0xFFFF
#define MASK_OPERANDO 0x01FF
#define MASK_OPCODE 0xFE00
#define BYTE_SHIFT 8
#define OPCODE_SHIFT 9
#define MASK_MSB 0x8000
#define MASK_LSB 0x0001



#define BYTE_SIZE 1
#define BYTE_CANT_HIGHT_LOW 1
#define DELIMITADOR_COMENTARIO ";"

status_t abrir_archivos(params_t * param);
void cerrar_archivos(params_t * param);
status_t leer_archivo(vector_t ** memoria, archivo_t * archivo, size_t cantidad);
status_t leer_archivo_txt(vector_t ** memoria, FILE * stream, size_t cantidad);
status_t leer_archivo_bin(vector_t ** memoria, FILE * stream, size_t cantidad);
status_t leer_archivo_stdin(vector_t ** memoria, size_t cantidad);

#endif