#ifndef __PROCESSING__
#define __PROCESSING__

#include "wavTAD.h"
#include <string.h>
#include <inttypes.h>

void effect_rev(tWAV *w, tWAV *o);
void printHeader(tWAV *w);
void volAdjust(tWAV *w, tWAV *o, float level);
void autoVolAdjust(tWAV *w, tWAV *o);
void effect_echo(tWAV *w, tWAV *o, float level, int delay, int nthreads);
void effect_wide(tWAV *w, tWAV *o, float level);
int wavConcat(tWAV *w, tWAV *o);
void effect_mix(tWAV *w, tWAV *o);

#endif
