#ifndef PROJ1_H_
#define PROJ1_H_

#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>



void parseBook(std::ifstream& in);
void printIndex(std::ofstream& out);
void lowercaseWords(std::string& line);
void updateIndex(std::string word, int page, int begin, int end);

// Represents a word from the book. name is the word, count is the number 
// of times it shows up, and pages is the page numbers it occurs on.
typedef struct {
	std::string name;
	int count;
	std::vector<int> *pages;
} word;




#endif