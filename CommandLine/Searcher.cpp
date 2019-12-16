#include "Searcher.h"
#include <fstream>
#include <sstream>

using namespace ProjSearch;
using namespace std;

SearchResults :: SearchResults(int row, int col, int offset, int fType, string match) : row(row), col(col), offset(offset), fileType(fType), match(match) {}

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
	int count = 1 , pPosition = 0;
	for(int i = source.find(lineSeperator, 0); i != string::npos && i < offset ; i = source.find(lineSeperator, ++i)) {
		pPosition = i + 1;
		count++;
	}
	col = offset - pPosition;
	row = count;
}

namespace ProjSearch {
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
}


string SearchResults :: lineSeperator = DEFAULT_LINE_SEPERATOR;


Searcher :: ~Searcher() {}

namespace ProjSearch {
string getContents(string fileName) {
  ifstream in(fileName.c_str());
  string buf;
  string s = "";
  getline(in, buf);
  while(!in.eof()) {
    s = s +  buf;
    getline(in, buf);
    if(!in.eof()) 
      s = s + "\n";
  }
  in.close();
  return s;
}

};


SearchResults :: operator string() {
  ostringstream out;
  out << "SearchResult( filePath = " << this->filePath << "(row, col) = (" << row <<"," << col
    << ")" << " offset = " << offset << " match = " << match << " fileType = " <<fileType << ")";
  return out.str();
}

