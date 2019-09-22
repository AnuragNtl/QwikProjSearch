#include "Searcher.h"

using namespace ProjSearch;

SearchResults :: SearchResults(string filePath, int row, int col, int offset, int fType) : filePath(filePath), row(row), col(col), offset(offset), fileType(fType) {}

Searcher :: Searcher(char *data) {
	this->pData = data;	
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

Searcher :: ~Searcher() {
	delete[] pData;
}

void SearchResults :: setRowAndCol(string source, int offset, int &row, int &col) {
	int count = 0, pPosition = 0;
	for(int i = 0; i != string::npos; i = source.find(lineSeperator, i) ) {
		pPosition = i;
		count++;
	}
	col = offset - pPosition;
	row = count;
}
