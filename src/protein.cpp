#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
using std::cerr;
using std::cout;
using std::endl;
using std::flush;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::string;

#include "protein.h"

// Protein constructor
Protein::Protein() {
  // header = sequence = "";
}

Protein::~Protein() {
  // header = sequence = "";
}

void Protein::setHeader(string h) { header = h; }

void Protein::setSequence(string s) { sequence = s; }

void Protein::setLength(int l) { length = l; }

void Protein::getHeader() { cout << header << "\n"; }

void Protein::getSequence() { cout << sequence << "\n"; }

void Protein::getLength() { cout << length << "\n"; }
