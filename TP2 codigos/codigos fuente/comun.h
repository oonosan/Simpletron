#ifndef COMUN__H
#define COMUN__H

/*Se utilizan estás variables en "comun.h" ya que las utilizan distintos módulos de simpletron para
realizar operaciones con palabras y conversiones de formato de texto a formato binario. eg -10511 = FFFF.
En particular se las escribe en formato decimal porque con ellas se realizar cuentas aritmeticas con el formato
TXT de las palabras
*/
#define MAX_STR 200
#define NUMERO_FIN_CARGA -99999999
#define MIN_PALABRA_TXT -640511
#define MAX_PALABRA_TXT 630511
#define MIN_PALABRA_BIN 0
#define MAX_PALABRA_BIN 65535
#define MIN_PALABRA_BIN_SIGNED -32768
#define MAX_PALABRA_BIN_SIGNED 32767
#define OPCODE_OPERANDO_MULTIPLIER 10000
#define OPERANDO_MIN 0
#define OPERANDO_MAX 511
#define OPCODE_MIN 0
#define OPCODE_MAX 127
#define OPCODE_FIELD_MIN -64
#define OPCODE_FIELD_MAX 63

#endif