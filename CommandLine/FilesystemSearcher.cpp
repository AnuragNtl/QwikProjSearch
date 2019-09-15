#include "RegesTemplateSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;


RegesTemplateSearcher :: RegesTemplateSearcher(string fPath) : filePath(fPath) {}

vector<SearchResults> RegesTemplateSearcher :: searchFor(char *data, vector<string> regexes) {
	vector<SearchResults> searchResults;
  for_each(regexes.begin(), regexes.end(), [] (string regex) {
		boost::regex expr{regex};
		boost::smatch matches;
		if(boost::regex_search(data, matches, expr)) {
    for(auto it = matches.begin(); it != matches.end(); it++) {
      searchResults.insert(SearchResults(filePath, 0 , 0, *it-pData, 0));
    }
		}
	});
  return searchResults;
}

vector<SearchResults> RegesTemplateSearcher :: searchFor(string filePath, vector<string> regexes) {
	
}
