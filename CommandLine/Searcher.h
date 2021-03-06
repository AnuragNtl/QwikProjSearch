#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define DEFAULT_LINE_SEPERATOR "\n";

namespace ProjSearch {
	struct SearchResults {
		SearchResults(int row, int col, int, int, string);
		SearchResults(int row, int col, int offset) : row(row), col(col) {
			this->offset = offset;
		}
		string filePath;
		int row, col;
		int offset;
		int fileType;
		static string lineSeperator;
		static void setRowAndCol(string source, int offset, int &row, int &col);
    string match;
    operator string();
	};



	class Searcher {
    protected:
      string filePath;
	public:
		virtual vector<SearchResults> searchFor(const char *data, const vector<string>) const {  return vector<SearchResults>();}
    void readFromPath(string);
		~Searcher();
	};
  string replace(string, string, string);
  string getContents(string);
};


#endif
