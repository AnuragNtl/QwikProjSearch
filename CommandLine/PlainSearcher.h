#ifndef PLAIN_SEARCHER_H
#define PLAIN_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {

	class PlainSearcher : public Searcher {
	public:
		vector<SearchResults> searchFor(const char *, const vector<string>) const;
	};

};

#endif
