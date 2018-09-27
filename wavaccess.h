
#ifndef __ACCESS__
#define __ACCESS__

#include "wavTAD.h"
#include <stdio.h>
#include <stdlib.h>

void readHeader(tWAV *w, FILE *i);
void writeToWav(tWAV *w, FILE *o);
void readData(tWAV *w, FILE *i);

#endif