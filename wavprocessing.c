#include <stdlib.h>
#include "wavprocessing.h"
#include <stdio.h>

tWAV *effect_rev(tWAV *w) {
	// Saida com efeito rev
	tWAV *o = inicializaWAV();
	o->data = malloc(w->header->subChunk2Size/2);

	// Reverte w
	int i, j , tam;
	j = tam = w->header->subChunk2Size/2;

	for(i = 0; i < tam; i++, j--)
		o->data[i] = w->data[j];
	return o;
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
