#ifndef SCORE_H
#define SCORE_H
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

#include "globals.h"

using namespace std;

// WITH DP void SCORE2( size_t , size_t, proteins&, proteins&, accessions&,
// accessions&, double score_method, double yscore, uint16_t **, ofstream&,
// ofstream& outputdotplot, double );
void SCORE2(size_t, size_t, proteins &, proteins &, accessions &, accessions &,
            double score_method, double yscore, uint16_t **, ofstream &,
            double);
void SCORE(size_t, size_t, proteins &, proteins &, accessions &, accessions &,
           double score_method, double yscore, uint16_t **, int16_t **,
           ofstream &, ofstream &, double);

double CALC_STATS2(vector<double> &, vector<double> &, vector<double> &,
                   size_t r, size_t c, vector<double> &);
void CALC_STATS(vector<double> &, vector<double> &, vector<double> &, size_t r,
                size_t c, vector<double> &);
double getIdentity(double);

#endif
