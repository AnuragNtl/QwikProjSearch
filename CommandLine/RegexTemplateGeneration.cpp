#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace boost::property_tree;
using namespace ProjSearch;


RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  regexTemplates = loadRegexTemplates(source);
}

string RegexTemplateGeneration :: generateSpec(vector<RegexTemplate> regexTemplateList) {
  ptree specList;
  for_each(regexTemplateList.begin(), regexTemplateList.end(), [&specList] (RegexTemplate regexTemplate) {    
  ptree spec;
  ptree properties;
  spec.put(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME, regexTemplate.getName());  
 set<string> propertyNames = regexTemplate.getPlaceHolderNames();
for(auto it = propertyNames.begin(); it != propertyNames.end(); it++) {
  properties.put(*it, regexTemplate[*it]);
}
spec.add_child(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES, properties);
specList.push_back(spec);
      });
  ostringstream buf;
  write_json(buf, specList, false);
  return buf.str();
}

string RegexTemplateGeneration :: getSpecByName(string name) {
return regexTemplates[name].regexTemplate;
}

set<string> RegexTemplateGeneration :: getRegexTemplateNames() {
  set<string> regexTemplateNames;
  for_each(regexTemplates.begin(), regexTemplates.end(), [&regexTemplateNames](pair<string, RegexTemplate> regexTemplatePair) {
      regexTemplateNames.insert(regexTemplatePair.first);
      });
  return regexTemplateNames;
}

vector<RegexTemplate> RegexTemplateGeneration :: getRegexTemplates() {
  vector<RegexTemplate> regexTemplateList;
  for_each(regexTemplates.begin(), regexTemplates.end(), [&regexTemplateList](pair<string, RegexTemplate> regexTemplatePair) {
    regexTemplateList.push_back(regexTemplatePair.second);    
      });
  return regexTemplateList;
}

