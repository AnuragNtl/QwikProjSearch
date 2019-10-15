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
  } 
  source.close();
}
