#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "wavTAD.h"

#define MAX_INPUT_QNT 15 // Numero maximo de arqvs wav que podem ser passados

typedef char FILE_NAME[MAX_FILE_NAME]; // Nome de um arquivo eh uma string de tamanho MAX_FILE_NAME

// Estrutura para tratar a entrada
typedef struct sOPT_ARGS {
	char  	  INPUT_FILE[MAX_FILE_NAME];
	char 	  OUTPUT_FILE[MAX_FILE_NAME];
	float     LEVEL;
	int       DELAY;
	FILE_NAME INPUT_LIST[MAX_INPUT_QNT]; // Lista de arquivos da entrada
	int INPUT_LIST_SIZE;
} tOPT_ARGS;

int parseMain(int argc, char *const *argv, const char *options, tOPT_ARGS *o);
void inicializaOPTS(tOPT_ARGS *opt);