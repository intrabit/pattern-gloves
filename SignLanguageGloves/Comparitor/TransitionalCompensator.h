#pragma once
#include "Word.h"

class TransitionalCompensator {
private:
	bool trust;
	int trustExpiry;
	int type;
	bool compareFingers(Snapshot* s1, Snapshot* s2);
	int pocFinder(Frame* wordFrames, int frameCount, int index);
	bool earlyCheck(Frame* frame, Frame* wordFrames, int frameCount, int index);
public:
	TransitionalCompensator() { }
	TransitionalCompensator(int type) : type(type) { }
	bool compare(Frame* frame, Frame* wordFrames, int index, int frameCount);
};
