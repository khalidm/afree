#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <vector>
using namespace std;

using std::ofstream;

#include "globals.h"
#include "score.h"
#include "sequence_info.h"

#define AVG(I, J) ((I / J) * 100)
#define AVG2(I, J, K) ((I + J + K) / 3)
#define SQUARE(K) (K * K)
#define mmax(a, b) (((a) > (b)) ? (a) : (b))
#define mmin(a, b) (((a) < (b)) ? (a) : (b))

void SCORE2(size_t r, size_t c, proteins &p1, proteins &p2, accessions &a1,
            accessions &a2, double score_method, double yscore,
            uint16_t **count_matrix, ofstream &outputdp,
            double identity_threshold) {
  // double yscore, uint16_t **count_matrix, ofstream& outputdp, ofstream&
  // outputdotplot, double identity_threshold ){

  double score = 0.0;
  // vector<double> av1v;
  // vector<double> av2v;
  // vector<double> av3v;
  size_t dim = r + c;
  int current_smat = 0;
  // double current_count = 0;
  // double sd_score = 0;

  int max_targets = 50;
  double len1 = 0;
  double len2 = 0;
  int kwords_i = 0;
  int kwords_j = 0;

  // vector<double> yy;
  double minY = 0.0;
  double proportion = 50.0 / 100.0;
  int matches = 0;
  int mismatches = 0;

  bool RET = false;
  string head1 = "#accession1";
  string head2 = "#accession2";
  string head3 = "#SD-score";
  // head1.resize(32,' ');
  // head2.resize(32,' ');
  // head3.resize(32,' ');

  // ORIGINAL outputdp << "#accession1\t#accession2\t#SD-score" << endl;
  // outputdp << head1 << head2 << head3 << endl;

  int trash_count = 0;
  // cout << endl;
  for (int row = 0; row < dim; ++row) {
    // sort row
    for (int col = row; col < dim; ++col) {
      double current_count = count_matrix[row][col];
      len1 = (double)(p1.at(row)).length();
      len2 = (double)(p1.at(col)).length();
      kwords_i = len1 - K_SIZE + 1;
      kwords_j = len2 - K_SIZE + 1;

      double sd_score = (200 * current_count) / (kwords_i + kwords_j);

      if (len1 < 1200 && len1 > 40 && len2 < 1200 && len2 > 40) {
        if (current_count > 10 && current_count < (kwords_i + kwords_j) &&
            sd_score > identity_threshold) {
          if (mmin(len1, len2) >= mmax(len1, len2) * proportion) {
            outputdp << a1[row] << '\t' << a2[col] << '\t';
            outputdp << fixed << showpoint << setprecision(4) << sd_score
                     << endl;
            // outputdotplot << row << '\t' << col << endl;
            if (row != col) {
              outputdp << a1[col] << '\t' << a2[row]
                       << '\t'; //<< sd_score << endl;
              outputdp << fixed << showpoint << setprecision(4) << sd_score
                       << endl;
              // outputdotplot << col << '\t' << row << endl;
            }
          }
        }
      }
    }
  }
  // outputdotplot.close();
  outputdp.close();
}

void SCORE(size_t r, size_t c, proteins &p1, proteins &p2, accessions &a1,
           accessions &a2, double score_method, double yscore,
           uint16_t **count_matrix, int16_t **smat, ofstream &output,
           ofstream &outputdp, double identity_threshold) {
  double score = 0.0;
  vector<double> av1v;
  vector<double> av2v;
  vector<double> av3v;
  size_t dim = r + c;
  int current_smat = 0;

  vector<double> yy;
  double minY = 0.0;
  int matches = 0;
  int mismatches = 0;

  int trash_count = 0;
  for (int row = 0; row < dim; ++row) {
    trash_count = 0;
    matches = 0;
    mismatches = 0;
    for (int col = 0; col < dim; ++col) {
      double len1 = (double)(p1.at(row)).length();
      double len2 = (double)(p2.at(col)).length();
      double d = count_matrix[row][col];
      int l_min = min(len1, len2);
      double l_frac = 0.0;
      double x = 0.0;
      double jdist = 0.0;
      if (len1 == l_min)
        l_frac = len1 / len2;
      else
        l_frac = len2 / len1;
      if (mismatches > (dim / 2))
        break;
      // if(l_frac >= (double) (identity_threshold / 100.0)){
      if (l_frac >= 0.5) {

        double n = l_min - K_SIZE + 1;
        double F = d / n;
        double Y = log10(F + 0.1);
        double sd_score =
            (200 * d) / ((len1 - K_SIZE + 1) + (len2 - K_SIZE + 1));
        jdist = 100.0 * ((len1 - K_SIZE + 1 + len2 - K_SIZE + 1) - d) /
                ((len1 - K_SIZE + 1 + len2 - K_SIZE + 1));
        x = getIdentity(Y);
        if (x > 100.00)
          x = 100.0;
        if (score_method == 0) {
          // cout << "SCORE METHOD : " << score_method << endl;
          if (sd_score > identity_threshold) {
            if ((row < r) && (col > (r - 1))) {
              // smat[row][col -r] = jdist;
              smat[row][col - r] = sd_score;
              count_matrix[row][col] = 1;

              output << (row) << '\t' << (col - r) << "\t" << sd_score << endl;
              outputdp << (row) << '\t' << (col - r) << '\t' << sd_score
                       << endl;
              matches++;
            } else {
              // cout << row << ':' << col << '\t';
              if (row < r && col < r)
                output << (row) << '\t' << (col) << "\t" << sd_score << endl;
              else if (row >= r && col >= r)
                output << (row - r) << '\t' << (col - r) << "\t" << sd_score
                       << endl;
              count_matrix[row][col] = 0;
            }
          } else {
            count_matrix[row][col] = 0;
            mismatches++;
          }
        } else if (score_method == 1) {
          if (x > identity_threshold) {
            if ((row < r) && (col > (r - 1))) {
              smat[row][col - r] = x;
              count_matrix[row][col] = 1;

              output << (row) << '\t' << (col - r) << endl;
              outputdp << (row) << '\t' << (col - r) << endl;
              matches++;
            } else {
              if (row < r && col < r)
                output << (row) << '\t' << (col) << endl;
              else if (row >= r && col >= r)
                output << (row - r) << '\t' << (col - r) << endl;
              count_matrix[row][col] = 0;
            }
          } else {
            count_matrix[row][col] = 0;
            mismatches++;
          }
        }
      } else {
        count_matrix[row][col] = 0;
      }
    }
  }
  output.close();
  outputdp.close();
}

double getIdentity(double Y) {
  double x = 40;
  double b = 70;
  return ((x * Y) + b);
}

void CALC_STATS(vector<double> &x, vector<double> &y, vector<double> &z,
                size_t r, size_t c, vector<double> &scores) {
  double sum_x = 0;
  double sum_y = 0;
  double sum_z = 0;
  double sum_xs = 0;
  double sum_ys = 0;
  double sum_zs = 0;
  int size = r * c;
  double diff = 0;

  for (int i = 0; i < x.size(); i++) {
    // cout << x.at(i) << " ";
    sum_x = sum_x + x.at(i);
    sum_y = sum_y + y.at(i);
    sum_z = sum_z + z.at(i);
  }

  // cout << "\n\tsize = " << x.size() << " " << y.size() << " " << z.size() <<
  // endl; cout << "\tsum = " << sum_x << " " << sum_y << " " << sum_z << endl;

  double av_x = (double)sum_x / x.size();
  double av_y = (double)sum_y / y.size();
  double av_z = (double)sum_z / z.size();
  scores.at(0) = av_x;
  scores.at(1) = av_y;
  scores.at(2) = av_z;

  for (int i = 0; i < x.size(); i++) {
    // diff = x.at(i) - av_x ;
    sum_xs = sum_xs + SQUARE((x.at(i) - av_x));
    // diff = y.at(i) - av_y ;
    sum_ys = sum_ys + SQUARE((y.at(i) - av_y));
    // diff = z.at(i) - av_z ;
    sum_zs = sum_zs + SQUARE((z.at(i) - av_z));
  }

  double sd_x = sqrt((sum_xs / x.size()));
  double sd_y = sqrt((sum_ys / y.size()));
  double sd_z = sqrt((sum_zs / z.size()));
  scores.at(3) = sd_x;
  scores.at(4) = sd_y;
  scores.at(5) = sd_z;

  double t_x = av_x - sd_x;
  double t_y = av_y - sd_y;
  double t_z = av_z - sd_z;

  double avg_t = (t_x + t_y + t_z) / 3.0;
  scores.at(6) = avg_t;
}

double CALC_STATS2(vector<double> &x, vector<double> &y, vector<double> &z,
                   size_t r, size_t c, vector<double> &scores) {
  double sum_x = 0;
  double sum_y = 0;
  double sum_z = 0;
  double sum_xs = 0;
  double sum_ys = 0;
  double sum_zs = 0;
  int size = r * c;
  double diff = 0;

  // double scores[4][2];

  for (int i = 0; i < x.size(); i++) {
    cout << x.at(i) << " ";
    sum_x = sum_x + x.at(i);
    sum_y = sum_y + y.at(i);
    sum_z = sum_z + z.at(i);
  }
  cout << endl;

  cout << "size = " << x.size() << " " << y.size() << " " << z.size() << endl;
  cout << "sum = " << sum_x << " " << sum_y << " " << sum_z << endl;

  double av_x = (double)sum_x / x.size();
  double av_y = (double)sum_y / y.size();
  double av_z = (double)sum_z / z.size();
  // scores.at(0) = av_x; scores.at(1) = av_y; scores.at(2) = av_z;

  cout << "avgs = " << av_x << " " << av_y << " " << av_z << endl;

  cout << x.at(0) << " " << av_x << endl;
  cout << SQUARE((x.at(0) - av_x)) << endl;
  cout << SQUARE(2) << endl;

  for (int i = 0; i < x.size(); i++) {
    // diff = x.at(i) - av_x ;
    sum_xs = sum_xs + SQUARE((x.at(i) - av_x));
    // diff = y.at(i) - av_y ;
    sum_ys = sum_ys + SQUARE((y.at(i) - av_y));
    // diff = z.at(i) - av_z ;
    sum_zs = sum_zs + SQUARE((z.at(i) - av_z));
  }

  double sd_x = sqrt((sum_xs / x.size()));
  double sd_y = sqrt((sum_ys / y.size()));
  double sd_z = sqrt((sum_zs / z.size()));
  // scores.at(3) = sd_x; scores.at(4) = sd_y; scores.at(5) = sd_z;

  double t_x = av_x - sd_x;
  double t_y = av_y - sd_y;
  double t_z = av_z - sd_z;

  double avg_t = (t_x + t_y + t_z) / 3.0;
  // scores.at(6) = avg_t;

  cout << "threholds " << t_x << " " << t_y << " " << t_z;
  cout << " : " << avg_t << endl;

  return avg_t;
  // return scores;
}
