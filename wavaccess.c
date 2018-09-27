#include "wavaccess.h"

void readWavFile(tWAV *w, FILE *i) {
	int j;
	// Le cabecario
	fread(w->header, sizeof(tHeader), 1, i);

	// Le dados
	w->data = malloc(w->header->subChunk2Size); // Aloca espaco para dados
	//printf("%lu", sizeof(w->data));
	for(j = 0; j < w->header->subChunk2Size; j++) {
		fread(&w->data[j], 1, 1, i);
	}
}

void writeToWav(tWAV *w, FILE *o) {
	// Escreve cabecario
	fwrite(w->header, sizeof(tHeader), 1, o);
	// Escreve dados
	fread(w->data, w->header->subChunk2Size, 1, o);

}
