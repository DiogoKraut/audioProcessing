#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "utils.h"
#include "wavprocessing.h"

void effect_rev(tWAV *w, tWAV *o) {
    // Reverte w
    int i;
    // Auxiliares para percorrer dados a cada 2 bytes
    short *auxw, *auxo;
    auxw = (short *)w->data;
    auxo = (short *)o->data + (w->header->subChunk2Size / 2); // Comeca na ultima posicao

    // Reverte os dados
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
        // Aplica mudanca de volume
        if( ((int)*auxw * level) > MAX_INTERVAL)
            *auxo = MAX_INTERVAL;
        else if( ((int)*auxw * level) < MIN_INTERVAL)
            *auxo = MIN_INTERVAL;
        else
            *auxo = *auxw * level;
    }

}

void effect_echo(tWAV *w, tWAV *o, float level, int delay,int nthreads) {
    int i, echo;
    float x;
    double t1;
    // Garantir que 0.0 <= level <= 10.0
    if(level < 0)
        level = 0;
    else if(level > 10)
        level = 10;

    // Garantir que delay >= 0
    if(delay < 0)
        delay = 0;

    // Auxiliares para percorrer dados a cada 2 bytes
    short *auxw, *auxo;
    auxw = (short *)w->data;
    auxo = (short *)o->data;

    // Calcula quantas amostram teram entre o eco e a amostra atual
    echo  = round((delay / 1000.0) * w->header->sample_rate);

    // Paralelizar aqui
    t1 = timestamp();
    #pragma omp parallel for default(shared) private(x) num_threads(nthreads)
        for(i = echo; i < w->header->subChunk2Size / 2; i++) {
            x = (level * (auxw[i-echo])); // Amostra do delay * level
            if( ((int)auxw[i] + x) > MAX_INTERVAL )
                auxo[i] = MAX_INTERVAL;
            else if( ((int)auxw[i] + x) < MIN_INTERVAL )
                auxo[i] = MIN_INTERVAL;
            else
                auxo[i] = auxw[i] + x;
        }
    t1 = timestamp()-t1;
    printf("%lf\n", t1);
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

            if( ((int)*auxw + widening_factor) > MAX_INTERVAL )
                *auxo = MAX_INTERVAL;
            else if( ((int)*auxw + widening_factor) < MIN_INTERVAL )
                *auxo = MIN_INTERVAL;
            else
                *auxo = *auxw + widening_factor;

            if( ((int)*(auxw + 1) - widening_factor) > MAX_INTERVAL)
                *(auxo + 1) = MAX_INTERVAL;
            else if( ((int)*(auxw + 1) - widening_factor) < MIN_INTERVAL)
                *(auxo + 1) = MIN_INTERVAL;
            else
                *(auxo + 1) = *(auxw +1) - widening_factor;
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

    // Auxiliares para percorrer dados a cada 2 bytes
    short *auxw, *auxo;
    auxw = (short *)w->data;
    auxo = (short *)o->data;
    int i;
    for(i = 0; i < (w->header->subChunk2Size) / 2; i++, auxw++, auxo++) {
        auxo[((w->header->subChunk2Size) / 2) + i] = auxw[i];
    }

    o->header->subChunk2Size += w->header->subChunk2Size;
    return 1;
}

void printHeader(tWAV *w) {
    printf("riff tag       : %.4s\n"       , w->header->chunkID);
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
