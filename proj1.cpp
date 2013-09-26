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


// parses each word in the given input stream, and adds it to the index structure
void parseBook(ifstream& in)
{	

	int counter = 0;

	string s;

	// for every word in the input stream:
	while(getline(in, s)){
		lowercaseWords(s);
		string word;
		istringstream iss(s, istringstream::in);
		while(iss >> word){
			updateIndex(word, (counter/40)+1, 0, words.size()-1);
		}
		counter++;
	}
}


// find location of word alphabetically, if it exists: increase the count and add the page number.
// if it doesn't: insert it into the index.
void updateIndex(string wd, int page, int begin, int end)
{
	// using binary search
	if (begin > end) { 
		// create and insert new word into array
		word *w = new word();
		w->name = wd;
		w->count = 1;
		w->pages = new vector<int>;
		(w->pages)->push_back(page);
		vector<word*>::iterator nth = words.begin() + end +1 ;//here is the segmentation fault
		words.insert(nth, w);
	} else {
		int middle = (begin + end )/2;
		int compValue = wd.compare(words[middle]->name);
		if (compValue < 0) {
			updateIndex(wd, page, begin, middle-1);
		} else if (compValue > 0) {
			updateIndex(wd, page, middle+1, end);
		} else {
			// updates the given word's information
			word* w = words[middle];
			(w->count)++;
			(w->pages)->push_back(page);
		}
	} 								 

}


// prints the pages vector
void printPages(vector<int> pages, ofstream& out)
{
	for (vector<int>::iterator it = pages.begin(); it != pages.end(); ++it)
	{
		out << *it << " ";
	}
}

// prints index of words, counts and pages
void printIndex(ofstream& out)
{
	
	//iterate through words
	//for each word, print word, number of occurances, and list of pages. endl.
	for (vector<word*>::iterator it = words.begin() ; it != words.end(); ++it)
	{	
		word* w = *it;
		out << w->name << " (" << w->count << ") ";
		printPages(*(w->pages), out);
		out << endl;  
	}
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
		return 1;
	}

	ifstream in(argv[1]);
	ofstream out(argv[2]); //TODO: make more robust (potential error handling)
	string s;

	parseBook(in);
	printIndex(out);

	return 0;
}