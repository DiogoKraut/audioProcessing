#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "wavprocessing.h"
#include "wavaccess.h"
#include "wavTAD.h"
#include "parse.h"

int main(int argc, char * const *argv) {
    // Aloca estrutura para tratar entrada
    tOPT_ARGS *opts = malloc(sizeof(tOPT_ARGS));
    int i;
    inicializaOPTS(opts);
    if(!parseMain(argc, argv, "i:o:l:t:", opts)) 
        exit(EXIT_FAILURE);

    tWAV **win, *wout;

    // Aloca espaco para os arquivos wav
    win = malloc(sizeof(tWAV *) * opts->INPUT_LIST_SIZE);
    for(i = 0; i < opts->INPUT_LIST_SIZE; i++) {
        win[i]         = malloc(sizeof(tWAV));
        win[i]->header = malloc(sizeof(tHeader));
        win[i]->data   = malloc(sizeof(int16_t));
    }

    // wout         = malloc(sizeof(tWAV));
    // wout->header = malloc(sizeof(tHeader));
    // wout->data   = malloc(sizeof(int16_t));

    for(i = 0; i < opts->INPUT_LIST_SIZE; i++) {
        readWavFile(&win[i], opts->INPUT_LIST[i]);
        // printHeader(win[i]);
    }

    for(i = 1; i < opts->INPUT_LIST_SIZE; i++) { // Para cada arqv da lista
        // Aloca espaco para concatenar e verifica alocacao
        win[0]->data = realloc(win[0]->data, win[0]->header->subChunk2Size + win[i]->header->subChunk2Size);
        if(!wavConcat(win[i], win[0])) {// Concatena no primeiro arqv
            fprintf(stderr, "Falha ao concatenar o arquivo %s.\n", opts->INPUT_LIST[i]);
            exit(EXIT_FAILURE);
        }
    }


    // // Copia o cabecario e aloca espaco para dados em wout
    // memcpy(wout->header, win->header, sizeof(tHeader));
    // wout->data = realloc(wout->data, wout->header->subChunk2Size);
    // int n;
    // for (n = 1; n<=16;n++){
    //     effect_echo(win, wout, opts->LEVEL, opts->DELAY, n);
    // }    
    writeToWav(win[0], opts->OUTPUT_FILE); // Escreve para arqv de saida

    // Free routine
    for(i = 0; i < opts->INPUT_LIST_SIZE; i++) {
        free(win[i]->data);
        free(win[i]->header);
        free(win[i]);
    }
    free(opts);
    free(win);

    // free(wout->data);
    // free(wout->header);
    // free(wout);
return 0;
}