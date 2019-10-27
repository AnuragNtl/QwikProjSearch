#include "RegexTemplateSearcher.h"
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/regex.hpp>

using namespace ProjSearch;
using namespace boost::property_tree;

RegexTemplate :: RegexTemplate(string regexTemplate, string regexTemplateName) : regexTemplate(regexTemplate), regexTemplateName(regexTemplateName) {
  boost::regex expr{REGEX_TEMPLATE_WRAPPER_START + string(".*?") + REGEX_TEMPLATE_WRAPPER_END};
  boost::smatch what;
  boost::regex_search(regexTemplate, what, expr);

}

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

string RegexTemplate :: getName() {
  return regexTemplateName;
}

set<string> RegexTemplate :: getPlaceHolderNames() {
  set<string> placeHolderNames;
  for(auto it = placeHolders.begin(); it != placeHolders.end(); it++) {
    placeHolderNames.push_back(it->first);
  }
  return placeHolderNames;
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


vector<string, string> split(string toSplit, string delim) {
  istringstream input(toSplit);
  vector<string> output;
  while(!input.eof()) {
    string token;
    getline(token, delim);
    output.push_back(token);
  }
  input.close();
  return output;
}

RegexTemplate RegexTemplateExtractor :: extractFromString(string regexTemplateSpecifier) {
  vector<string> spec = split(regexTemplateSpecifier, " ");
  string regexTemplateName = spec[0];
  string regexTemplateSpec = spec[1];
  RegexTemplate regexTemplate(regexTemplateSpec, regexTemplateName);
}

