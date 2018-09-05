#include "TransitionalCompensator.h"
#include "Settings.h"

// Returns true if both snapshot's fingers match each other.
bool TransitionalCompensator::compareFingers(Snapshot* s1, Snapshot* s2) {
	return s1->f1 == s2->f1 && s1->f2 == s2->f2 && s1->f3 == s2->f3 &&
		s1->f4 == s2->f4 && s1->f5 == s2->f5;
}

// pocFinder should only find a POC for a certain snapshot.
int TransitionalCompensator::pocFinder(Frame* wordFrames, int frameCount, int index) {
	Snapshot* previous = nullptr;
	for (int i = index; i < frameCount; ++i) {
		Frame* frame = wordFrames + i;
		switch (type) {
		case 1:
			if (previous != nullptr && !compareFingers(previous, &frame->left)) {
				return i;
			}
			previous = &frame->left;
			break;
		case 2:
			if (previous != nullptr && !compareFingers(previous, &frame->right)) {
				return i;
			}
			previous = &frame->right;
			break;
		}
	}
	return -1;
}

bool TransitionalCompensator::earlyCheck(Frame* frame, Frame* wordFrames, int frameCount, int index) {
	int poc = pocFinder(wordFrames, frameCount, index);
	return poc != -1 ? (poc - index) <= MAX_POC_DIST : false;
}

bool TransitionalCompensator::compare(Frame* frame, Frame* wordFrames, int index, int frameCount) {
	if (trust) {
		if (trustExpiry > 0) {
			trustExpiry -= 1;
			return true;
		}
		else {
			trust = false;
		}
	}
	bool matched = false;
	if (type == 1) {
		matched = compareFingers(&frame->left, &wordFrames[index].left);
	}
	else if (type == 2) {
		matched = compareFingers(&frame->right, &wordFrames[index].right);
	}
	if (!matched) {
		if (earlyCheck(frame, wordFrames, frameCount, index)) {
			return true;
		}
		else {
			// This code wouldn't run if the gyros didn't match.
			trust = true;
			trustExpiry = TRUST_EXPIRY;
		}
	}
	return matched;
}

// Upgrade: Make the program check to see if the word's frame at the index is a point of change. 
//			If it is, then do the trust. Otherwise there's no point. 


/*
if (trust) {
if (trustExpiry > 0) {
trustExpiry -= 1;
return true;
}
else {
trust = false;
}
}
bool matched = false;
if (word->type == 1) {
matched = compareFingers(&frame->left, &word->frames[index].left);
}
else if (word->type == 2) {
matched = compareFingers(&frame->right, &word->frames[index].right);
}
else {
matched = compareFingers(&frame->left, &word->frames[index].left)
&& compareFingers(&frame->right, &word->frames[index].right);
}
if (!matched) {
if (earlyCheck(frame, word, index)) {
return true;
}
else {
if (gyroStatus) {
trust = true;
trustExpiry = TRUST_EXPIRY;
}
}
}
return matched;
*/