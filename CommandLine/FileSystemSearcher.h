#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	class FileSystemSearcher : public Searcher {
	public:
		FileSystemSearcher(string filePath);
		FileSystemSearcher(char *data);
		vector<SearchResults> searchFor(vector<string>);
	};
};
#endif

