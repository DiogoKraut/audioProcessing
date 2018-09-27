#include "wavaccess.h"
#include "wavTAD.h"
#include <stdio.h>
#include "wavprocessing.h"

int main(void) {
    FILE *i = fopen("./adele.wav", "r+");
    FILE *o = fopen("./o.wav", "w+");

    tWAV *w = inicializaWAV();
    tWAV *x = inicializaWAV();

    readWavFile(w, i);
    x = effect_rev(w);
    writeToWav(x, o);


}
