#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "Searcher.h"

#define REGEX_TEMPLATE_WRAPPER_START "${"
#define REGEX_TEMPLATE_WRAPPER_END "}"

namespace ProjSearch {
	struct RegexTemplate {

	private:
		map<string, string> placeHolders;
	public:
		string regexTemplate;
		RegexTemplate(string);
		string& operator[](string templateName) {
				return placeHolders[templateName];
		}
		string applyAndGetRegex();
	};

	class RegexTemplateSearcher : public RegexSearcher {
	private:
		map<string, RegexTemplate> regexTemplates;
	public:
		RegexTemplateSearcher(map<string, RegexTemplate>);
		vector<SearchResults> searchFor(char *, vector<string>);
	};
};
#endif

