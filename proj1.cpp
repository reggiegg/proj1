#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "proj1.h"

using namespace std;

// Go line by line, extracting each word, adding them to the index structure

vector<word*> words;


void parseBook(ifstream& in)
{	
	word *a = new word();
	a->name = "banana";
	words.push_back(a);

	cout << words[0]->name << endl;
}

void printIndex(ofstream& out)
{
	
	//code goes here.
}

// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string& line) 
{
	for( string::iterator it = line.begin(); it != line.end(); ++it ) {
		if( !isalpha(*it) ) {
			if( (*it != '-' && *it != '\'') ||
			it == line.begin() || it+1 == line.end() ||
			!isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
				*it = ' ';
			}
		} 
		else {
			*it = tolower(*it);
		}
	}
}


int main(int argc, char const *argv[])
{	
	// error handling for incorrect arguments
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " infile.txt outfile.txt" << endl;
		// return 1;
	}

	ifstream in(argv[1]);
	ofstream out(argv[2]); //TODO: make more robust (potential error handling)
	string s;

	while(getline(in, s)){
		cout << s << "\n";
		// out << s << "\n";
	}

	parseBook(in);
	printIndex(out);

	return 0;
}