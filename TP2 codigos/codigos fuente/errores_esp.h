#ifndef ERRORES_ESP__H
#define ERRORES_ESP__H

/*Mensajes de ayuda*/
#define MSJ_AYUDA_PROTOTIPO "Prototipo de ejecucion: .\\simpletron -m N -f FMT [Archivo1 Archivo2 Archivo3...]"
#define MSJ_AYUDA_MEMORIA "MEMORIA:\n -m N:\t -m es el flag indicador de memoria y N debe ser un numero entero. No es obligatorio su ingreso. En caso de no ingresarse N sera 50"
#define MSJ_AYUDA_FORMATO "FORMATO:\n-f FMT:\t -f es el flag indicador del formato de salida donde FMT debe ser TXT o BIN. No es obligatorio su ingreso. Por default sera TXT"
#define MSJ_AYUDA_ARCHIVOS "ARCHIVOS:\n Los nombres de archivo de entrada deberan estar antecedidos por 't:' o 'b:' si el archivo debera leerse como un archivo de texto o un archivo binario respectivamente. En caso de omiterse esta especificacion, el archivo sera leido como un archivo de texto. En caso de que no se ingresen nombres de archivos, la entrada de datos sera por stdin"
#define MSJ_OPCION_AYUDA "Ingrese: .\\simpletron -h o .\\simpletron --help para mas informacion."
/*Validacion de argumentos*/
#define MSJ_ST_OK "La operación finalizó correctamente"
#define MSJ_ST_ERROR_STDIN_INVALIDO "El ingreso de archivos multiples junto con stdin no está soportado"
#define MSJ_ST_ERROR_PTR_NULO "Error: puntero nulo"
#define MSJ_ST_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo ingresado no se encuentra"
#define MSJ_ST_ERROR_MEMORIA "No se hayó memoria suficiente para la operación"
#define MSJ_ST_ERROR_MEMORIA_INGRESADA_INVALIDA "La memoria ingresada no es valida, la misma debe ser un entero positivo"
#define MSJ_ST_ERROR_FORMATO_ARCHIVO_INVALIDO "El formato de archivo de salida no es valido"
#define MSJ_ST_ERROR_PALABRA_NO_VALIDA "La palabra ingresada no es valida"
/*lectura de archivos*/
#define MSJ_ST_ERROR_LEER_PALABRA "Ocurrio un error durante la lectura de la palabra"
#define MSJ_ST_ERROR_MEMORIA_INSUFICIENTE "Se superó la memoria solicitada para el simpletron"
#define MSJ_ST_ERROR_VECTOR "Ocurrio un error al operar con los vectores"
/*simpletron*/
#define MSJ_SMP_RV_SUCCESS "La operación finalizó correctamente"
#define MSJ_SMP_RV_SEGMENTATION_FAULT "Se trató de acceder a memoria restringida durante la ejecución"
#define MSJ_SMP_RV_PALABRA_NO_LEIDA "Ocurrio un error durante la lectura de la palabra"
#define MSJ_SMP_RV_ERROR "Error"
#define MSJ_SMP_RV_PALABRA_FORMATO_INVALIDO "Se trató de operar con una palabra no soportada por la simpletron"
#define MSJ_SMP_RV_PALABRA_FUERA_DE_RANGO "Se trató de operar con una palabra fuera del rango aceptado por la simpletron"
#define MSJ_SMP_RV_PALABRA_NO_ES_ENTERO "Se trató de operar con una palabra que no es entero"
#define MSJ_SMP_RV_OVERFLOW "Se trató de operar con un rango de números no soportados por la máquina"
#define MSJ_SMP_RV_OPCODE_INVALIDO "Se trató de ejecutar una instrucción no especificada en el lenguaje"
#define MSJ_SMP_RV_ERROR_MEMORIA "No se hayó memoria suficiente para la operación"
#define MSJ_SMP_RV_ILLEGAL "Error: puntero nulo"
#define MSJ_SMP_RV_HALT "Finalizó la ejecución del archivo"
/*TDA vector*/
#define MSJ_VCT_RV_SUCCESS "La operación finalizó correctamente"
#define MSJ_VCT_RV_ILLEGAL "Error: puntero nulo"
#define MSJ_VCT_RV_NOSPACE  "No se hayó memoria suficiente para la operación"
#define MSJ_VCT_RV_ERROR "Error"
#define MSJ_VCT_RV_NOTIMPLEMENTED "Operación no implementada"
#define MSJ_VCT_RV_MISSING_ARGS "Faltan argumentos para realizar la operación"
#define MSJ_VCT_RV_INVALID_ARGS "Se enviaron argumentos invalidos para la operación"
/*TDA Lista*/
#define MSJ_RV_SUCCESS "La operación finalizó correctamente"
#define MSJ_RV_ILLEGAL "Error: puntero nulo"
#define MSJ_RV_NOSPACE "No se hayó memoria suficiente para la operación"
#define MSJ_RV_ERROR "Error"
#define MSJ_RV_NOTIMPLEMENTED "Operación no implementada"
#define MSJ_RV_MISSING_ARGS "Faltan argumentos para realizar la operación"
#define MSJ_RV_INVALID_ARGS "Se enviaron argumentos invalidos para la operación"
#endif /* ERRORES_ESP_H */

