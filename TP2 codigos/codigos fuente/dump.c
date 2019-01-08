#include "dump.h"
#include <ctype.h>

/*Recibe una putnero a simpletron_t y un puntero a archivo_t
Imprime el dump proveniente de la primera estructura en el archivo de la segunda estructura.
Delega una tarea específica a otras funciones de acuerdo al formato del dump.
*/


void imprimir_dump(simpletron_t * simpletron, archivo_t * archivo_salida){
    switch(archivo_salida->formato){
        case FMT_TXT:
            imprimir_dump_txt(simpletron, archivo_salida->stream);
            return;
        case FMT_BIN:
            imprimir_dump_bin(simpletron, archivo_salida->stream);
            return;
    }
}


/*Imprime el dump en formato texto de la memoria de simpletron en el archivo abierto stream pasado como argumento
Le da formato de acuerdo a la especifiacion del programa simpletron*/
void imprimir_dump_txt(simpletron_t * simpletron, FILE * stream){
    size_t memoria_pedida;
    palabra_t instruccion_txt, opcode_txt, operando_txt;
    size_t palabras_hexa, salto_linea, memory_counter, palabras_char, blank_offset;
    size_t palabras_obtenidas;
    palabra_t palabra;
    int aux;
    

    instruccion_txt = cambiar_fmt_palabra(simpletron->instruccion, FMT_BIN);
    opcode_txt = get_opcode(instruccion_txt, FMT_TXT);
    operando_txt = get_operando(instruccion_txt, FMT_TXT);
    memoria_pedida = VECTOR_obtener_memoria_pedida(simpletron->memoria);
    
    fprintf(stream, "\n%s:\n", DUMP_MSJ_REGISTROS);
    fprintf(stream, "%15s:     %04X\n", DUMP_MSJ_ACUMULADOR, simpletron->acumulador);
    fprintf(stream, "%15s:%9ld\n", DUMP_MSJ_PROGRAM_COUNTER, simpletron->program_counter);
    fprintf(stream, "%15s: %+08d\n", DUMP_MSJ_INSTRUCCION, instruccion_txt);
    fprintf(stream, "%15s:%9d\n", DUMP_MSJ_OPCODE, opcode_txt);
    fprintf(stream, "%15s:      %03d\n", DUMP_MSJ_OPERANDO, operando_txt);
    fprintf(stream, "%s:", DUMP_MSJ_MEMORIA);

    for(memory_counter = 0, salto_linea = 0; memory_counter < memoria_pedida;){
	    fprintf(stream, "\n%02lx0:", salto_linea++);
	    for(palabras_hexa = 0, palabras_char = 0; palabras_hexa < PALABRAS_POR_LINEA; palabras_hexa++){
	    	if(palabras_hexa < PALABRAS_HEXA_POR_LINEA){
	    		palabras_obtenidas = palabras_hexa + 1;
	    		fprintf(stream, " %04X", VECTOR_obtener_dato(simpletron->memoria, memory_counter + 1));
	    		memory_counter++;
	    		if(memory_counter == memoria_pedida){
	    			palabras_hexa = PALABRAS_POR_LINEA - palabras_obtenidas - 1;
	    			for(blank_offset = PALABRAS_HEXA_POR_LINEA; blank_offset > palabras_obtenidas; blank_offset--){
	    				fprintf(stream, "%5c", ' ');
	    			}
	    		}
	    	}
	    	else{
	    		if(!palabras_char)
	    			fprintf(stream, "%3c", ' ');
	    		palabra = VECTOR_obtener_dato(simpletron->memoria, (memory_counter + palabras_char++ + 1) - palabras_obtenidas);
	    		aux = (palabra & MASK_HIGH_BYTE) >> MASK_HIGH_BYTE_SHIFT;
	    		isprint(aux) ? fprintf(stream, "%c", aux) : fprintf(stream, "%c", '.');
	    		aux = palabra & MASK_LOW_BYTE;
	    		isprint(aux) ? fprintf(stream, "%c", aux) : fprintf(stream, "%c", '.');
	    	}
	    }
	}
	
}
/*Imprime el dump em formato binario de la memoria en simpletron en el archivo abierto pasado como argumento*/
/*El dump se realiza de forma secuencial y binario, sin formato*/
void imprimir_dump_bin(simpletron_t * simpletron, FILE * stream){
    size_t i, memoria_pedida;
    palabra_t palabra;
    
    memoria_pedida = VECTOR_obtener_memoria_pedida(simpletron->memoria);

    for (i = 0; i < memoria_pedida; i++){
        palabra = VECTOR_obtener_dato(simpletron->memoria, i + 1);
        fwrite(&palabra,sizeof(palabra_t),1,stream);
    }
}