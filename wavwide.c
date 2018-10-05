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

    readWavFile(win, opts->INPUT_FILE);

	// Copia o cabecario e aloca espaco para dados em wout
	memcpy(wout->header, win->header, sizeof(tHeader));
	wout->data = malloc(wout->header->subChunk2Size);

    effect_wide(win, wout, opts->LEVEL);   // Aplica o efeito REV

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
