#include "RegexSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;

vector<SearchResults> RegexSearcher :: searchFor(const char *rawData, const vector<string> regexes) const {
	vector<SearchResults> searchResults;
  for_each(regexes.begin(), regexes.end(), [rawData, &searchResults] (string regex) {
		boost::regex expr{regex};
    string data = rawData;
    boost::sregex_iterator itBegin(data.begin(), data.end(), expr), itEnd;
    for(boost::sregex_iterator it = itBegin; it != itEnd; it++) {
    int row, col;
    SearchResults :: setRowAndCol(data, it->position(), row, col);
    SearchResults searchResult(row, col, it->position(), 0, it->str());
    searchResults.push_back(searchResult);
    }
	});
  return searchResults;
}

