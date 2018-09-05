#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>
#include <iostream>
#include <string>
#include "Frame.h"

using std::thread;
using std::mutex;
using std::queue;
using std::lock_guard;
using std::cout;
using std::string;

class SerialInterface {
private:
	char status;
	long frames;
	thread worker;
	mutex* queueMutex;
	queue<Frame>* frameQueue;
	void process();
public:
	SerialInterface(queue<Frame>* frameQueue, mutex* queueMutex) : queueMutex(queueMutex), frameQueue(frameQueue), status(4) { }
	void start();
	void pause() { status = 2; }
	void stop();
	long getTotalFrameCount() { return frames; }
};

// Status states: 1 = running, 2 = paused, 3 = stopped, 4 = not initialised.