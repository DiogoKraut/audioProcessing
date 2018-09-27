#include "wavaccess.h"
#include "wavTAD.h"
#include <stdio.h>
#include "wavprocessing.h"

tWAV *w, *x;

int main(void) {
    FILE *i = fopen("./adele.wav", "r+");
    FILE *o = fopen("./o.wav", "w+");

    tWAV *w   = malloc(sizeof(tWAV));
	w->header = malloc(sizeof(tHeader));


    tWAV *x   = malloc(sizeof(tWAV));
	x->header = malloc(sizeof(tHeader));

    readHeader(w, i);

    w->data = (int16_t *) malloc(w->header->subChunk2Size + sizeof(tHeader));
    x->data = (int16_t *) malloc(w->header->subChunk2Size);

    readData(w, i);
    effect_rev(w, x);

    writeToWav(x, o);

}
