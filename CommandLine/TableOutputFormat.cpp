#include "TableOutputFormat.h"

using namespace ProjSearch;

ostream& TableOutputFormat :: format(ostream &out) {
  out << "row\tcol\toffset\tfilePath\tfileType\tmatch\n"; 
  for(vector<SearchResults> :: iterator it = searchResults.begin(); it != searchResults.end(); it++) {
    out << it->row << "\t";
    out << it->col << "\t";
    out << it->offset << "\t";
    out << it->filePath << "\t";
    out << it->fileType << "\t";
    out << replace(it->match, "\n", "\\n") << "\t";
    out <<"\n";
  }
  return out;
}
