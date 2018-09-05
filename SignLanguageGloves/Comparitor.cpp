#include "Comparitor.h"
#include "Settings.h"

Comparitor::Comparitor() {
	left = TransitionalCompensator(1);
	right = TransitionalCompensator(2);
}

bool Comparitor::checkDifference(float value1, float value2) {
	return (abs(value1 - value2) / ((value1 + value2) / 2)) <= GYRO_COMPARE_TOLERANCE;
}

bool Comparitor::checkGyros(Snapshot* s1, Snapshot* s2) {
	return checkDifference(s1->gyroX, s2->gyroX) &&
		checkDifference(s1->gyroY, s2->gyroY) &&
		checkDifference(s1->gyroZ, s2->gyroZ);
}

bool Comparitor::compare(Frame* frame, Word* word, int index) {
	bool gyroMatch = true;
	bool fingerMatch = true;
	int type = word->type;
	if (type == 1 || type == 3) {
		// Left.
		gyroMatch = gyroMatch && checkGyros(&frame->left, &word->frames[index].left);
		fingerMatch = fingerMatch && left.compare(frame, word->frames, index, word->frameCount);
	}
	else if (type == 2 || type == 3) {
		// Right.
		gyroMatch = gyroMatch && checkGyros(&frame->right, &word->frames[index].right);
		fingerMatch = fingerMatch && right.compare(frame, word->frames, index, word->frameCount);
	}
	return gyroMatch && fingerMatch;
}

// Getting in is very important for me. I've been working tirelessly on this project.