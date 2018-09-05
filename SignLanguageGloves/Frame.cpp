#include "Frame.h"

void createSnapshot(Snapshot* snapshot, string data) {
	snapshot->f1 = data.at(0) == '1';
	snapshot->f2 = data.at(1) == '1';
	snapshot->f3 = data.at(2) == '1';
	snapshot->f4 = data.at(3) == '1';
	snapshot->f5 = data.at(4) == '1';
	snapshot->accelX = stof(data.substr(5, 5));
	snapshot->accelY = stof(data.substr(10, 5));
	snapshot->accelZ = stof(data.substr(15, 5));
	snapshot->gyroX = stof(data.substr(20, 5));
	snapshot->gyroY = stof(data.substr(25, 5));
	snapshot->gyroZ = stof(data.substr(30, 5));
}