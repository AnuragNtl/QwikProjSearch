#include "PlainSearcher.h"

using namespace ProjSearch;

using namespace std;

vector<SearchResults> PlainSearcher :: searchFor(char *rawData, vector<string> toSearch) {
	string data = rawData;
	vector<SearchResults> searchResults;
	int indx = 0;
	do {
	indx = data.find(toSearch, indx);
	if(indx != string::npos) {
		int row, col;
		SearchResults :: setRowAndCol(toSearch(data, indx, row, col));
		searchresults.push_back(SearchResults(row, col, indx));
	}
	} while(indx != string::npos);
	return searchResults;
}
