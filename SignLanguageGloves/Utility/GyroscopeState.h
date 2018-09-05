#pragma once

class GyroscopeState {
private:
	float x, y, z;
	float prevX, prevY, prevZ;
public:
	GyroscopeState() : x(0), y(0), z(0), prevX(0), prevY(0), prevZ(0) { }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void inputData(float xVel, float yVel, float zVel);
};
