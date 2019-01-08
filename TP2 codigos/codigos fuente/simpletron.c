#include "simpletron.h"
#include "tipos.h"
#include "comun.h"

static const pfx_lms instrucciones[] = {
    &lms_leer,
    &lms_escribir,
    &lms_cargar,
    &lms_guardar,
    &lms_pcargar,
    &lms_pguardar,
    &lms_sumar,
    &lms_restar,
    &lms_dividir,
    &lms_multiplicar,
    &lms_jmp,
    &lms_jmpneg,
    &lms_jmpzero,
    &lms_jnz,
    &lms_djnz,
    &lms_halt
};

static const palabra_t opcode_validos[] = {
    OP_LEER,
    OP_ESCRIBIR,
    OP_CARGAR,
    OP_GUARDAR,
    OP_PCARGAR,
    OP_PGUARDAR,
    OP_SUMAR,
    OP_RESTAR,
    OP_DIVIDIR,
    OP_MULTIPLICAR,
    OP_JMP,
    OP_JMPNEG,
    OP_JMPZERO,
    OP_JNZ,
    OP_DJNZ,
    OP_HALT
};

/*Retorna un booleano indicando si una palabra en formato txt (ej: +0110511) puede ser representado por 16bits
y respetar los rangos de los opcode y operandos*/
bool_t palabra_es_valida(palabra_t palabra){
    palabra_t operando;
    palabra_t opcode;
    
    if (palabra > MAX_PALABRA_TXT || palabra < MIN_PALABRA_TXT)
        return FALSE;
    operando = palabra < 0 ? -palabra % OPCODE_OPERANDO_MULTIPLIER : palabra % OPCODE_OPERANDO_MULTIPLIER;
    if (operando < OPERANDO_MIN || operando > OPERANDO_MAX)
        return FALSE;
    opcode = palabra / OPCODE_OPERANDO_MULTIPLIER;
    if (opcode < OPCODE_FIELD_MIN || opcode > OPCODE_FIELD_MAX)
        return FALSE;
    
    return TRUE;
}

/************************************************************************************************/
/*Me dan la representacion binaria de los op desplazados a la derecha. Por esto, siempre los toma positivos
 Si quisiera representarlos con signo, necesito hacer complemento a 2 manualmente*/


/*Obtiene el opcode de una palabra con un determinado formato que se indica por argumento*/
/*FMT_TXT : 	+0110511*/
/*FMT_BIN : 0110111  111110101*/
palabra_t get_opcode(palabra_t palabra, formato_t formato){
    return formato != FMT_TXT ? (palabra & MASK_OPCODE) >> OPCODE_SHIFT : palabra / OPCODE_OPERANDO_MULTIPLIER;
} 
/*Obtiene el operando de una palabra con un determinado formato que se indica por argumento*/
palabra_t get_operando(palabra_t palabra, formato_t formato){
	/*Esta condicion solo afecta a FMT_TXT, ya que un binario con 16bits dentro de un entero de 32bits (nuestro caso)
	nunca puede ser negativo*/
    if(palabra < 0)
        palabra = -palabra;
    return formato != FMT_TXT ? palabra & MASK_OPERANDO : palabra % OPCODE_OPERANDO_MULTIPLIER;
} 

/*Un opcode en FMT_BIN nunca puede ser negativo, uno FMT_TXT si puede. Si quisiera hacer un pasaje de formatos,
necesitaría que el FMT_BIN detecte el signo de forma que la conversioń sea la correcta*/

/*Esta funcipn me permite "forzar" un signo en bits que esten almacenados dentro de una variable de mayor tamaño que impide
que sean negativos*/
palabra_t aplicar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD ,palabra_t MSB){
    return palabra & MSB ? palabra | (~BIT_FIELD) : palabra;
    
}
/*Realiza la operación opuesta a aplicar_signo_palabra. Remueve el signo si tuviera uno, por lo que siempre se
obtiene algo positivo*/
palabra_t quitar_signo_palabra(palabra_t palabra, palabra_t BIT_FIELD){
    return palabra & BIT_FIELD;
}
/*Usando las funciones para operar con los signos, esta función permite cambiar entre el formato TXT y BIN
de una palabra*/
palabra_t cambiar_fmt_palabra(palabra_t palabra, formato_t actual){
    palabra_t operando;
    palabra_t opcode;
    
    opcode = get_opcode(palabra, actual);
    operando = get_operando(palabra, actual);
    
    switch(actual){
        case FMT_BIN: /*La palabra estaba almacenada en un entero con el formato binario y se quiere pasar al formato texto*/
            opcode = aplicar_signo_palabra(opcode, MASK_OPCODE >> OPCODE_SHIFT, MASK_MSB >> OPCODE_SHIFT);
            return opcode * OPCODE_OPERANDO_MULTIPLIER + (opcode >= 0 ? operando : -operando);
        case FMT_TXT:
        	/*Necesito eliminar el signo del opcode, antes de convertir la palabra*/
            opcode = quitar_signo_palabra(opcode, MASK_OPCODE >> OPCODE_SHIFT);
            return (( (int) 0 | opcode) << OPCODE_SHIFT) | operando;
        default:
            return palabra;
    }
}

/*Crea una instancia de simpletron y devuelve un puntero por el nombre*/
/*Inicializa todas las variables con calloc, retorna NULL en caso de error*/
simpletron_t * SIMPLETRON_crear(void){
    return (simpletron_t *)calloc(1,sizeof(simpletron_t));
}

/*Destruye una instancia de simpletron con su memoria*/
void SIMPLETRON_destruir(simpletron_t ** simply){
    if(simply != NULL && *simply != NULL){
        if((*simply)->memoria != NULL){
            VECTOR_destruir(&(*simply)->memoria);  
        }
        free(*simply);
        *simply = NULL;
    }
}

/*Ejecuta las instucciones de la memoria*/
simply_retval_t SIMPLETRON_ejecutar(simpletron_t * simply){
    size_t i;
    int memoria_pedida;
    simply_retval_t status;
    pfx_lms operacion;
    
    if(simply == NULL || simply->memoria == NULL)
        return SMP_RV_ILLEGAL;
    
    memoria_pedida = VECTOR_obtener_memoria_pedida(simply->memoria);

    for(; simply->program_counter < memoria_pedida; simply->program_counter++){
        /*Obtengo opcode y operandos*/
        simply->instruccion = VECTOR_obtener_dato(simply->memoria, simply->program_counter + 1);
        simply->opcode = get_opcode(simply->instruccion, FMT_BIN);
        simply->operando = get_operando(simply->instruccion, FMT_BIN);
        /*Valida que operando pueda ser accdedido*/
        if(simply->operando > memoria_pedida - 1 || simply->operando < 0){
            return SMP_RV_SEGMENTATION_FAULT;
        }
        /*Valido que los opcode sean validos*/  
        for(i = 0; simply->opcode != opcode_validos[i] && i < sizeof(opcode_validos)/sizeof(opcode_validos[0]) ; i++){
        }
        if(i == sizeof(opcode_validos)/sizeof(opcode_validos[0])){
            return SMP_RV_OPCODE_INVALIDO;
        }
        /*Ejecuta opcde*/
        operacion = instrucciones[i];
        status = (*operacion)(simply);
        if (status != SMP_RV_SUCCESS){
            if(status != SMP_RV_HALT){
                return status;
            }
            break;
        }
    }
    return SMP_RV_SUCCESS;
}

simply_retval_t lms_leer(simpletron_t * simpletron){
    char buffer[MAX_STR];
    palabra_t palabra;
    char * pch;
    
    fprintf(stdout,"%s ",MSJ_INGRESO_PALABRA);
    if(fgets(buffer, MAX_STR, stdin) == NULL){
        return SMP_RV_PALABRA_NO_LEIDA;
    }
    palabra = strtol(buffer, &pch, 10);
    /*Se valida que el numero pueda ser representado en 16bits con signo*/
    if (pch == NULL || (*pch != '\n' && *pch != '\0'))
        return SMP_RV_PALABRA_NO_ES_ENTERO;
    if(palabra > MAX_PALABRA_BIN_SIGNED || palabra < MIN_PALABRA_BIN_SIGNED)
        return SMP_RV_PALABRA_FUERA_DE_RANGO;
    
    palabra = quitar_signo_palabra(palabra, MASK_PALABRA);
    
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, palabra);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_escribir(simpletron_t * simpletron){
    palabra_t palabra;

    palabra = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    palabra = aplicar_signo_palabra(palabra, MASK_PALABRA, MASK_MSB);
    
    fprintf(stdout,"%s %i: %i\n", MSJ_IMPRIMIR_PALABRA, simpletron->operando, palabra);
    return SMP_RV_SUCCESS;
} 
simply_retval_t lms_cargar(simpletron_t * simpletron){
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_guardar(simpletron_t * simpletron){
    VECTOR_guardar_entero(simpletron->memoria, simpletron->operando + 1, simpletron->acumulador);
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pcargar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    simpletron->acumulador = VECTOR_obtener_dato(simpletron->memoria, puntero);

    return SMP_RV_SUCCESS;
}
simply_retval_t lms_pguardar(simpletron_t * simpletron){
    palabra_t puntero;
    /*Las funciones de TDA Vector empiezan a contar desde 1*/
    puntero = VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1) + 1;
    if(puntero > VECTOR_obtener_memoria_pedida(simpletron->memoria) || puntero < 1){
        return SMP_RV_SEGMENTATION_FAULT;
    }
    VECTOR_guardar_entero(simpletron->memoria, puntero, simpletron->acumulador);
    
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_sumar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador + VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_restar(simpletron_t * simpletron){
    palabra_t resultado;
    /*Si dejo que el programa reste normalmente, me llena de ceros a la izquierda
     Resto a nivel de bit, en el campo de la palabra*/
    resultado = simpletron->acumulador - VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    
    resultado = quitar_signo_palabra(resultado, MASK_PALABRA);

    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_dividir(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador / VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_multiplicar(simpletron_t * simpletron){
    palabra_t resultado;
    
    resultado = simpletron->acumulador * VECTOR_obtener_dato(simpletron->memoria, simpletron->operando + 1);
    if(resultado > MAX_PALABRA_BIN || resultado < MIN_PALABRA_BIN){
        return SMP_RV_OVERFLOW;
    }
    simpletron->acumulador = resultado;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmp(simpletron_t * simpletron){
    simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpneg(simpletron_t * simpletron){
    if(simpletron->acumulador & MASK_MSB)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jmpzero(simpletron_t * simpletron){
    if(!simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_jnz(simpletron_t * simpletron){
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_djnz(simpletron_t * simpletron){
    simpletron->acumulador--;
    if(simpletron->acumulador)
        simpletron->program_counter = simpletron->operando - 1;
    return SMP_RV_SUCCESS;
}
simply_retval_t lms_halt(simpletron_t * simpletron){
    return SMP_RV_HALT;
}