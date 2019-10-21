#include "RegexTemplateGeneration.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <algorithm>

using namespace ProjSearch;
using namespace boost::property_tree;



RegexTemplateGeneration :: RegexTemplateGeneration(string source) {
  istringstream input;
  while(!input.eof()) {
    string spec;
    input.getline(spec, '\n');
    string regexTemplateName, regexTemplateSpec;
    regexTemplateName.insert(0, spec, 0, spec.find(" "));
    regexTemplateSpec.insert(0, spec, spec.find(" ") + 1, spec.size());
    regexTemplates[regexTemplateName] = regexTemplateSpec;
  } 
  source.close();
}
string RegexTemplateGeneration :: generateSpec() {

}

vector<string, string> split(string toSplit, string delim) {
  istringstream input(toSplit);
  vector<string> output;
  while(!input.eof()) {
    
  }
}

