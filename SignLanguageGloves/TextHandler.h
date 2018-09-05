#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class TextHandler {
private:
	static string text;
	static int wordCount;
public:
	static void addWord(string word);
};