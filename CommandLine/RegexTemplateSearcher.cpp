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
  vector<string> regex = {REGEX_TEMPLATE_WRAPPER_FIND_REGEX};
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

RegexTemplateException :: RegexTemplateException(string message) : message(message) {}

const char* RegexTemplateException :: what() const throw() {
  return ("Regex Template Error : " + message).c_str();
}

RegexTemplateSearcher :: RegexTemplateSearcher(map<string, RegexTemplate> regexTemplates) : regexTemplates(regexTemplates) {}

vector<SearchResults> RegexTemplateSearcher :: searchFor(const char *data, const vector<string> regexTemplateSpecifiers) const {
  vector<string> regexList;
  regexList.resize(regexTemplateSpecifiers.size());
  transform(regexTemplateSpecifiers.begin(), regexTemplateSpecifiers.end(), regexList.begin(), [&data, this] (string regexTemplateSpecifier) {
     ptree regexTemplateSpecification;
     istringstream input(regexTemplateSpecifier);
      try {
     read_json(input, regexTemplateSpecification);
     string templateName = regexTemplateSpecification.get_child(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME).get_value<string>();
     ptree templateProperties = regexTemplateSpecification.get_child(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES);
     if(regexTemplates.find(templateName) == regexTemplates.end()) {
      throw RegexTemplateException("No regex template found");
     }
   RegexTemplate regexTemplate = (regexTemplates.find(templateName))->second;
     for(ptree :: iterator it = templateProperties.begin(); it != templateProperties.end(); it++) {
      regexTemplate[it->first] = templateProperties.get_child(it->first).get_value<string>();
     }
     return regexTemplate.applyAndGetRegex();
     }
   catch(boost::exception &e) {
    throw RegexTemplateException("Wrong Regex Template"); 
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
  string regexTemplateSpec = "";
  int i;
  for(i = 1; i < spec.size() - 1; i++) {
    regexTemplateSpec = regexTemplateSpec + spec[i] + " ";
  }
  regexTemplateSpec = regexTemplateSpec + spec[i];
  RegexTemplate regexTemplate(regexTemplateSpec, regexTemplateName);
  return regexTemplate;
}


map<string, RegexTemplate> ProjSearch :: loadRegexTemplates(string source) {
  map<string, RegexTemplate> regexTemplateMap;
  vector<string> specs = ProjSearch::splitString(source, "\n");
    for(vector<string> :: iterator it = specs.begin(); it != specs.end(); it++) {
    RegexTemplate regexTemplate = RegexTemplateExtractor::extractFromString(*it);
    regexTemplateMap[regexTemplate.regexTemplateName] = regexTemplate;
  }
    return regexTemplateMap;
}

set<string> RegexTemplateSearcher :: getAllRegexTemplateNames() {
  set<string> regexTemplateNames;
  for(auto it = regexTemplates.begin(); it != regexTemplates.end(); it++) {
    regexTemplateNames.insert(it->first);
  }
  return regexTemplateNames;
}

vector<RegexTemplate> RegexTemplateSearcher :: getAllRegexTemplates() {
  vector<RegexTemplate> regexTemplateList;
  for(auto it = regexTemplates.begin(); it != regexTemplates.end(); it++) {
    regexTemplateList.push_back(it->second);
  }
  return regexTemplateList;
}

