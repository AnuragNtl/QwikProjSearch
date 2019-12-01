#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include "RegexSearcher.h"
#include <map>
#include <set>

#define REGEX_TEMPLATE_WRAPPER_START "${"
#define REGEX_TEMPLATE_WRAPPER_END "}"
#define REGEX_TEMPLATE_WRAPPER_FIND_REGEX "\\$\\{.+?\\}"

#define REGEX_TEMPLATE_SPEC_TEMPLATE_NAME "templateName"
#define REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES "templateParams"


namespace ProjSearch {
	struct RegexTemplate {

	private:
		map<string, string> placeHolders;
	public:
		string regexTemplate;
    string regexTemplateName;
    RegexTemplate(){}
		RegexTemplate(string, string);
		string& operator[](string templateName) {
				return placeHolders[templateName];
		}
		string applyAndGetRegex();
    string getName();
    set<string> getPlaceHolderNames();
	};

  class RegexTemplateException : public std::exception {
    public:
      const char* what() const throw() ;
  };
  class RegexTemplateExtractor {
    public:
     virtual RegexTemplate extractFromString(string regexTemplateSpecifier);

  };

	class RegexTemplateSearcher : public RegexSearcher {
	private:
    map<string, RegexTemplate> regexTemplates;
  public:
    vector<SearchResults> searchFor(const char *, const vector<string>);
    set<string> getAllRegexTemplateNames();
    vector<RegexTemplate> getAllRegexTemplates();
	};
  vector<string> splitString(string, string);
  map<string, RegexTemplate> loadRegexTemplates(string);
};
#endif

