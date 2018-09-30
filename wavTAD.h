
#ifndef __wavTAD__
#define __wavTAD__

#include <inttypes.h>

#define MAX_FILE_NAME 25
#define MAX_INTERVAL  32767
#define MIN_INTERVAL -32767

typedef struct sHEADER {
	char chunkID[4];
	uint32_t chunkSize;
	char     format[4];
	char     subChunk1ID[4];
	uint32_t subChunk1Size;
	uint16_t audio_format;
	uint16_t num_channels;
	uint32_t sample_rate;
	uint32_t byte_rate;
	uint16_t block_align;
	uint16_t bits_per_sample;
	char     subChunk2ID[4];
	uint32_t subChunk2Size;
} tHeader;

typedef struct sWAV {
	tHeader *header;
	int16_t *data;
} tWAV;

#endif
