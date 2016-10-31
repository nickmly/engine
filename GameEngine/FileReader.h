#pragma once
#include <iostream>
#include "LogManager.h"
using namespace std;
LogManager* lm = LogManager::getInstance();
class FileReader {
public:
	static char* ReadFromFile(char* filename) { 
		FILE* file;
		fopen_s(&file, filename, "rb");
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* src = new char[length + 1];
		fread(src, 1, length, file);
		fclose(file);
		return src;
	}
};