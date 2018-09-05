#include "TextHandler.h"

string TextHandler::text = "";
int TextHandler::wordCount = 0;

void TextHandler::addWord(string word) {
	text += word;
	cout << text << std::endl;
}
