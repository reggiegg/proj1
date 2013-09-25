#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "proj1.h"
#include <sstream>

using namespace std;

// Go line by line, extracting each word, adding them to the index structure

vector<word*> words;


void parseBook(ifstream& in)
{	
	string s;
	// for every word in the input stream:
	while(getline(in, s)){
		lowercaseWords(s);
		string word;
		istringstream iss(s, istringstream::in);
		while(iss >> word){
			updateIndex(word);
		}
	}


	// add if the word if it isn't, in the correct position
	// if it is, increment the count of the word, and add the page




	// word *a = new word();
	// a->name = "banana";
	// a->count = 666;
	// a->pages = new vector<int>;
	// (*(a->pages)).push_back(6);
	// (*(a->pages)).push_back(6);
	// (*(a->pages)).push_back(6);
	// words.push_back(a);

	// a = new word();
	// a->name = "banana";
	// a->count = 666;
	// a->pages = new vector<int>;
	// (*(a->pages)).push_back(6);
	// (*(a->pages)).push_back(6);
	// (*(a->pages)).push_back(6);
	// words.push_back(a);


	// cout << words[0]->name << endl;
}

void updateIndex(string word)
{
	// check to see if the word is in the index
	// add if the word if it isn't, in the correct position
	// if it is, increment the count of the word, and add the page
}


// prints the pages vector
void printPages(vector<int> pages)
{
	for (vector<int>::iterator it = pages.begin(); it != pages.end(); ++it)
	{
		cout << *it << " ";
	}
}

// prints index of words, counts and pages
void printIndex(ofstream& out)
{
	
	//iterate through words
	for (vector<word*>::iterator it = words.begin() ; it != words.end(); ++it)
	{	
		word* w = *it;
		cout << w->name << " (" << w->count << ") ";
		printPages(*(w->pages));
		cout << endl;  
	}
	//for each word, print word, number of occurances, and list of pages. endl.
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

	parseBook(in);
	printIndex(out);

	return 0;
}