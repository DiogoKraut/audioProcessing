/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include "wavaccess.h"
#include "wavTAD.h"
#include "wavprocessing.h"
#include "parse.h"

tWAV *win, *wout;

int main(int argc, char * const *argv) {
	// Aloca estrutura para tratar entrada
	tOPT_ARGS *opts = malloc(sizeof(tOPT_ARGS));
	inicializaOPTS(opts);
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

    readWavFile(&wout, opts->INPUT_LIST[0]); // Le o primeiro arqv da lista
	int16_t *tmp;
	for(i = 1; i < opts->INPUT_LIST_SIZE; i++) { // Para cada arqv da lista
	    readWavFile(&win, opts->INPUT_LIST[i]);  // Le este arquivo

		// Aloca espaco para concatenar e verifica alocacao
		tmp = realloc(wout->data, wout->header->subChunk2Size + win->header->subChunk2Size);
		if (tmp) {
		    wout->data = tmp;
		} else {
		    fprintf(stderr, "Falha ao realocar espaco para concatenar.\n");
			abort();
		}


	    if(!wavConcat(win, wout)) // Concatena no primeiro arqv
			fprintf(stderr, "Falha ao concatenar o arquivo %s.\n", opts->INPUT_LIST[i]);
	    	abort();
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
