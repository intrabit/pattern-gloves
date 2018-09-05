#pragma once
#include "Frame.h"
#include "Word.h"
#include "TransitionalCompensator.h"

class Comparitor {
private:
	TransitionalCompensator left;
	TransitionalCompensator right;
	bool checkDifference(float value1, float value2);
	bool checkGyros(Snapshot* s1, Snapshot* s2);
public:
	Comparitor();
	bool compare(Frame* frame, Word* word, int index);
};

// Only pass in words that use left hands for the left compensator and right hands for the right compensator.
// When using words that use both, pass the left snapshot of the frame into the left and the right into the right and
// logically and their results.
