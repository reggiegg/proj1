#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "proj1b.h"
#include <sstream>

using namespace std;


// The dummy node (the beginning) of the skip list: our Data Structure
node* head;

// keeps track of all the nodes we've visited.
node* path[MAX_HEIGHT];

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
			updateIndex(word, (counter/40)+1);
		}
		counter++;
	}
}

// Return the node for the word of the given string in the given skip list, or NULL if it doesn't exit.
node* find(string wd, node* skiplist, int index)
{
	if (index == -1){  // not in the list
		return NULL;
	}

	path[index] = skiplist; // add where we've been
	node* next = skiplist->next[index];

	if (next){
		int compValue = wd.compare(next->w->name);
		if (compValue == 0){
			return next;
		} else if (compValue > 0){
			return find (wd, next, index);
		}
	}
	return find(wd, skiplist, index-1);	
}


// creates a new word and adds it to a new node, and returns that node
node* make_node(string wd, int page)
{
		// create and initialize a new word
		word *w = new word();
		w->name = wd;
		w->count = 1;
		w->pages = new vector<int>;
		(w->pages)->push_back(page);

		// create and initialize a new node, arbitrary next!
		node* n = new node();
		make_height(n);
		n->w = w;

		return n;
}

// Assigns a random height for a given node.
void make_height(node* n)
{
	int i;
	for( i=1; i<MAX_HEIGHT; ++i ) {
		if( randBit() == 1 ) break;
	}
	n->height = i;
}

// creates a random number with proper distribution from 1 to MAX_HEIGHT
int randBit(void) 
{ 
	static int bitsUpperBd=0;
	static int bits; // store bits returned by rand()
	if( bitsUpperBd == 0 ) { // refresh store when empty
		bitsUpperBd = RAND_MAX;
		bits = rand();
	}
	int b = bits & 1;
	bits >>= 1;
	bitsUpperBd >>= 1;
	return b;
}

// find location of word alphabetically, if it exists: increase the count and add the page number.
// if it doesn't: insert it into the index.
void updateIndex(string wd, int page)
{
	node* n = find(wd, head, MAX_HEIGHT - 1);
	if (n) { 				// assuming NULL is false
		update_word(n->w, page);
	} else {
		n =	make_node(wd, page);
		update_pointers(n);
	}

}

// Adds the given page number to the given word
void update_word(word* w, int page)
{
	(w->count)++;
	pushPages(w, page);
}

// Adds given page number to back of page vector only if it isn't already there
// Assumes: increasing order for page nums.
void pushPages(word *w, int num)
{
	vector<int> *pages = w->pages;
	if (pages->back() != num) {
		pages->push_back(num);
	}
}

// Assigns the pointers in n->next to the appropriate ones in path.
// And updates the pointers in the preceding path nodes.
void update_pointers(node* n)
{
	for(int h = 0; h < n->height; ++h ) {
		n->next[h] = path[h]->next[h]; //initialize x's next pointers
		path[h]->next[h] = n; // update next pointers that change
	}
}

// prints index of words, counts and pages
void printIndex(ofstream& out)
{
	printNodes(*(head->next), out);
}

// Prints all the nodes
void printNodes(node* n, ofstream& out)
{
	if (n) {
		printWord(n->w, out);
		printNodes(*(n->next), out);
	}
}

// Prints a word with its count and page numbers
void printWord(word* w, ofstream& out)
{
	out << w->name << " (" << w->count << ") ";
	printPages(*(w->pages), out);
	out << endl; 
}

// prints the pages vector
void printPages(vector<int> pages, ofstream& out)
{
	vector<int>::iterator it = pages.begin();
	out << *it;
	bool consecutive = false; // whether the pages we are evaluating are consecutive
	int prev = *it;
	it++;
	while (it != pages.end()){
		if (consecutive){ 
			if (prev+1 == *it){ 
				prev = *it;
				it++;
			}else {
				out << "-" << prev; 
				consecutive = false;
			}
		}else {
			if (prev+1 == *it){ 
				consecutive = true;
				prev = *it;
				it++;
			}else {
				out << "," << *it;
				it++;
			}
		}
	}
	if (consecutive) {
		out << "-" << prev;		
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

// initializes the skip list, creating a head node
void init_head()
{
	head = new node;
	head->height = MAX_HEIGHT;
	for (int i = 0; i < head->height; ++i)
	{
		head->next[i] = NULL;
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
	ofstream out(argv[2]); 
	string s;

	init_head();
	parseBook(in);
	printIndex(out);

	return 0;
}
			