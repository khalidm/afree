#include "globals.h"
#include "macros.h"

using namespace std;

// int getCode(char c);
uint64_t getCode(char c);
char toLower(char ch);
int str_len(char *str);

struct residues res_names[] = {

    {'a', getCode('a')}, {'c', getCode('c')}, {'d', getCode('d')},
    {'e', getCode('e')}, {'f', getCode('f')}, {'g', getCode('g')},
    {'h', getCode('h')}, {'i', getCode('i')}, {'k', getCode('k')},
    {'l', getCode('l')}, {'m', getCode('m')}, {'n', getCode('n')},
    {'p', getCode('p')}, {'q', getCode('q')}, {'r', getCode('r')},
    {'s', getCode('s')}, {'t', getCode('t')}, {'v', getCode('v')},
    {'w', getCode('w')}, {'y', getCode('y')},

};

// GET BITSET
// int getCode(char c){
uint64_t getCode(char c) {
  char aa = toLower(c);
  // int aab = -1;
  uint64_t aab = -1;
  if (ENCODING == 0) {
    switch (aa) {
    case 'a':
      return aab = 0;
      break;
    case 'c':
      return aab = 1;
      break;
    case 'd':
      return aab = 2;
      break;
    case 'e':
      return aab = 3;
      break;
    case 'f':
      return aab = 4;
      break;
    case 'g':
      return aab = 5;
      break;
    case 'h':
      return aab = 6;
      break;
    case 'i':
      return aab = 7;
      break;
    case 'k':
      return aab = 8;
      break;
    case 'l':
      return aab = 9;
      break;
    case 'm':
      return aab = 10;
      break;
    case 'n':
      return aab = 11;
      break;
    case 'p':
      return aab = 12;
      break;
    case 'q':
      return aab = 13;
      break;
    case 'r':
      return aab = 14;
      break;
    case 's':
      return aab = 15;
      break;
    case 't':
      return aab = 16;
      break;
    case 'v':
      return aab = 17;
      break;
    case 'w':
      return aab = 18;
      break;
    case 'y':
      return aab = 19;
      break;
    }
  } else if (ENCODING == 1) {
    switch (aa) {
    case 'a':
      return aab = 0;
      break;
    case 'c':
      return aab = 1;
      break;
    case 'd':
      return aab = 4;
      break;
    case 'e':
      return aab = 4;
      break;
    case 'f':
      return aab = 2;
      break;
    case 'g':
      return aab = 0;
      break;
    case 'h':
      return aab = 3;
      break;
    case 'i':
      return aab = 1;
      break;
    case 'k':
      return aab = 5;
      break;
    case 'l':
      return aab = 1;
      break;
    case 'm':
      return aab = 2;
      break;
    case 'n':
      return aab = 3;
      break;
    case 'p':
      return aab = 1;
      break;
    case 'q':
      return aab = 3;
      break;
    case 'r':
      return aab = 5;
      break;
    case 's':
      return aab = 0;
      break;
    case 't':
      return aab = 0;
      break;
    case 'v':
      return aab = 1;
      break;
    case 'w':
      return aab = 2;
      break;
    case 'y':
      return aab = 2;
      break;
    }
  } else if (ENCODING == 2) {
    switch (aa) {
    case 'a':
      return aab = 0;
      break;
    case 'c':
      return aab = 1;
      break;
    case 'd':
      return aab = 2;
      break;
    case 'e':
      return aab = 3;
      break;
    case 'f':
      return aab = 4;
      break;
    case 'g':
      return aab = 5;
      break;
    case 'h':
      return aab = 2;
      break;
    case 'i':
      return aab = 6;
      break;
    case 'k':
      return aab = 3;
      break;
    case 'l':
      return aab = 6;
      break;
    case 'm':
      return aab = 6;
      break;
    case 'n':
      return aab = 1;
      break;
    case 'p':
      return aab = 7;
      break;
    case 'q':
      return aab = 3;
      break;
    case 'r':
      return aab = 3;
      break;
    case 's':
      return aab = 0;
      break;
    case 't':
      return aab = 0;
      break;
    case 'v':
      return aab = 6;
      break;
    case 'w':
      return aab = 4;
      break;
    case 'y':
      return aab = 4;
      break;
    }
  } else if (ENCODING == 3) {
    switch (aa) {
    case 'a':
      return aab = 0;
      break;
    case 'c':
      return aab = 1;
      break;
    case 'd':
      return aab = 2;
      break;
    case 'e':
      return aab = 2;
      break;
    case 'f':
      return aab = 3;
      break;
    case 'g':
      return aab = 4;
      break;
    case 'h':
      return aab = 5;
      break;
    case 'i':
      return aab = 6;
      break;
    case 'k':
      return aab = 7;
      break;
    case 'l':
      return aab = 8;
      break;
    case 'm':
      return aab = 8;
      break;
    case 'n':
      return aab = 5;
      break;
    case 'p':
      return aab = 9;
      break;
    case 'q':
      return aab = 2;
      break;
    case 'r':
      return aab = 7;
      break;
    case 's':
      return aab = 0;
      break;
    case 't':
      return aab = 0;
      break;
    case 'v':
      return aab = 6;
      break;
    case 'w':
      return aab = 3;
      break;
    case 'y':
      return aab = 3;
      break;
    }
  }
  return aab;
}

// TO LOWER
char toLower(char ch) {

  char aa_lower;
  int differ = 'A' - 'a';
  if (ch >= 'A' && ch <= 'Z') {
    ch = ch - differ;
    // memcpy(aaL,&ch,1);
  }
  aa_lower = ch;
  return aa_lower;
}

// CHAR ARRAY LENGTH
int str_len(char *str) {

  int count = 0;
  while (*str++)
    count++;
  return count;
}

void max2min(int **ARRAY, int dim) {
  // transform the matrix from maximization to minimization
  int maxVal = -32767;
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (ARRAY[i][j] > maxVal)
        maxVal = ARRAY[i][j];
    }
  }
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      ARRAY[i][j] = maxVal - ARRAY[i][j];
    }
  }
}

std::vector<std::string> split2(const std::string &s, char delim,
                                std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

double round(double num, int places) {
  double temp, mult;
  mult = pow(10.0, places);
  temp = floor(num * mult + 0.5);
  temp = temp / mult;
  return temp;
}
