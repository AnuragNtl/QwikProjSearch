#include "RegexTemplateSearcher.h"
#include <algorithm>


using namespace ProjSearch;

RegexTemplate :: RegexTemplate(string regexTemplate) : regexTemplate(regexTemplate) {}

string RegexTemplate :: applyAndGetRegex() {
	string tempRegexTemplate = regexTemplate;
	for(map<string, string> :: iterator it = placeHolders.begin(); it != placeHolders.end(); it++) {
    string replaceValue = it->first;
    string toReplaceWith = it->second;
    toReplaceWith = REGEX_TEMPLATE_WRAPPER_START + toReplaceWith + REGEX_TEMPLATE_WRAPPER_END;
    replace(tempRegexTemplate.start(), tempRegexTemplate.end(), replaceValue, toReplaceWith);
	}
	return tempRegexTemplate;
}

/*
 * 
 */
vector<string> RegexTemplateSearcher :: searchFor(char *data, vector<string> regexTemplateSpecifiers) {
  for_each(regexTemplateSpecifiers.begin(), regexTemplateSpecifiers.end(), [] (string regexTemplateSpecifier) {
      });
}

