#ifndef GLOBALS_H
#define GLOBALS_H

#include <cmath>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef std::vector<string> proteins;

typedef std::vector<string> accessions;

// typedef unsigned long long int uint64_t;

// typedef unsigned short int uint16_t;

struct residues {
  char single_letter_code;
  int aab;
};

template <class Type> inline std::string to_string(const Type &number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}

template <class T> void init2D(T **mat, size_t r, size_t c) {
  for (int i = 0; i < r; i++)
    mat[i] = new T[c];

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      mat[i][j] = 0;
    }
  }
}

template <class T> void delete2D(T **cnt, size_t r) {
  for (int row = 0; row < r; ++row) {
    delete[] cnt[row];
  }
  delete[] cnt;
}

// HEADERS
uint64_t getCode(char c);
char toLower(char ch);
int str_len(char *str);

std::vector<std::string> split2(const std::string &s, char delim,
                                std::vector<std::string> &elems);
double round(double, int);

extern int K_SIZE;

#define KMER_SIZE 3
#define ENCODING 0 // 0 aa or 1 lesk

#endif
