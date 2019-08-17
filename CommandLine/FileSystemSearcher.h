#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

class FileSystemSearcher : public Searcher {
public:
	FileSystemSearcher(string filePath) : Searcher(filePath) {
		
	}
};

#endif

