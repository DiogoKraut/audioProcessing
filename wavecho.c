/* DIOGO PARIS KRAUT - GRR20166365 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "wavaccess.h"
#include "wavTAD.h"
#include "parse.h"

void effect_echo(tWAV *w, tWAV *o, float level, int delay) {
	int i, echo;
	float x;
	// Garantir que 0.0 <= level <= 10.0
	if(level < 0)
		level = 0;
	else if(level > 10)
		level = 10;

	// Garantir que delay >= 0
	if(delay < 0)
		delay = 0;

	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;
	auxw = (short *)w->data;
	auxo = (short *)o->data;

	// Calcula quantas amostram teram entre o eco e a amostra atual
	echo  = round((delay / 1000.0) * w->header->sample_rate);

	// Offset para nao ecoar amostras de antes do inicio dos dados
	auxo += echo;
	auxw += echo;

	// Paralelizar aqui
	for(i = echo; i < w->header->subChunk2Size / 2; i++, auxw++, auxo++) {
		x = (level * *(auxw - echo)); // Amostra do delay * level

		if( ((int)*auxw + x) > MAX_INTERVAL )
			*auxo = MAX_INTERVAL;
		else if( ((int)*auxw + x) < MIN_INTERVAL )
			*auxo = MIN_INTERVAL;
		else
			*auxo = *auxw + x;
	}
}

int main(int argc, char * const *argv) {
	// Aloca estrutura para tratar entrada
	tOPT_ARGS *opts = malloc(sizeof(tOPT_ARGS));
	inicializaOPTS(opts);
	if(parseMain(argc, argv, "i:o:l:t:", opts)) exit(EXIT_FAILURE);

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

    readWavFile(&win, opts->INPUT_FILE);

	// Copia o cabecario e aloca espaco para dados em wout
	memcpy(wout->header, win->header, sizeof(tHeader));
	wout->data = realloc(wout->data, wout->header->subChunk2Size);

    effect_echo(win, wout, opts->LEVEL, opts->DELAY);

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
