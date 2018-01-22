#include <algorithm>
#include <bitset>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>

#include "globals.h"

using namespace std;

// SHIFT PACK FIRST 32 BIT
#define SHIFT(K_SIZE) (64 - (K_SIZE * 5))

// HEADERS
void GET_GENOME_TUPLES(proteins &p, uint64_t *g_tuples);
uint64_t getIntCode(const char *kmer);
char *int2bin(uint64_t a);
void clearCharBuff(char *buf);

void GET_GENOME_TUPLES(proteins &p, uint64_t *g_tuples) {

  int i, j, second_length, tuple_index, k;
  i = j = second_length = tuple_index = k = 0;
  // TEMPORARY TUPLE FOR EACH PROTEIN TO BE INSERTED TO THE TUPLES
  uint64_t temp_tuple = 0;
  int protein_number = 0;
  const char *kmer;
  string s;

  for (proteins::const_iterator it = p.begin(); it != p.end(); ++it) {

    // second_length = str_len(it->second);
    second_length = (*it).length(); // SEQUENCE VECTOR
    s = *it;                        // SEQUENCE VECTOR
    // cout << "seq: " << s << endl ;
    k = second_length - K_SIZE + 1;

    vector<uint64_t> l_tuples_vec;
    for (i = 0; i < k; i++) {

      // kmer = s.substr( i , 3 ).c_str();
      kmer = s.substr(i, K_SIZE).c_str();
      // cout << kmer << ", ";

      // INSERT K-MER TO LIST
      uint64_t a = getIntCode(kmer);
      // INSERT PROTEIN NUMBER TO TUPLE
      uint64_t b = protein_number;
      // b <<= (32 - 18);
      b <<= 14;
      // INSERT OFFSET TO TUPLE
      b = b | i;
      temp_tuple = a | b;

      l_tuples_vec.push_back(temp_tuple);
    }
    sort(l_tuples_vec.begin(), l_tuples_vec.end());
    /*	cout << "List contains:\n" ;
            for( size_t i = 0 ; i < l_tuples_vec.size() ; i++ ) {
            cout << (l_tuples_vec[i]>>32) << endl;
            }

            cout << "----" << endl << endl ;
            */

    uint64_t prev = ~(0UL);
    for (size_t i = 0; i < l_tuples_vec.size(); i++) {
      if ((l_tuples_vec[i] >> 32) != (prev >> 32)) {
        // add tuple into the global list
        g_tuples[tuple_index++] = l_tuples_vec[i];
        prev = l_tuples_vec[i];
        // cout << "adding " << (l_tuples_vec[i]>>32) << endl ;
      }
      /*
         else {
         cout << "ignoring " << (l_tuples_vec[i]>>32)
         << " -- " << (prev>>32) << endl ;
         }*/
    }

    // INCREMENT AND RESET
    protein_number++;
    temp_tuple = 0;
    // cout <<endl;
  }
}

// PACK IN THE INT VALE FOR EACH AMINO ACID IN KMER TO LLUint
uint64_t getIntCode(const char *kmer) {
  uint64_t temp = 0;
  int i = 0;
  for (i = 0; i < K_SIZE; i++) {
    // cout << kmer[i] << "." << getCode(kmer[i]);
    temp = temp | getCode(kmer[i]);
    temp <<= 5;
    // cout << ' ';
  }
  temp <<= (SHIFT(K_SIZE) - 5); // change for general k-mer size
  return temp;
}

// PRINT INT TO BINARY -- TEST
char *int2bin(uint64_t a) {
  char *str, *tmp;
  int count = 63;
  str = (char *)malloc(65);
  tmp = str;
  while (count > -1) {
    str[count] = '0';
    count--;
  }
  count = 63;
  while (a > 0) {
    if (a % 2 == 1) {
      str[count] = '1';
    }
    count--;
    a = a / 2;
  }
  return tmp;
}
