#ifndef SEARCHER_H
#define SEARCHER_H

namespace ProjSearch {
	struct SearchResults {

		string filePath;
		int row, col;
		int offset;
		int fileType;
	};

	class Searcher {
	protected:
		char *data;
	public:
		Searcher(string filePath);
		Searcher(char *data);
		virtual vector<SearchResults> searchFor(vector<string>) { return vector<SearchResults>();}
		~Searcher();
	};
};


#endif
