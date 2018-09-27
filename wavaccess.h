#ifndef __ACCESS__
#define __ACCESS__

#include "wavTAD.h"
#include <stdio.h>
#include <stdlib.h>

void readWavFile(tWAV *w, FILE *i) {
	// Le cabecario
	fread(w->header, sizeof(tHeader), 1, i);

	// Le dados
	w->data = malloc(w->header->subChunk2Size); // Aloca espaco para dados
	fread(w->data, w->header->subChunk2Size, 1, i);
}

void writeToWav(tWAV *w, FILE *o) {
	// Escreve cabecario
	fwrite(w->header, sizeof(tHeader), 1, o);
	// Escreve dados
	fread(w->data, w->header->subChunk2Size, 1, o);

}

#endif
