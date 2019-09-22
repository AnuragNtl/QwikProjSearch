#include "RegexTemplateSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;

RegexTemplate :: RegexTemplate(string regexTemplate) : regexTemplate(regexTemplate) {}

string RegexTemplate :: applyAndGetRegex() {
	for(map<string, string> :: iterator it = placeHolders.begin(); it != placeHolders.end(); it++) {
    string replaceValue = *it;
    replaceValue = 
	} 
}

vector<SearchResults> RegexTemplateSearcher :: searchFor(vector<string> regexes) {
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

