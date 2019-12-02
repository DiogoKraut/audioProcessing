/* DIOGO PARIS KRAUT - GRR20166365 */

#include "wavTAD.h"

#define MAX_FILE_SZ 25 // Tamanho maximo do nome do arquivo de entrada

// Estrutura para tratar a entrada
typedef struct sOPT_ARGS {
	char  	  INPUT_FILE[MAX_FILE_SZ];
	float     LEVEL;
	char 	  OUTPUT_FILE[MAX_FILE_SZ];
	int       DELAY;
} tOPT_ARGS;

int parseMain(int argc, char *const *argv, const char *options, tOPT_ARGS *o);
void inicializaOPTS(tOPT_ARGS *opt);
