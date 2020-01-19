#include "JsonOutputFormat.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace ProjSearch;

using namespace boost :: property_tree;

ostream& JsonOutputFormat :: format(ostream &out) {
  ptree specList;
  for(auto it = searchResults.begin(); it != searchResults.end(); it++) {
    ptree spec;
    spec.put("row", it->row);
    spec.put("col", it->col);
    spec.put("filePath", it->filePath);
    spec.put("offset", it->offset);
    spec.put("fileType", it->fileType);
    spec.put("match", it->match);
    specList.push_back(std::make_pair("", spec));
  }
  ptree data;
  data.add_child("searchResults", specList);
  write_json(out, data);
  return out;
}

