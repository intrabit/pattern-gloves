#include "Word.h"
#include "Comparitor.h"

extern Comparitor comparitor;

// Deep copy.
Word::Word(Word& copy) {
	frames = new Frame[copy.frameCount];
	for (int i = 0; i < copy.frameCount; ++i) {
		frames[i] = copy.frames[i];
	}
	word = copy.word;
	type = copy.type;
	frameCount = copy.frameCount;
}

bool Word::match(Frame frame, int index) {
	return comparitor.compare(&frame, this, index);
}

void Word::add(Frame frame) {
	Frame* temp = new Frame[frameCount + 1];
	for (int i = 0; i < frameCount; ++i) {
		temp[i] = frames[i];
	}
	temp[frameCount++] = frame;
	delete[] frames;
	frames = temp;
}