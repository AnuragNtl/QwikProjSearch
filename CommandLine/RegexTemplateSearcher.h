#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	class RegexTemplateSearcher : public Searcher {
	private:
		char* getFileData(string fileName, int &len);
	public:
		vector<SearchResults> searchFor(char *, vector<string>);
		vector<SearchResults> searchFor(string filePath, vector<string>);
	};
};
#endif

