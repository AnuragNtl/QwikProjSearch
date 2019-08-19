#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <vector>

using namespace std;

namespace ProjSearch {
	struct SearchResults {

		SearchResults(string filePath, int row, int col, int, int);
		string filePath;
		int row, col;
		int offset;
		int fileType;
	};

	class Searcher {
	private:
		void readFromPath(string filePath);
	protected:
		char *dPata;
	public:
		Searcher(string filePath);
		Searcher(char *data);
		virtual vector<SearchResults> searchFor(vector<string>) { return vector<SearchResults>();}
		~Searcher();
	};
};


#endif
