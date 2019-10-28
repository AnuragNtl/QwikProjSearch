#include "RegexTemplateSearcher.h"
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <cstring>

using namespace ProjSearch;
using namespace boost::property_tree;
using namespace std;

RegexTemplate :: RegexTemplate(string regexTemplate, string regexTemplateName) : regexTemplate(regexTemplate), regexTemplateName(regexTemplateName) {
  vector<string> regex = {REGEX_TEMPLATE_WRAPPER_START + regexTemplate + REGEX_TEMPLATE_WRAPPER_END};
  RegexSearcher regexSearcher;
  vector<SearchResults> searchResults = regexSearcher.searchFor(regexTemplate.c_str(), regex);
  for(int i = 0; i < searchResults.size(); i++) {
   string match = searchResults[i].match;
   placeHolders[match] = string(""); 
  }
}

string RegexTemplate :: applyAndGetRegex() {
	string tempRegexTemplate = regexTemplate;
	for(map<string, string> :: iterator it = placeHolders.begin(); it != placeHolders.end(); it++) {
    string replaceValue = it->first;
    string toReplaceWith = it->second;
    toReplaceWith = REGEX_TEMPLATE_WRAPPER_START + toReplaceWith + REGEX_TEMPLATE_WRAPPER_END;
    tempRegexTemplate = replace(tempRegexTemplate, replaceValue, toReplaceWith);
	}
	return tempRegexTemplate;
}

string RegexTemplate :: getName() {
  return regexTemplateName;
}

set<string> RegexTemplate :: getPlaceHolderNames() {
  set<string> placeHolderNames;
  for(auto it = placeHolders.begin(); it != placeHolders.end(); it++) {
    placeHolderNames.insert(it->first);
  }
  return placeHolderNames;
}

const char* RegexTemplateException :: what() const throw() {
  return "Wrong Regex Template";
}

/*
 * 
 */
vector<SearchResults> RegexTemplateSearcher :: searchFor(const char *data, const vector<string> regexTemplateSpecifiers) {
  vector<string> regexList;
  regexList.resize(regexTemplateSpecifiers.size());
  transform(regexTemplateSpecifiers.begin(), regexTemplateSpecifiers.end(), regexList.begin(), [&data, this] (string regexTemplateSpecifier) {
     ptree regexTemplateSpecification;
     istringstream input(regexTemplateSpecifier);
      try {
     read_json(input, regexTemplateSpecification);
     string templateName = regexTemplateSpecification.get_child(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME).get_value<string>();
     ptree templateProperties = regexTemplateSpecification.get_child(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES);
   RegexTemplate regexTemplate = regexTemplates[templateName];  
     for(ptree :: iterator it = templateProperties.begin(); it != templateProperties.end(); it++) {
      regexTemplate[it->first] = templateProperties.get_child(it->first).get_value<string>();
     }
     return regexTemplate.applyAndGetRegex();
     }
   catch(boost::exception &e) {
    throw RegexTemplateException(); 
   }
      });
  return RegexSearcher :: searchFor(data, regexList);
}


namespace ProjSearch {
  vector<string> splitString(string toSplit, string delim) {
  istringstream input(toSplit);
  vector<string> output;
  while(!input.eof()) {
    string token;
    getline(input, token, delim.c_str()[0]);
    output.push_back(token);
  }
  return output;
}
}

RegexTemplate RegexTemplateExtractor :: extractFromString(string regexTemplateSpecifier) {
  vector<string> spec = splitString(regexTemplateSpecifier, " ");
  string regexTemplateName = spec[0];
  string regexTemplateSpec = spec[1];
  RegexTemplate regexTemplate(regexTemplateSpec, regexTemplateName);
}


map<string, RegexTemplate> ProjSearch :: loadRegexTemplates(string source) {
  map<string, RegexTemplate> regexTemplateMap;
  vector<string> specs = ProjSearch::splitString(source, "\n");
    for(vector<string> :: iterator it = specs.begin(); it != specs.end(); it++) {
    string regexTemplateName, regexTemplateSpec;
    vector<string> spec = ProjSearch::splitString(*it, string(" "));
    regexTemplateName = spec[0];
    regexTemplateSpec = spec[1];
    RegexTemplate regexTemplate(regexTemplateSpec, regexTemplateName);
    regexTemplateMap[regexTemplateName] = regexTemplate;
  }
    return regexTemplateMap;
}


