#ifndef SEQINFO
#define SEQINFO

#include "globals.h"
#include "macros.h"

void GET_SEQUENCES(string file, proteins &p, accessions &acc, size_t *g_kmers);
string split(const string &s, const string &delim);
char *getCharArray(string s);

#endif
