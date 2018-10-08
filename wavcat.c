#include <stdio.h>
#include "wavaccess.h"
#include "wavTAD.h"
#include "wavprocessing.h"
#include "parse.h"

tWAV *win, *wout;

int main(int argc, char * const *argv) {
	// Aloca estrutura para tratar entrada
	tOPT_ARGS *opts = malloc(sizeof(tOPT_ARGS));

	if(!parseMain(argc, argv, "i:o:l:t:", opts)) abort();

	// Aloca espaco para os arquivos wav
    tWAV *win    = malloc(sizeof(tWAV));
	win->header  = malloc(sizeof(tHeader));
	win->data    = malloc(sizeof(int16_t));

    tWAV *wout   = malloc(sizeof(tWAV));
	wout->header = malloc(sizeof(tHeader));
	wout->data   = malloc(sizeof(int16_t));

	if(!win || !win->header || !wout || !wout->header || !win->data || !wout->data) {
		fprintf(stderr, "Falha na alocacao de tWAV\n");
		abort();
	}


	/* Inicio da concatenacao */
	int i;

    readWavFile(wout, opts->INPUT_LIST[i]); // Le o primeiro arv da lista

	for(i = 0; i < opts->INPUT_LIST_SIZE; i++) {
	    readWavFile(win, opts->INPUT_LIST[i]);
	    if(!wavConcat(win, wout))
	    	// Informa falha, mas continua para o proximo arquivo
	    	fprintf(stderr, "Falha ao concatenar o arquivo %s.\n", opts->INPUT_LIST[i]);
    }
    /* Fim da concatenacao */

    writeToWav(wout, opts->OUTPUT_FILE); // Escreve para arqv de saida

	// Free routine
	free(opts);

	free(win->data);
	free(win->header);
	free(win);

	free(wout->data);
	free(wout->header);
	free(wout);
	return 0;
}
