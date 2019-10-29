#ifndef REGEX_SEARCHER_H
#define REGEX_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	class RegexSearcher : public Searcher {
	public:
		virtual vector<SearchResults> searchFor(const char *data, const vector<string> regexes);
	};
};

#endif
