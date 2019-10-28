#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace boost::property_tree;



RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  regexTemplates = loadRegexTemplates(source);
  }
}

string RegexTemplateGeneration :: generateSpec(string regexTemplateName) {
  ptree spec;
  ptree properties;
  RegexTemplate regexTemplate = regexTemplates[regexTemplateName]; 
  spec.put(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME, regexTemplate.getName());  
 set<string> propertyNames = regexTemplate.getPlaceHolderNames();
for(auto it = propertyNames.begin(); it != propertyNames.end(); it++) {
  properties.put(*it, regexTemplate[*it]);
}
spec.put(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES, properties);
  ostringstream buf;
  write_json(buf, spec, false);
  return spec.str();
}

string RegexTemplateGeneration :: getSpecByName(string name) {
return regexTemplates[name];
}

