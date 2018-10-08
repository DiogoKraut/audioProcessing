#ifndef __PROCESSING__
#define __PROCESSING__

#include "wavTAD.h"
#include <string.h>
#include <inttypes.h>

void effect_rev(tWAV *w, tWAV *o);
void printHeader(tWAV *w);
void volAdjust(tWAV *w, tWAV *o, float level);
void autoVolAdjust(tWAV *w, tWAV *o);
void effect_echo(tWAV *w, tWAV *o, float level, int delay);
void effect_wide(tWAV *w, tWAV *o, float level);
int safe_add(short *op1, short *op2, int limit);
int safe_mul(short *op1, float *op2, int limit);
int wavConcat(tWAV *w, tWAV *o);

#endif
