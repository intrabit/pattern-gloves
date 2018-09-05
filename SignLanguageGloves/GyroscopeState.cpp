#include "GyroscopeState.h"
#include "Settings.h"

void GyroscopeState::inputData(float xVel, float yVel, float zVel) {
	float sampleRateSeconds = SAMPLE_RATE / 1000.0f;
	xVel *= sampleRateSeconds;
	yVel *= sampleRateSeconds;
	zVel *= sampleRateSeconds;

	if (abs(prevX - xVel) > GYRO_BIAS) {
		if (x + xVel >= 360.0f) {
			x = (x + xVel) - 360.0f;
		}
		else if (x + xVel < 0) {
			x = (x + xVel) + 360.0f;
		}
		else {
			x += xVel;
		}
	}

	if (abs(prevY - yVel) > GYRO_BIAS) {
		if (y + yVel >= 360.0f) {
			y = (y + yVel) - 360.0f;
		}
		else if (y + yVel < 0) {
			y = (y + yVel) + 360.0f;
		}
		else {
			y += yVel;
		}
	}

	if (abs(prevZ - zVel) > GYRO_BIAS) {
		if (z + zVel >= 360.0f) {
			z = (z + zVel) - 360.0f;
		}
		else if (z + zVel < 0) {
			z = (z + zVel) + 360.0f;
		}
		else {
			z += zVel;
		}
	}

	prevX = xVel;
	prevY = yVel;
	prevZ = zVel;
}