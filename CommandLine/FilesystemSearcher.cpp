#include "FileSystemSearcher.h"
#include <boost/regex.hpp>

using namespace ProjSearch;


FileSystemSearcher :: FileSystemSearcher(string filePath) : Searcher(filePath) {}

FileSystemSearcher :: FileSystemSearcher(char *data) : Searcher(data) {}

vector<SearchResults> searchFor(vector<string> regexes) {
	for_each(regexes.begin(), regexes.end(), [] (string regex) {
		boost::regex expr{regex};
		boost::smatch matches;
		if(boost::regex_search(data, matches, expr)) {
			
		}
	});
}
