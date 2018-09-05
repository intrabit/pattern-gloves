#include "SerialInterface.h"
#include "Settings.h"

// TODO: Create a mutex locked error printing system so errors from the interface
//		 aren't printed randomly while other threads are trying to print. (Non-vital)

void SerialInterface::process() {
	DCB dcb;
	COMMTIMEOUTS timeouts;
	timeouts.ReadIntervalTimeout = READ_TIMEOUT;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	HANDLE portHandle = CreateFile(
		COM_PORT.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (portHandle == INVALID_HANDLE_VALUE) {
		cout << "Error: Problem with port connection.\n";
		cout << "Try reconnecting the transceiver and check the port name is correct.\n\n";
		return;
	}
	if (!GetCommState(portHandle, &dcb)) {
		cout << "Error: Unable to get port state.\n";
		CloseHandle(portHandle);
		return;
	}
	dcb.BaudRate = BAUD_RATE;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	if (!SetCommState(portHandle, &dcb)) {
		cout << "Error: Unable to set port state.\n";
		CloseHandle(portHandle);
		return;
	}
	if (!SetCommTimeouts(portHandle, &timeouts)) {
		cout << "Error: Cannot set timeouts.\n";
		cout << "Try checking the READ_TIMEOUT setting in the settings file.\n\n";
		CloseHandle(portHandle);
		return;
	}
	char buffer[256];
	string data;
	DWORD portEvent = 0;
	SetCommMask(portHandle, EV_RXCHAR);
	while (status != 3) {
		if (status == 1) {
			DWORD bytesRead;
			WaitCommEvent(portHandle, &portEvent, NULL);
			ReadFile(portHandle, buffer, 256, &bytesRead, NULL);
			for (int i = 8; i < bytesRead - 1; ++i) {
				data += buffer[i];
			}
			Frame frame;
			string left = data.substr(0, 40);
			string right = data.substr(40);
			Snapshot sLeft;
			Snapshot sRight;
			createSnapshot(&sLeft, left);
			createSnapshot(&sRight, right);
			frame.left = sLeft;
			frame.right = sRight;
			lock_guard<mutex> guard(*queueMutex);
			frameQueue->push(frame);
			data = "";
		}
	}
}

void SerialInterface::start() {
	if (status == 4) {
		worker = thread(&SerialInterface::process, this);
	}
	status = 1;
}

void SerialInterface::stop() {
	status = 3;
	worker.join();
}

// A potential problem with this system could be the start and pause methods. If the connection is paused then it may simply store data in
// the serial buffer and when it's started again, all that data could be read instead of new data that's just come in.
