#include "PlainSearcher.h"
#include <algorithm>

using namespace ProjSearch;

using namespace std;

vector<SearchResults> PlainSearcher :: searchFor(const char *rawData, const vector<string> toSearch)  const {
	string data = rawData;
	vector<SearchResults> searchResults;
  for_each(toSearch.begin(), toSearch.end(), [&data, &toSearch, &searchResults] (string searchItem) {
	int indx = 0;
	do {
	indx = data.find(searchItem, indx);
	if(indx != string::npos) {
		int row, col;
    string substr;
		SearchResults :: setRowAndCol(data, indx, row, col);
		searchResults.push_back(SearchResults(row, col, indx, 0, searchItem));
    indx++;
	}
	} while(indx != string::npos);
  });

	return searchResults;
}

