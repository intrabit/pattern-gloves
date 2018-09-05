#pragma once
#include "Dictionary.h"

class DictionaryFileHandler {
public:
	static void writeDictionaryFile(Dictionary* dict, const char* filename);
	static Dictionary* readDictionaryFile(const char* filename);
};

