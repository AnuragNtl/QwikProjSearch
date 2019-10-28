#include "Searcher.h"
#include <fstream>

using namespace ProjSearch;
using namespace std;

SearchResults :: SearchResults(string filePath, int row, int col, int offset, int fType) : filePath(filePath), row(row), col(col), offset(offset), fileType(fType) {}

void Searcher :: readFromPath(string filePath) {
  this->filePath = filePath;
	ifstream in(filePath.c_str());
	string fileData = "";
	char *buffer = new char[1024];
	while(!in.eof()) {
		in.read(buffer, 1023);
		int readCount = in.gcount();
		buffer[readCount] = '\0';
		fileData = fileData + buffer;
	}
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

string replace(string inString, string oldValue, string newValue) {
  int findIndex = 0;
  int len = oldValue.size();
  do {
    findIndex = inString.find(oldValue, findIndex + 1);
    if(findIndex != string::npos) {
      inString.replace(findIndex, len, newValue);
    }
  } while(findIndex != string::npos);
  return inString;
}

