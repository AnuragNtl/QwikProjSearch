#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace boost::property_tree;



RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  vector<string> specs = split(source, "\n");
    for(vector<string> :: iterator it = specs.begin(); it != specs.end(); it++)
    string regexTemplateName, regexTemplateSpec;
    vector<string> spec = it->split(" ");
    regexTemplateName = spec[0];
    regexTemplateSpec = spec[1];
    regexTemplates[regexTemplateName] = regexTemplateSpec;
  }
  source.close();
}

string RegexTemplateGeneration :: generateSpec(RegexTemplate regexTemplate) {
  ptree spec;
  ptree properties;
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

