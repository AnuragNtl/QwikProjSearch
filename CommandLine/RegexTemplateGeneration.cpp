#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace boost::property_tree;
using namespace ProjSearch;


RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  regexTemplates = loadRegexTemplates(source);
}

string RegexTemplateGeneration :: generateSpec(RegexTemplate regexTemplate) {
  ptree spec;
  ptree properties;
  spec.put(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME, regexTemplate.getName());  
 set<string> propertyNames = regexTemplate.getPlaceHolderNames();
for(auto it = propertyNames.begin(); it != propertyNames.end(); it++) {
  properties.put(*it, regexTemplate[*it]);
}
spec.add_child(REGEX_TEMPLATE_SPEC_TEMPLATE_PROPERTIES, properties);
  ostringstream buf;
  write_json(buf, spec, false);
  return buf.str();
}

string RegexTemplateGeneration :: getSpecByName(string name) {
return regexTemplates[name].regexTemplateName;
}

