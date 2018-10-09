/* DIOGO PARIS KRAUT - GRR20166365 */

#include "wavaccess.h"

void readWavFile(tWAV **w, char *i) {
	if(*i == '\0') { // arquivo de entrada nao especificado, usar stdin
		fread((*w)->header, sizeof(tHeader), 1, stdin);
		(*w)->data = realloc((*w)->data, (*w)->header->subChunk2Size);
		fread((*w)->data, (*w)->header->subChunk2Size, 1, stdin);
	} else {
		FILE *in = fopen(i, "r+");

		fread((*w)->header, sizeof(tHeader), 1, in);
		(*w)->data = realloc((*w)->data, (*w)->header->subChunk2Size);
		fread((*w)->data, (*w)->header->subChunk2Size, 1, in);

		fclose(in);
	}
}

void writeToWav(tWAV *w, char *o) {
	if(*o == '\0') { // arquivo de saida nao especificado, usar stdout
		fwrite(w->header, sizeof(tHeader), 1, stdout);
		fwrite(w->data, w->header->subChunk2Size, 1, stdout);
	} else {
		FILE *out = fopen(o, "w+");

		fwrite(w->header, sizeof(tHeader), 1, out);
		fwrite(w->data, w->header->subChunk2Size, 1, out);

		fclose(out);
	}
}
