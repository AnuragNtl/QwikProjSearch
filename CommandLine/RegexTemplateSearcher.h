#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

namespace ProjSearch {
	struct RegexTemplate {

	private:
		map<string, string> placeHolders;
	public:
		RegexTemplate(string);
		string& operator[](string templateName) {
				return placeHolders[templateName];
		}
		string regexTemplate;
		string applyAndGetRegex();
	};

	class RegexTemplateSearcher : public Searcher {
	private:
	public:
		vector<SearchResults> searchFor(char *, vector<string>);
		vector<SearchResults> searchFor(string filePath, vector<string>);
	};
};
#endif

