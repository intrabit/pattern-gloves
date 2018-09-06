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
