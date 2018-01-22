#ifndef SEQUENCE_TUPLES_H
#define SEQUENCE_TUPLES_H

#include "globals.h"
#include "macros.h"

// HEADERS
void GET_GENOME_TUPLES(proteins &p, uint64_t *g_tuples);

char *int2bin(uint64_t a);
char *getSubArray(char *second, int start);
int getIntCode(const char *kmer);
void clearCharBuff(char *buf);

#endif
