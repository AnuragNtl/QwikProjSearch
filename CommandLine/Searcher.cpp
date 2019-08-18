#include "Searcher.h"

using namespace ProjSearch;

Searcher :: Searcher(char *data) {
	this->data = data;	
}

Searcher :: Searcher(string filePath) : data(NULL) {
	readFromPath(filePath);
}

void Searcher :: readFromPath(string filePath) {
	ifstream in(filePath.c_str());
	string fileData = "";
	char *buffer = new char[1024];
	while(!in.eof()) {
		in.read(buffer, 1023);
		int readCount = in.gcount();
		buffer[readCount] = '\0';
		fileData = fileData + buffer;
	}
	if(data != NULL) {
		delete[] data;
	}
	data = new char[fileData.size() + 1];
	strcpy(data, fileData.c_str());
}
