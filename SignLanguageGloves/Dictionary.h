#pragma once
#include "WordList.h"

class Dictionary {
private:
	WordList* refined;
	WordList mainList;
	int index;
public:
	Dictionary() : refined(nullptr), index(0) { }
	void match(Frame frame);
	inline void add(Word word) { mainList.add(word); }
	static Dictionary* load(const char* filename);
	static void save(Dictionary* dict, const char* filename);
};