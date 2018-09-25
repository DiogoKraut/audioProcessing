#include <stdlib.h>

tWAV *effect_rev(tWAV *i) {
	// Saida com efeito rev
	tWAV *o = inicializaWAV();
	o->data = malloc(i->header.subChunk2Size);

	// Reverte i
	int i, j = tam = i->header.subChunk2Size;
	for(i = 0; i < tam; i++, j--)
		o->data[i] = i->data[j];
	return o;
}

tWAV *inicializaWAV() {
	tWAV *w = malloc(sizeof(tWAV));
	w->header = malloc(sizeof(tHeader));

	if(!w || !w->header) {
		printf(stderr, "Falha ao inicializar tWAV");
		return NULL;
	}
	return w;
}