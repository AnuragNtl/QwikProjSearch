#include "OutputFormat.h"

using namespace ProjSearch;

namespace ProjSearch {
  ostream& operator<<(ostream &out, OutputFormat &outputFormat) {
    return outputFormat.format(out);    
  }
};

OutputFormat& OutputFormat :: operator()(vector<SearchResults> &searchResults) {
  this->searchResults = searchResults;
  return *this;
}

