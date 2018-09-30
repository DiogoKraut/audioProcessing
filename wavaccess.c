#include "wavaccess.h"

void readWavFile(tWAV *w, char *i) {
	if(*i == '\0') {
		fread(w->header, sizeof(tHeader), 1, stdin);
		w->data = (int16_t *)realloc(w->data, w->header->subChunk2Size);
		fread(w->data, w->header->subChunk2Size, 1, stdin);
	} else {
		FILE *in = fopen(i, "r+");

		fread(w->header, sizeof(tHeader), 1, in);
		w->data = (int16_t *)realloc(w->data, w->header->subChunk2Size);
		fread(w->data, w->header->subChunk2Size, 1, in);

		fclose(in);
	}
}

void writeToWav(tWAV *w, char *o) {
	if(*o == '\0') {
		fwrite(w->header, sizeof(tHeader), 1, stdout);
		fwrite(w->data, w->header->subChunk2Size, 1, stdout);
	} else {
		FILE *out = fopen(o, "w+");

		fwrite(w->header, sizeof(tHeader), 1, out);
		fwrite(w->data, w->header->subChunk2Size, 1, out);

		fclose(out);
	}
}
