#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using std::ofstream;

#include "globals.h"
#include "join_lists.h"
#include "macros.h"
#include "radixLSD.h"
#include "score.h"
#include "sequence_info.h"
#include "sequence_tuples.h"

void printTuples(uint64_t *g_tuple, size_t g_tuples_length);
void printV(accessions &a);
void printUsage();

#define AVG(I, J) ((I / J) * 100)

int K_SIZE;

int main(int argc, char *argv[]) {
  // VARIABLES
  proteins p1;
  proteins p2;
  accessions a1;
  accessions a2;

  std::string fastaFile1 = "";
  std::string fastaFile2 = "";
  std::string blastFile = "";
  std::string out = "";
  char out_file[20];
  char out_dp_file[20];
  char out_cl_file[20];
  char out_e1_file[20];
  char out_e2_file[20];
  char out_dp2_file[20];
  double identity_threshold = 10.00;
  double coverage = 50.00;
  double yscore = -1;
  double score_method = -1; // 0 SD - 1 DIST
  K_SIZE = 5;

  map<string, string> kmer_map;

  int option = 1;

  if (argc == 1) {
    std::cout << "Not enough or invalid arguments, please try again.\n";
    printUsage();
    exit(0);
  }

  for (int i = 1; i < argc; i = i + 2) {
    if (i + 1 != argc) {
      if (strncmp(argv[i], "-g1", 3) == 0) {
        fastaFile1 = argv[i + 1];
      } else if (strcmp(argv[i], "-g2") == 0) {
        fastaFile2 = argv[i + 1];
      } else if (strcmp(argv[i], "-o") == 0) {
        out_file[str_len(argv[i + 1])];
        out_dp_file[str_len(argv[i + 1]) + 3];
        out_cl_file[str_len(argv[i + 1]) + 3];
        out_e1_file[str_len(argv[i + 1]) + 6];
        out_e2_file[str_len(argv[i + 1]) + 6];
        out_dp2_file[str_len(argv[i + 1]) + 6];
        strcpy(out_file, argv[i + 1]);
        strcpy(out_dp_file, argv[i + 1]);
        strcpy(out_cl_file, argv[i + 1]);
        strcpy(out_e1_file, argv[i + 1]);
        strcpy(out_e2_file, argv[i + 1]);
      } else if (strcmp(argv[i], "-c") == 0) {
        coverage = atof(argv[i + 1]);
        identity_threshold = atof(argv[i + 1]);
        if (coverage > 100 || coverage < 10) {
          std::cout << "Invalid argument -c should be 10 < c < 100, please try "
                       "again.\n";
          printUsage();
          exit(0);
        }
        // option = 1;
      } else if (strcmp(argv[i], "-y") == 0) {
        yscore = atof(argv[i + 1]);
        // option = 1;
      } else if (strcmp(argv[i], "-b") == 0) {
        // blastFile = argv[i+1];
        // option = 2;
        printUsage();
        exit(0);
      } else if (strcmp(argv[i], "-s") == 0) {
        score_method = atof(argv[i + 1]);
        if (score_method < 0 || score_method > 1) {
          std::cout << "Invalid argument -s should be 0 - Sorensen or 1 - "
                       "Distance based similarity measure.\n";
          printUsage();
          exit(0);
        }
      } else if (strcmp(argv[i], "-k") == 0) {
        K_SIZE = atoi(argv[i + 1]);
        if (K_SIZE > 6 || K_SIZE < 3) {
          std::cout
              << "Invalid argument -k should be 2 < k < 7, please try again.\n";
          printUsage();
          exit(0);
        }
        // option = 1;
      } else {
        std::cout << "Not enough or invalid arguments, please try again.\n";
        printUsage();
        exit(0);
      }
    } else {
      std::cout << "Not enough or invalid arguments, please try again.\n";
      printUsage();
    }
  }

  time_t start_wall = time(NULL);
  clock_t start_cpu = clock();

  cout << "Reading sequecnes... " << flush;
  size_t *g1 = new size_t[2];
  size_t *g2 = new size_t[2];
  // READ FASTA FILE 1 & 2
  GET_SEQUENCES(fastaFile1, p1, a1, g1);
  GET_SEQUENCES(fastaFile2, p2, a2, g2);
  size_t g1_size = g1[0];  // number of proteins in G1
  size_t g1_kmers = g1[1]; // number of kmers in G1
  size_t g2_size = g2[0];  // number of proteins in G2
  size_t g2_kmers = g2[1]; // number of kmers in G2
  cout << "done." << endl << flush;

  // MERGE a1 and a2 to a3
  accessions a3;
  accessions::iterator it;
  std::back_insert_iterator<accessions> acc(a3);
  copy(a1.begin(), a1.end(), acc);
  copy(a2.begin(), a2.end(), acc);
  a1.clear();
  a2.clear();
  // printV(a3);

  proteins p3;
  proteins::iterator itp;
  std::back_insert_iterator<proteins> prot(p3);
  copy(p1.begin(), p1.end(), prot);
  copy(p2.begin(), p2.end(), prot);
  p1.clear();
  p2.clear();

  // CONCATENATED SEQUENCES VARIABLES
  size_t g3_kmers = g1_kmers + g2_kmers; // number of kmers in G1+G2
  size_t g3_size = g1_size + g2_size;    // number of kmers in G1 and G2

  // HASH EACH SEQUENCE
  uint64_t *g3_tuples = new uint64_t[g3_kmers];

  uint16_t **count_matrix = new uint16_t *[g3_size];
  init2D<uint16_t>(count_matrix, g3_size, g3_size);

  int maxsize = max(g1_size, g2_size);

  if (option == 1) {
    cout << "Running comparison... " << flush;
    GET_GENOME_TUPLES(p3, g3_tuples);

    SORT_TUPLES(g3_tuples, g3_kmers);
    JOIN_TUPLES2(g3_tuples, g3_kmers, count_matrix);
    strcat(out_dp_file, "");
    ofstream outputdp(out_dp_file);
    SCORE2(g1_size, g2_size, p3, p3, a3, a3, score_method, yscore, count_matrix,
           outputdp, identity_threshold);
    a3.clear();
    p3.clear();
    // delete [] g3_tuples;
    cout << "done." << endl << flush;
    // EXIT IF ONLY AAA
    exit(0);
  } else {
    printUsage();
    exit(1);
  }
}

// PRINT USAGE
void printUsage() {
  cout << "\n"
       << "Usage: afree -g1 <fasta file1> -g2 <fasta file2> -o <output file "
          "name> -c <SD-score 10 < c < 100 default=10> "
       << "-k <k-word size (default+recommended=5)>\n"
       << "afree(v2): Alignment-free all-against-all proteome sequence "
          "comparison.\n"
       << "Authors K.Mahmood, A.Konagurthu, et.al.\n"
       << endl;
}

void printTuples(uint64_t *g_tuples, size_t g_tuples_length) {
  int c = 0;
  int cc = 0;
  cout << "array size: " << g_tuples_length << endl;
  for (int i = 0; i < g_tuples_length; i++) {
    cout << int2bin(g_tuples[i]) << "\n";
    // cout << g_tuples[i] << "\n";
  }
}

void printV(accessions &a) {
  for (int i = 0; i < a.size(); ++i) {
    cout << a[i] << "\n";
  }
  cout << endl;
  cout << "********" << endl;
}
