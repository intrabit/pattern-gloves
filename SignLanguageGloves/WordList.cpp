#include "WordList.h"
// The dictionary is made up of word lists. Each word list has the ability to refine itself. A frame is given to the word list along with an index.
// The word list goes through its list of words and checks which words have a matching frame for that index. If a word doesn't match then it removes
// it from the word list. If the word list contains only one word it will return true, otherwise it will return false.

// When creating the dictionary, it must create a new word list as the refined list each time and gradually reduce it.

WordList::WordList(WordList& copy) {
	words = new Word[copy.wordCount];
	for (int i = 0; i < copy.wordCount; ++i) {
		words[i] = copy.words[i];
	}
	wordCount = copy.wordCount;
}

void WordList::remove(int index) {
	if (wordCount - 1 <= 0) {
		delete[] words;
		words = nullptr;
		wordCount = 0;
		return;
	}
	Word* temp = new Word[--wordCount];
	while (index < wordCount) {
		words[index] = words[index + 1];
		index++;
	}
	for (index = 0; index < wordCount; ++index) {
		temp[index] = words[index];
	}
	delete[] words;
	words = temp;
}

// If this causes a problem replace temp[wordCount++] = word with temp[wordCount++] = Word(word);
void WordList::add(Word word) {
	Word* temp = new Word[wordCount + 1];
	for (int i = 0; i < wordCount; ++i) {
		temp[i] = words[i];
	}
	temp[wordCount++] = word;
	delete[] words;
	words = temp;
}

// Returns whether the list should be refined any more.
bool WordList::refine(Frame frame, int index) {
	for (int i = 0; i < wordCount; ++i) {
		if (!words[i].match(frame, index)) {
			remove(i);
		}
	}
	return wordCount != 1 && wordCount != 0;
}