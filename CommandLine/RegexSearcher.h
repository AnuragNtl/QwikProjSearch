#ifndef REGEX_SEARCHER_H
#define REGEX_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	class RegexSearcher : public Searcher {
	public:
		virtual vector<SearchResults> searchFor(char *data, vector<string> regexes);
	};
};

#endif
