#include "RegexTemplateSearcher.h"
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace ProjSearch;
using namespace boost::property_tree;

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

const char* RegexTemplateException :: what() const {
  return "Wrong Regex Template";
}

/*
 * 
 */
vector<string> RegexTemplateSearcher :: searchFor(char *data, vector<string> regexTemplateSpecifiers) {
  vector<RegexTemplate> regexTemplateList;
  regexTemplateList.resize(regexTemplateSpecifiers.size());
  transform(regexTemplateSpecifiers.begin(), regexTemplateSpecifiers.end(), regexTemplateList.begin(), [] (string regexTemplateSpecifier) {
     ptree regexTemplateSpecification;
     istringstream input(regexTemplateSpecifier);
      try {
     read_json(input, regexTemplateSpecification);
     string templateName = regexTemplateSpecification.get_child<string>(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME);
     string templateProperties = regexTemplateSpecification.get_child<string>(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES);
     RegexTemplate regexTemplate(templateName);
     for(ptree :: iterator it = templateProperties.begin(); it != templateProperties.end(); it++) {
      regexTemplate[it->first] = templateProperties.get_child<string>(it->first);
     }
     return regexTemplate;
     }
   catch(boost::exception &e) {
    throw RegexTemplateException(); 
   }
      });
}

