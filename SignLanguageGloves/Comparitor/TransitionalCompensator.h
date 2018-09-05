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

// Assumptions: 
/*
	* earlyCheck is only called if the current snapshot given is of a point of change.
	* 
	
*/


/*

	A frame should be given instead of a snapshot because the word will have frames instead of snapshots.
	That way only the hands specified in the word will be checked.

	The word has a type int which specifies which hands the word uses.
	The early check should only check the required hands specified in the word.

	A compensator only works for one hand!

	The early and late systems will work for a single hand. Two compensators will be required; one for the left and one for the right.
	Instead of a word, we pass a list of frames and the size of the word. That way we don't have to worry about passing any type data.


*/
