#include <stdlib.h>
#include "wavprocessing.h"
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

void effect_rev(tWAV *w, tWAV *o) {
	// Reverte w
	int i;
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data + (w->header->subChunk2Size / 2);

	for(i = 0; i < (w->header->subChunk2Size) / 2; i++, auxw++, auxo--)
		*auxo = *auxw;
}

void volAdjust(tWAV *w, tWAV *o, float level) {
	int i;

	// Garantir que 0.0 <= level <= 10.0
	if(level < 0)
	level = 0;
	else if(level > 10)
	level = 10;

	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data;

	for(i = 0; i < w->header->subChunk2Size / 2; i++, auxw++, auxo++) {
		// Aplica mudanca de volume mas nao permite OVERFLOW ou UNDERFLOW
		if(*auxw > MAX_INTERVAL / level)      // OVERFLOW
			*auxo = MAX_INTERVAL;
		else if(*auxw < MIN_INTERVAL / level) // UNDERFLOW
			*auxo = MIN_INTERVAL;
		else
			*auxo = *auxw * level;
	}

}

void effect_echo(tWAV *w, tWAV *o, float level, int delay) {
	int i, echo;
	float x;
	// Garantir que 0.0 <= level <= 10.0
	if(level < 0)
		level = 0;
	else if(level > 10)
		level = 10;

	// Garantir que delay >= 0
	if(delay < 0) delay = 0;

	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data;

	// Calcula quantas amostram teram entre o eco e a amostral atual
	echo  = round((delay / 1000.0) * w->header->sample_rate);
	auxo += echo;
	auxw += echo;

	for(i = 0; i < (w->header->subChunk2Size / 2) - echo; i++, auxw++, auxo++) {
		x = (level * *(auxw - echo)); // Amostra do delay * level
		if((x > 0) && (*auxw > MAX_INTERVAL - x))
			*auxo = MAX_INTERVAL;
		else if((x < 0) && (*auxw < MIN_INTERVAL - x))
			*auxo = MIN_INTERVAL;
		else
			*auxo = *auxw + x;

	}
}

void effect_wide(tWAV *w, tWAV *o, float level) {
	int i;
	float widening_factor;
	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data;

	// Se audio for estereo de 2 canais
	if(w->header->num_channels == 2) {
		// Para cada par de amostras (L & R) aplicar widening effect
		for(i = 0; i < w->header->subChunk2Size / 4; i++, auxw += 2, auxo += 2) {
			widening_factor = (*auxw - *(auxw + 1) * level); // k * diff

			// Verficacao de OVERFLOW e UNDERFLOW
			if((widening_factor > 0) && (*auxw > MAX_INTERVAL - widening_factor))
				*auxo = MAX_INTERVAL;
			else if((widening_factor < 0) && (*auxw < MIN_INTERVAL - widening_factor))
				*auxo = MIN_INTERVAL;
			else
				*auxo = *auxw + widening_factor;

			if((widening_factor < 0) && (*(auxw + 1) > MAX_INTERVAL + widening_factor))
				*(auxo + 1) = MAX_INTERVAL;
			else if((widening_factor > 0) && (*(auxw + 1) < MIN_INTERVAL + widening_factor))
				*(auxo + 1) = MIN_INTERVAL;
			else
				*(auxo + 1) = *(auxw + 1) - widening_factor;
		}
	}
}

int wavConcat(tWAV *w, tWAV *o) {
	// Apende os dados de o em w
	// Retorna 0 na falha ou 1 no sucesso
	if((w->header->sample_rate  != o->header->sample_rate) ||
	   (w->header->byte_rate    != o->header->byte_rate)   ||
	   (w->header->num_channels != o->header->num_channels))
		return 0;

	// Aloca espaco para concatenar
	o->data = realloc(o->data, sizeof(w->data) + sizeof(o->data));

	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data + w->header->subChunk2Size;

	int i;
	for(i = 0; i < w->header->subChunk2Size / 2; i++, auxw++, auxo++) {
		*auxo = *auxw;
	}

	o->header->subChunk2Size += w->header->subChunk2Size;
	return 1;
}

void effect_mix(tWAV *w, tWAV *o) {
	// Auxiliares para percorrer dados a cada 2 bytes
	short *auxw, *auxo;

	auxw = (short *)w->data;
	auxo = (short *)o->data;

	int i;
	for(i = 0; i < o->header->subChunk2Size && i < w->header->subChunk2Size; i++, auxw++, auxo++) {
		// Verificacao de OVERFLOW
		if((*auxo > 0) && (*auxo > MAX_INTERVAL - *auxw))
				*auxo = MAX_INTERVAL;
			else if((*auxo < 0) && (*auxo < MIN_INTERVAL - *auxw))
				*auxo = MIN_INTERVAL;
			else
				*auxo += *auxw;
	}
}

void printHeader(tWAV *w) {
	printf("riff tag       : %.4s\n"	   , w->header->chunkID);
	printf("riff size      : %" PRIu32 "\n", w->header->chunkSize);
	printf("wave tag       : %.4s\n"       , w->header->format);
	printf("form tag       : %.4s\n"       , w->header->subChunk1ID);
	printf("fmt_size       : %" PRIu32 "\n", w->header->subChunk1Size);
	printf("audio_format   : %" PRIu16 "\n", w->header->audio_format);
	printf("num_channels   : %" PRIu16 "\n", w->header->num_channels);
	printf("sample_rate    : %" PRIu32 "\n", w->header->sample_rate);
	printf("byte_rate      : %" PRIu32 "\n", w->header->byte_rate);
	printf("block_align    : %" PRIu16 "\n", w->header->block_align);
	printf("bits_per_sample: %" PRIu16 "\n", w->header->bits_per_sample);
	printf("data tag       : %.4s\n"       , w->header->subChunk2ID);
	printf("data size      : %" PRIu32 "\n", w->header->subChunk2Size);
	printf("samples/channel: %" PRIu32 "\n", w->header->subChunk2Size / w->header->block_align);

}
