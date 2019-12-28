#include "Searcher.h"
#include <string>

using namespace std;

namespace ProjSearch {
  class OutputFormat {
    private:
      vector<SearchResults> &searchResults;
    public:
      virtual OutputFormat& format(ostream &, vector<SearchResults> &searchResults) = 0;
     OutputFormat& operator()(vector<SearchResults> &);
  };

  ostream& operator<<(ostream &out, OutputFormat &);
};

