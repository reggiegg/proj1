#include <string>
#define EMPTY -1
#define TOMBSTONE -2


class FreqQ{


	// an entry in the frequency heap with the index
	// of the associated hash table entry
	typedef struct
	{
		int freq;
		int hashIndex;
	}HeapEntry; 

	// an entry in the hash table with the index
	// of the associated frequency heap entry
	
	typedef struct
	{
		std::string name;
		int heapIndex;
	}HashEntry;

	// assume that the max number of values is going to be 2^15
	static const int HASHTAB_SIZE = 65536; //2^16



	public:

		HashEntry hashTab[HASHTAB_SIZE];
		HeapEntry heap[HASHTAB_SIZE/2];
		int heapSize;
		
		// constructor
		FreqQ() {

			heapSize = 0;
			for (int i = 0; i < HASHTAB_SIZE; ++i){
				hashTab[i].heapIndex = EMPTY;
			}
		}

		// increment frequency count of word if it is in hash table
		// if not, add the word and set the count as 1 return true if successful
		bool add(std::string word);

		// decrement the frequency count if word is in has table,
		// remove it if count is 1, if it's not there return false.
		bool sub(std::string word);

		// return the word with the highest frequency
		std::string topWord();

		// return the count of the most frequent word
		int topFreq();

	private:

		// remove HashEntry at index i from hashtable at index i and replace it with a tombstone
		void hashRemove(int i);

		// assigns an index for an entry
		int hash(std::string word);

		// find the word in the hash table and return the index or -1 if it is not in the table
		int hashFind(std::string word);

		// insert a value into the hash table and updates the heap freq count
		// returns true if it is successful
		bool hashInsert(std::string word);

		// remove HeapEntry at index i from heap
		void heapRemove(int i);

		// swap entries in the heap, and updates the appropriate hashtable indices
		void swap(int i, int j);

		// continually swaps a heap entry with it's parent, until it's at the correct height,
		// returns index of new position
		int swapUp(int i);

		// continually swaps a heap entry with it's children until it's at the correct height
		void swapDown(int i);


};