#include "freqq.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int FreqQ::hash(string word){
	int h = word[0];
	for (unsigned int i = 1; i < word.length(); ++i)
	{
		h = (31 * h + word[i]) & (HASHTAB_SIZE - 1);
	}
	return h;
}

void FreqQ::swap(int i, int j){
	hashTab[heap[i].hashIndex].heapIndex = j;
	hashTab[heap[j].hashIndex].heapIndex = i;
	HeapEntry tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
}

int FreqQ::hashFind(string word){
	int h = hash(word);
	for (int i = 1; i < HASHTAB_SIZE/2; ++i){ //quadratic probing: after probing half repeats.
		HashEntry entry = hashTab[h];
		if (entry.heapIndex == EMPTY) return -1;
		if (entry.heapIndex != TOMBSTONE && entry.name == word) return h;
		h = (h + 2*i -1) % HASHTAB_SIZE;
	}
	return -1;
}

bool FreqQ::hashInsert(string word){
		int h = hash(word);
	for (int i = 1; i < HASHTAB_SIZE/2; ++i)
	{
		HashEntry entry = hashTab[h];
		if (entry.heapIndex == EMPTY || entry.heapIndex == TOMBSTONE){
			hashTab[h].name = word;
			heap[heapSize].freq = 1;
			heap[heapSize].hashIndex = h;
			hashTab[h].heapIndex = heapSize++;
			return true;
		}
	
		h = (h + 2*i -1) % HASHTAB_SIZE;
	}
	return false;
}

int FreqQ::swapUp(int i){
	if (i == 0) return 0;
	int parent = (i-1)/2;
	if (heap[parent].freq < heap[i].freq){
		swap(i, parent);
		return swapUp(parent);
	}else{
		return i;
	}

}

void FreqQ::swapDown(int i){
	int left = (2 * i) + 1;
	int right = left + 1;
	int s = i;
	if (left < heapSize && heap[left].freq > heap[i].freq){
		s = left;
	}
	if (right < heapSize && heap[right].freq > heap[s].freq){
		s = right;
	}

	if (s!=i){
		swap(s, i);
		swapDown(s);
	}
}

bool FreqQ::add(string word){
	int i = hashFind(word);
	if (i != -1){
		int heapi = hashTab[i].heapIndex;
		heap[heapi].freq += 1;
		swapDown(swapUp(heapi));
		return true;
	}
	return hashInsert(word);
}

bool FreqQ::sub(string word){
	int i =  hashFind(word);
	if (i != -1){
		int heapi = hashTab[i].heapIndex;
		heap[heapi].freq -= 1;
		if (heap[heapi].freq == 0){
			heapRemove(heapi);
			hashRemove(i);
			return true;
		}
		swapDown(heapi);
		return true;
	}
	return false;
}

string FreqQ::topWord(){
	return hashTab[heap[0].hashIndex].name;
}

int FreqQ::topFreq(){
	return heap[0].freq;
}

void FreqQ::heapRemove(int i){
	swap(i, heapSize-1);
	if (swapUp(i)==i){
		swapDown(i);
	}
	heapSize--;
}

void FreqQ::hashRemove(int i){
	hashTab[i].heapIndex = TOMBSTONE;
}
