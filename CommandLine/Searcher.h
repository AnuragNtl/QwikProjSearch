#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <vector>

using namespace std;

#define DEFAULT_LINE_SEPERATOR "\n";

namespace ProjSearch {
	struct SearchResults {
		SearchResults(string filePath, int row, int col, int, int);
		SearchResults(int row, int col, int offset) : row(row), col(col) {
			this->offset = offset;
		}
		string filePath;
		int row, col;
		int offset;
		int fileType;
		static string lineSeperator;
		static void setRowAndCol(string source, int offset, int &row, int &col);
	};

	string SearchResults :: lineSeperator = DEFAULT_LINE_SEPERATOR;


	class Searcher {
	protected:
		char *pData;
	public:
		virtual vector<SearchResults> searchFor(char *data, vector<string>) { return vector<SearchResults>();}
		~Searcher();
	};
};


#endif
