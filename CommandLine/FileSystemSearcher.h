#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	class FileSystemSearcher : public Searcher {
	private:
		string filePath;
	public:
		FileSystemSearcher(string filePath);
		vector<SearchResults> searchFor(vector<string>);
	};
};
#endif

