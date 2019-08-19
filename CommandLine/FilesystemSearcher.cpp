#include "FileSystemSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;


FileSystemSearcher :: FileSystemSearcher(string fPath) : Searcher(fPath), filePath(fPath) {}

vector<SearchResults> searchFor(vector<string> regexes) {
	vector<SearchResults> searchResults;
  for_each(regexes.begin(), regexes.end(), [] (string regex) {
		boost::regex expr{regex};
		boost::smatch matches;
		if(boost::regex_search(data, matches, expr)) {
    for(auto it = matches.begin(); it != matches.end(); it++) {
      searchResults.insert(SearchResults())
    }
		}
	});
}
