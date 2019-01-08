#include "errores.h"
#include "tipos.h"


/*Función para imprimir el estado de las funciones utilizadas en el programa*/
void imprimir_estado(int status) {
	/*Utiliza un diccionario personal que selecciona de forma ordenada un mensaje para cada
	tipo de estado de las distintas funciones*/
    static const char *mensajes_errores[] = {
        MSJ_ST_OK,
        MSJ_ST_ERROR_STDIN_INVALIDO,
        MSJ_ST_ERROR_PTR_NULO,
        MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO,
        MSJ_ST_ERROR_MEMORIA,
        MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA,
        MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO,
        MSJ_ST_ERROR_PALABRA_NO_VALIDA,
        MSJ_ST_ERROR_LEER_PALABRA,
        MSJ_ST_ERROR_MEMORIA_INSUFICIENTE,
        MSJ_ST_ERROR_VECTOR,
        MSJ_SMP_RV_SEGMENTATION_FAULT,
        MSJ_SMP_RV_PALABRA_NO_LEIDA,
        MSJ_SMP_RV_ERROR,
        MSJ_SMP_RV_PALABRA_FORMATO_INVALIDO,
        MSJ_SMP_RV_PALABRA_FUERA_DE_RANGO,
        MSJ_SMP_RV_PALABRA_NO_ES_ENTERO,
        MSJ_SMP_RV_OVERFLOW,
        MSJ_SMP_RV_OPCODE_INVALIDO,
        MSJ_SMP_RV_ERROR_MEMORIA,
        MSJ_SMP_RV_ILLEGAL,
        MSJ_SMP_RV_HALT,
        MSJ_VCT_RV_ILLEGAL,
        MSJ_VCT_RV_NOSPACE,
        MSJ_VCT_RV_ERROR,
        MSJ_VCT_RV_NOTIMPLEMENTED,
        MSJ_VCT_RV_MISSING_ARGS,
        MSJ_VCT_RV_INVALID_ARGS,
        MSJ_RV_ILLEGAL,
        MSJ_RV_NOSPACE,
        MSJ_RV_ERROR,
        MSJ_RV_NOTIMPLEMENTED,
        MSJ_RV_MISSING_ARGS,
        MSJ_RV_INVALID_ARGS
    };

    if ((status == ST_AYUDA)) {
        imprimir_ayuda();
        return;
    }

    fprintf(stderr, "%s\n", mensajes_errores[status]);
}

void imprimir_ayuda(void) {
    fprintf(stdout, "%s\n", MSJ_AYUDA_PROTOTIPO);
    fprintf(stdout, "%s\n\n", MSJ_AYUDA_MEMORIA);
    fprintf(stdout, "%s\n\n", MSJ_AYUDA_FORMATO);
    fprintf(stdout, "%s\n\n", MSJ_AYUDA_ARCHIVOS);
}