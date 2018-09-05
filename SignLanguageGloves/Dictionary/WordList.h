#pragma once
#include "Word.h"

class WordList {
private:
	Word* words;
	int wordCount;
	void remove(int index);
public:
	WordList() : words(nullptr), wordCount(0) { }
	WordList(WordList& copy);
	void add(Word word);
	bool refine(Frame frame, int index);
	Word* getWord() { return words; }
	~WordList() { delete[] words; }
};
