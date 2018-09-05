#pragma once
#include <string>

using std::string;

struct Snapshot {
	bool f1;
	bool f2;
	bool f3;
	bool f4;
	bool f5;
	float accelX;
	float accelY;
	float accelZ;
	float gyroX;
	float gyroY;
	float gyroZ;
};

struct Frame {
	Snapshot left;
	Snapshot right;
};

void createSnapshot(Snapshot* snapshot, string data);