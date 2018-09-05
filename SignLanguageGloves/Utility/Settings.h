#pragma once
#include <string>

using std::wstring;

static const int BAUD_RATE = 9600; // The baud rate of the serial connection.
static const wstring COM_PORT = L"COM5"; // The port the radio module is connected to.
static const int READ_TIMEOUT = 10; // Set to 0 for blocking.
static const int RECORD_READ_RATE = 10; // How often to take frames from the queue for processing while recording words.
static const int SAMPLE_RATE = 500; // The amount of time between samples (ms)
static const float GYRO_BIAS = 2.0f; // The expected amount of error for the gyroscope.
static const int MAX_POC_DIST = 10; // Max distance between POC and index for early check.
static const int TRUST_EXPIRY = 5; // Standard length for a late check trust to last.
static const float GYRO_COMPARE_TOLERANCE = 0.7f; // The percentage match between two gyroscope values required.

// Note for future: Have the program use the XBee C++ files to transmit the settings to the gloves so they can all be set
// here from the computer.
