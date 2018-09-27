#include "wavaccess.h"

void readHeader(tWAV *w, FILE *i) {
	// Le cabecario
	fread(w->header, sizeof(tHeader), 1, i);

	// Le dados
	// w->data = (int16_t *) malloc(w->header->subChunk2Size + sizeof(tHeader)); // Aloca espaco para dados
	// fseek(i, 0, SEEK_SET);
	// fread(w->data, sizeof(w->header->subChunk2Size + sizeof(tHeader)), 1, i);
}

void readData(tWAV *w, FILE *i) {
	fseek(i, 0, SEEK_SET);
	fread(w->data, sizeof(w->header->subChunk2Size + sizeof(tHeader)-1), 1, i);
}

void writeToWav(tWAV *w, FILE *o) {
	// Escreve cabecario
	//fwrite(w->header, sizeof(tHeader), 1, o);
	// Escreve dados
	fwrite(w->data, w->header->subChunk2Size + sizeof(tHeader), 1, o);

}
