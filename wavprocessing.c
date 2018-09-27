#include <stdlib.h>
#include "wavprocessing.h"
#include <stdio.h>

void effect_rev(tWAV *w, tWAV *o) {
	// Reverte w
	int i, j , tam;
	tam = j = w->header->subChunk2Size /4;
	j += sizeof(tHeader) / 4;

	for(i = 0; i < tam; i++, j--)
		o->data[i] = w->data[j];
}

tWAV *inicializaWAV() {
	tWAV *w = malloc(sizeof(tWAV));
	w->header = malloc(sizeof(tHeader));

	if(!w || !w->header) {
		fprintf(stderr, "Falha ao inicializar tWAV");
		return NULL;
	}
	return w;
}