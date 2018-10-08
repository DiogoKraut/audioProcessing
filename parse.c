
#include "parse.h"

/* Tratamento da entrada baseado em
 * https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt
 */
int parseMain(int argc, char *const *argv, const char *options, tOPT_ARGS *o) {
	opterr = 0;
	int c, i, index;

	// Tratamento das opcoes de entrada
	while((c = getopt(argc, argv, "i:o:l:t:")) != -1)
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
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				return 0;
			default:
				abort();
		}

	// Argumentos sem opcao nao devem ultrapassar MAX_INPUT_QNT
	if(argc <= MAX_INPUT_QNT) {
		// // Cria uma lista desses argumentos;
		for (index = optind, i = 0; index < argc; index++, i++)
			strcpy(o->INPUT_LIST[i], argv[index]);
		return 1;
	}
	fprintf(stderr, "Qnt de argumentos: %d Qnt maxima: %d\n", argc, MAX_INPUT_QNT);
	return 0;
}

void inicializaOPTS(tOPT_ARGS *opt) {
	strcpy(opt->INPUT_FILE, "");  // Inicializa com string nula
	strcpy(opt->OUTPUT_FILE, "");
	opt->LEVEL = 1;
	opt->DELAY = 0;
	opt->INPUT_LIST_SIZE = 0;
}