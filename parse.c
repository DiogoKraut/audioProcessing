/* DIOGO PARIS KRAUT - GRR20166365 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parse.h"

int parseMain(int argc, char *const *argv, const char *options, tOPT_ARGS *o) {
	opterr = 0;
	int c, i, index;

	// Tratamento das opcoes de entrada
	while((c = getopt(argc, argv, "i:o:l:t:")) != -1) {
		switch(c) {
			case 'i':
				strcpy(o->INPUT_FILE, optarg);
				break;
			case 'o':
				strcpy(o->OUTPUT_FILE , optarg);
				break;
			case 'l':
				o->LEVEL = atof(optarg);
				break;
			case 't':
				o->DELAY = atoi(optarg);
				break;
			case '?':
				if (optopt == 'i' || optopt == 'o' || optopt == 'l' || optopt == 't')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				return 0;
			default:
				exit(EXIT_FAILURE);
		}
	}

	// Argumentos sem opcao nao devem ultrapassar MAX_INPUT_QNT
	if(argc <= MAX_INPUT_QNT) {
		// // Cria uma lista desses argumentos;
		for (index = optind, i = 0; index < argc; index++, i++) {
			strncpy(o->INPUT_LIST[i], argv[index], MAX_FILE_NAME);
			o->INPUT_LIST_SIZE++;
		}
		return 1;
	}
	fprintf(stderr, "Qnt de argumentos: %d Qnt maxima: %d\n", argc, MAX_INPUT_QNT);
	return 0;
}

void inicializaOPTS(tOPT_ARGS *opt) {
	strcpy(opt->INPUT_FILE, "");  // Inicializa com string nula
	strcpy(opt->OUTPUT_FILE, "");
	opt->LEVEL = 1;
	opt->DELAY = 1000;
	opt->INPUT_LIST_SIZE = 0;
}
