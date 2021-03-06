#include "Dictionary.h"
#include "SerialInterface.h"
#include "Settings.h"
#include "GyroscopeState.h"
#include "Comparitor.h"

using std::cin;

static queue<Frame> frameQueue;
static mutex queueMutex;
static SerialInterface serial = SerialInterface(&frameQueue, &queueMutex);
static Dictionary* dictionary;
static GyroscopeState leftGyro;
static GyroscopeState rightGyro;
Comparitor comparitor;

bool process(Frame* frame);
void recordGesture(Word& newWord, int duration);
string readValue(string parameters[]);
string readContains(string parameters[]);
float readNumber();
bool readOption(string parameters[], int index);

int main() {
	serial.start();
	serial.pause();

	// Start interface code.
	cout << "+----------------------------------+\n";
	cout << "| Sign Language Translation Gloves |\n";
	cout << "+----------------------------------+\n\n";

	cout << "Select dictionary mode.\n";
	cout << "------------------------\n\n";
	cout << "  * Create new dictionary. (1)\n";
	cout << "  * Load dictionary from file. (2)\n";
	
	{
		cout << "Enter option: ";
		string parameters[]{ "1", "2" };
		string value = readValue(parameters);
		if (value == "1") {
			dictionary = new Dictionary();
		}
		else {
			string extension[]{ ".dsf" };
			cout << "Enter dictionary file name (.dsf): ";
			string path = readContains(extension);
			dictionary = Dictionary::load(path.c_str());
			while (dictionary == nullptr) {
				cout << "Invalid file name. Try again or press q to quit: ";
				cin >> path;
				if (path == "q") {
					cout << "Creating new dictionary instead...\n";
					dictionary = new Dictionary();
					break;
				}
				dictionary = Dictionary::load(path.c_str());
			}
		}
	}

	cout << "\n\nSelect operating mode.\n";
	cout << "-----------------------\n\n";
	cout << "  * Dictionary programming mode. (1)\n";
	cout << "  * Translation mode. (2)\n";

	{
		cout << "Enter option: ";
		string parameters[]{ "1", "2" };
		string hands[]{ "1", "2", "3" };
		string choice[]{ "y", "yes", "n", "no" };
		string value = readValue(parameters);
		string type;
		int duration;
		bool persist;
		if (value == "1") {
			cout << "\n\nProgramming mode.\n";
			cout << "--------------------\n\n";

			do {
				cout << "Enter word: ";
				cin >> value;
				cout << "Enter approximate duration (ms): ";
				duration = static_cast<int>(readNumber());
				cout << "Which hands does this use? Left, right, or both? (1, 2, 3): ";
				type = readValue(hands);
				Word newWord(value, stoi(type));
				cout << "Prepare to record the word.\n";
				cout << "You will have the amount of time you previously entered.\n";
				cout << "The recording will start after a 15 second countdown.\n";
				for (int count = 0; count < 15; ++count) {
					cout << std::to_string(count) << "\n";
					Sleep(1000);
				}
				cout << "Starting recording.\n";
				recordGesture(newWord, duration);
				cout << "\nDo you want to add the word to the dictionary? (y/n): ";
				if (readOption(choice, 1)) {
					dictionary->add(newWord);
				}
				cout << "Do you want to record another word? (y/n): ";
				persist = readOption(choice, 1);
			} while (persist);
		}
		else {
			cout << "\n\nTranslation mode.\n";
			cout << "--------------------\n\n";
			serial.start();
			while (true) {
				Frame readFrame;
				if (process(&readFrame)) {
					dictionary->match(readFrame);
				}
			}
		}
	}
}

void recordGesture(Word& newWord, int duration) {
	serial.start();
	while (duration > 0) {
		duration -= RECORD_READ_RATE;
		Sleep(RECORD_READ_RATE);
		Frame readFrame;
		if (process(&readFrame)) {
			newWord.add(readFrame);
		}
	}
	serial.pause();
}

bool process(Frame* frame) {
	lock_guard<mutex> guard(queueMutex);
	if (!frameQueue.empty()) {
		Frame frameIn = frameQueue.front();

		Snapshot leftSnap = frameIn.left;
		Snapshot rightSnap = frameIn.right;

		leftGyro.inputData(leftSnap.gyroX, leftSnap.gyroY, leftSnap.gyroZ);
		rightGyro.inputData(rightSnap.gyroX, rightSnap.gyroY, rightSnap.gyroZ);

		*frame = frameIn;

		frame->left.gyroX = leftGyro.getX();
		frame->left.gyroY = leftGyro.getY();
		frame->left.gyroZ = leftGyro.getZ();

		frame->right.gyroX = rightGyro.getX();
		frame->right.gyroY = rightGyro.getY();
		frame->right.gyroZ = rightGyro.getZ();

		frameQueue.pop();
		
		return true;
	}
	return false;
}

// --------------------------------------------
//			    Interface Code				  |
// --------------------------------------------

void lower(string& text) {
	for (string::iterator i = text.begin(); i != text.end(); ++i) {
		if (*i >= 'A' && *i <= 'Z') {
			*i += 32;
		}
	}
}

bool checkValue(string parameters[], string value) {
	bool failed = true;
	for (int i = 0; i < sizeof(parameters) / sizeof(string); ++i) {
		failed = failed && (value != parameters[i]);
	}
	return failed;
}

bool containsValue(string parameters[], string value) {
	bool failed = true;
	for (int i = 0; i < sizeof(parameters) / sizeof(string); ++i) {
		failed = failed && (value.find(parameters[i]) != string::npos);
	}
	return failed;
}

bool readOption(string parameters[], int index) {
	string option;
	cin >> option;
	lower(option);
	while (checkValue(parameters, option)) {
		cout << "\nInvalid input. Try again: ";
		cin >> option;
	}
	for (int i = 0; i <= index; ++i) {
		if (option == parameters[i]) {
			return true;
		}
	}
	return false;
}

string readValue(string parameters[]) {
	string option;
	cin >> option;
	lower(option);
	while (checkValue(parameters, option)) {
		cout << "\nInvalid input. Try again: ";
		cin >> option;
	}
	return option;
}

string readContains(string parameters[]) {
	string option;
	cin >> option;
	lower(option);
	while (containsValue(parameters, option)) {
		cout << "\nInvalid input. Try again: ";
		cin >> option;
	}
	return option;
}

float readNumber() {
	string option;
	cin >> option;
	for (string::iterator i = option.begin(); i != option.end(); ++i) {
		if (*i >= '0' && *i <= '9') {
			return stof(option);
		}
	}
	return -1;
}


// To do.

/*
	* Write the .dsf file writer / reader.
*/