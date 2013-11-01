#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cstdlib>	// provides atoi(), exit()
#include <cctype>       // provides isalpha(), tolower()
#include <queue>	// provides queue class
#include "freqq.h"

using namespace std;


// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
  for( string::iterator it = line.begin(); it != line.end(); ++it ) {
    if( !isalpha(*it) ) {
      if( (*it != '-' && *it != '\'') ||
          it == line.begin() || it+1 == line.end() ||
          !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
        *it = ' ';
      }
    } else {
      *it = tolower(*it);
    }
  }
}

int main(int argc, char *argv[]) {
  if( argc != 3 ) {
    cerr << "Usage: " << argv[0] << " k book.txt" << endl;
    cerr << "  Print the most frequent word in each contiguous\n\
  subsequence of k words from book.txt." << endl; 
    exit(1);
  }

  int k = atoi(argv[1]);
  if( k < 1 || k > 32768 ) {
    cerr << "k must be between 1 and 32768." << endl;
    exit(2);
  }

  ifstream fin;
  fin.open(argv[2]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  string line, word;
  int nwords = 0;
  queue<string> Q;
  FreqQ FQ;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
      Q.push(word);
      FQ.add(word);
      nwords++;
      if( nwords > k ) {
	FQ.sub(Q.front());
	Q.pop();
      }
      if( nwords >= k ) {
	cout << nwords-k+1 << "-" << nwords << " ";
	cout << FQ.topWord() << "(" << FQ.topFreq() << ")" << endl;
      }
    }
  }
}
