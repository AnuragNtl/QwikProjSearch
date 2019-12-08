#include "RegexSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;

vector<SearchResults> RegexSearcher :: searchFor(const char *rawData, const vector<string> regexes) const {
	vector<SearchResults> searchResults;
  string filePath = this->filePath;
  for_each(regexes.begin(), regexes.end(), [filePath, rawData, &searchResults] (string regex) {
		boost::regex expr{regex};
    string data = rawData;
    boost::sregex_iterator itBegin(data.begin(), data.end(), expr), itEnd;
    for(boost::sregex_iterator it = itBegin; it != itEnd; it++) {
    SearchResults searchResult(filePath, 0, 0, it->position(), 0);
    searchResult.match = it->str();
    searchResults.push_back(searchResult);
    }
	});
  return searchResults;
}

