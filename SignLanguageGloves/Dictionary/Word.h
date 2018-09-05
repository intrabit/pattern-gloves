#pragma once
#include "Frame.h"
#include <string>

using std::string;

class Word {
private:
	Frame* frames;
	string word;
	int frameCount;
	int type;
	friend class Comparitor;
public:
	Word() { }
	Word(string word, int type) : frames(nullptr), frameCount(0), word(word), type(type) { }
	Word(Word& copy);
	bool match(Frame frame, int index);
	void add(Frame frame);
	inline string getText() { return word; }
	~Word() { delete[] frames; }
};
