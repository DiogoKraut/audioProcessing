/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include "wavaccess.h"
#include "wavTAD.h"
#include "wavprocessing.h"
#include "parse.h"

tWAV *win;
int main(int argc, char * const *argv) {
	// Aloca estrutura para tratar entrada
	tOPT_ARGS *opts = malloc(sizeof(tOPT_ARGS));
	inicializaOPTS(opts);
	if(!parseMain(argc, argv, "i:o:l:t:", opts)) abort();

	// Aloca espaco para os arquivos wav
    tWAV *win    = malloc(sizeof(tWAV));
	win->header  = malloc(sizeof(tHeader));
	win->data    = malloc(sizeof(int16_t));

	if(!win || !win->header || !win->data) {
		fprintf(stderr, "Falha na alocacao de tWAV\n");
		abort();
	}

    readWavFile(&win, opts->INPUT_FILE);

	printHeader(win);

	// Free routine
	free(opts);

	free(win->data);
	free(win->header);
	free(win);

	return 0;
}
