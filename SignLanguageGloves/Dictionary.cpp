#include "Dictionary.h"
#include "TextHandler.h"
#include "DictionaryFileHandler.h"

void Dictionary::match(Frame frame) {
	if (refined == nullptr) {
		refined = new WordList(mainList);
	}
	if (refined->refine(frame, index)) {
		index++;
	}
	else {
		Word* foundWord = refined->getWord();
		if (foundWord != nullptr) {
			TextHandler::addWord(foundWord->getText());
		}
		index = 0;
		delete refined;
		refined = nullptr;
	}
}


void Dictionary::save(Dictionary* dict, const char* filename) {
	DictionaryFileHandler::writeDictionaryFile(dict, filename);
}

Dictionary* Dictionary::load(const char* filename) {
	return DictionaryFileHandler::readDictionaryFile(filename);
}