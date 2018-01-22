#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include "globals.h"
#include "sequence_info.h"

using namespace std;
using std::cerr;
using std::cout;
using std::endl;
using std::flush;
using std::ifstream;
using std::ofstream;
using std::setw;

// void getSequences( string file, proteins& p, size_t *g );
// void GET_SEQUENCES( string file, proteins& p, size_t *g );
void GET_SEQUENCES(string file, proteins &p, accessions &acc, size_t *g);
string split(const string &s, const string &delim);
char *getCharArray(string s);

// GET PROTEIN SEQUENCES FROM FILE
// void getSequences( string file, proteins& p, size_t *g ){
// void GET_SEQUENCES( string file, proteins& p, size_t *g ){
void GET_SEQUENCES(string file, proteins &p, accessions &acc, size_t *g) {
  ifstream fasta(file.c_str(), ios::in);
  if (!fasta) {
    cerr << file << " could not be found.\n";
    fasta.close();
    exit(1);
  }
  string newID, seqID;
  int seqlength = 0;
  int sequenceheader = 0;
  int firstrun = 1; // FIRST HEADER
  string sequence;  // COMPLETE SEQUENCE
  string currentaa; // SEQUENCE IN EACH ROW OF FASTA FILE
  int id = 1;
  int bit_size;
  // char *a;
  char *seq;
  int size = 0;
  int kmers = 0;
  stringstream ss; // create a stringstream
  string seqidn;   // id number

  // GO THROUGH FASTA FILE
  while (!fasta.eof()) {
    getline(fasta, currentaa);

    // NEW SEQUENCE HEADER
    if (currentaa.substr(0, 1) == ">") {
      sequenceheader = 1;
      newID = currentaa.substr(1);
      size++;
    }
    // SEQUENCE LINE
    if (sequenceheader == 0) {
      sequence = sequence + currentaa;
      seqlength = sequence.length();
      continue;
    }
    // SKIP ANNOTATION FOR FIRST HEADER
    if (firstrun == 1) {
      firstrun = 0;
      sequenceheader = 0;
      seqID = newID;
      continue;
    }

    // DEBUG
    // cout << endl;
    int seqidlength = seqID.length();
    // cout << seqidlength << "\t";
    // string subid = seqID.substr(0,29);
    // cout << subid << endl << flush;
    // DEBUG

    if (seqidlength > 30) {
      seqID = split(seqID, " ");

    } else {
      seqID = seqID.substr(0, 30);
    }
    // add seq number
    // ss << id;//add number to the stream
    // seqidn = ss.str();
    // strcat(seqidn, seqID);
    seqID.resize(30, ' ');

    // seqID = split(seqID, " ");

    seq = new char[sequence.size() + 1];
    seq[sequence.size()] = 0;

    // for kmer count
    kmers += (sequence.size() - K_SIZE) + 1;
    // cout << "kmers " << kmers << ",";

    memcpy(seq, sequence.c_str(), sequence.size());
    // INSERT SEQUENCE INTO MAP
    // p.insert( proteins::value_type( id, seq ) );
    // INSERT SEQUENCE INTO VECTOR
    p.push_back(sequence);
    acc.push_back(getCharArray(seqID));
    // cout << getCharArray(seqID) << '\n' << sequence << endl;
    // p.insert( proteins::value_type( getCharArray(seqID), seq ) );

    // RESET SEQUENCE VARIABLES
    sequenceheader = 0;
    seqID = newID;
    sequence = "";
    id++;
    ss.str("");
    ss.clear();
  }
  // LOOP OVER FASTA FILE

  // LAST SEQUENCE
  seq = new char[sequence.size() + 1];
  seq[sequence.size()] = 0;

  kmers += (sequence.size() - K_SIZE) + 1;

  memcpy(seq, sequence.c_str(), sequence.size());

  // DEBUG
  // cout << endl;
  int seqidlength = seqID.length();
  // cout << seqidlength << "\t";
  // string subid = seqID.substr(0,29);
  // cout << endl << subid << endl << flush;
  // DEBUG
  if (seqidlength > 30) {
    seqID = split(seqID, " ");

  } else {
    seqID = seqID.substr(0, 30);
  }
  // add seq number
  // ss << id;//add number to the stream
  // seqidn = ss.str();
  // strcat(seqidn, seqID);
  seqID.resize(30, ' ');

  // seqID = split(seqID, " ");

  // INSERT LAST SEQUENCE INTO MAP
  // p.insert( proteins::value_type( id, seq ) );
  // INSERT LAST SEQUENCE INTO VECTOR
  p.push_back(sequence);
  acc.push_back(getCharArray(seqID));
  // cout << getCharArray(seqID) << '\n' << sequence << endl;
  // p.insert( proteins::value_type( getCharArray(seqID), seq ) );

  // seq = '\0';
  seq = NULL;
  fasta.close();

  g[0] = size;  // length of the protein
  g[1] = kmers; // number of kmers

  // return kmers;
}

// SPLIT STRING
string split(const string &s, const string &delim) {
  string res;
  vector<string> result;

  bool keep_empty = true;

  if (delim.empty()) {
    result.push_back(s);
    res = "";
    return res;
  }
  string::const_iterator substart = s.begin(), subend;
  while (true) {
    subend = search(substart, s.end(), delim.begin(), delim.end());
    string temp(substart, subend);
    if (keep_empty || !temp.empty()) {
      result.push_back(temp);
    }
    if (subend == s.end()) {
      break;
    }
    substart = subend + delim.size();
  }

  // res = result[1];
  res = result[0];

  return res;
}

// COVERT STRING TO CHAR ARRAY
char *getCharArray(string s) {
  char *b = new char[s.size() + 1];
  b[s.size()] = 0;
  memcpy(b, s.c_str(), s.size());

  return b;
}
