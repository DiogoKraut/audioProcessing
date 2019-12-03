#include <stdio.h>
#include <stdlib.h>
#include "wavaccess.h"

void readWavFile(tWAV **w, char *i) {
	FILE *fp;
	if(*i == '\0')
		fp = stdin;
	else
		fp = fopen(i, "r+");

	fread((*w)->header, sizeof(tHeader), 1, fp);
	(*w)->data = realloc((*w)->data, (*w)->header->subChunk2Size);

	// Paralelizar aqui
	fread((*w)->data, (*w)->header->subChunk2Size, 1, fp);

	fclose(fp);
}

void writeToWav(tWAV *w, char *i) {
	FILE *fp;
	if(*i == '\0')
		fp = stdout;
	else
		fp = fopen(i, "w+");

	fwrite(w->header, sizeof(tHeader), 1, fp);
	fwrite(w->data, w->header->subChunk2Size, 1, fp);

	fclose(fp);
}
