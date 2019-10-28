#ifndef PLAIN_SEARCHER_H
#define PLAIN_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {

	class PlainSearcher : public Searcher {
	public:
		vector<SearchResults> searchfor(const char *, const vector<string>);
	};

};

#endif
