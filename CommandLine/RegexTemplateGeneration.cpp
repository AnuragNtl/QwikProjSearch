#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace boost::property_tree;



RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  vector<string> specs = split(source, "\n");
    for(vector<string> :: iterator it = specs.begin(); it != specs.end(); it++)
    string regexTemplateName, *it;
    regexTemplateName.insert(0, spec, 0, spec.find(" "));
    regexTemplateSpec.insert(0, spec, spec.find(" ") + 1, spec.size());
    regexTemplates[regexTemplateName] = regexTemplateSpec;
  } 
  source.close();
}
string RegexTemplateGeneration :: generateSpec(RegexTemplate regexTemplate) {
  ptree spec;
  ptree properties;
  spec.put(REGEX_TEMPLATE_SPEC_TEMPLATE_NAME, regexTemplate. regexTemplate.getName());
  
  ostringstream buf;
  spec.put(buf, spec, false);
  return spec.str();
}

vector<string, string> split(string toSplit, string delim) {
  istringstream input(toSplit);
  vector<string> output;
  while(!input.eof()) {
    string token;
    input.getline(token, delim);
    output.push_back(line);
  }
  input.close();
  return output;
}

