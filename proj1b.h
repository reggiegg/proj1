#ifndef PROJ1_H_
#define PROJ1_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

const int MAX_HEIGHT = 16;


// Represents a word from the book. name is the word, count is the number 
// of times it shows up, and pages is the page numbers it occurs on.
typedef struct {
	std::string name;
	int count;
	std::vector<int> *pages;
} word;

typedef struct node{
	int height;
	node* next[MAX_HEIGHT];
	word* w;
} node;



void parseBook(std::ifstream& in);
node* find(std::string wd, node* skiplist, int index);
node* make_node(std::string wd, int page);
void update_pointers(node* n);
void pushPages(word *w, int num);
void updateIndex(std::string word, int page);
void update_word(word* w, int page);
int randBit(void);
void init_head();
void make_height(node* n);
void printPages(std::vector<int> pages, std::ofstream& out);
void printIndex(std::ofstream& out);
void printWord(word* w, std::ofstream& out);
void printNodes(node* n, std::ofstream& out);
void lowercaseWords(std::string& line);





#endif