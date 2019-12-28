#ifndef OUTPUT_FORMAT_H
#define OUTPUT_FORMAT_H

#include "Searcher.h"
#include <string>

using namespace std;

namespace ProjSearch {
  class OutputFormat {
    protected:
      vector<SearchResults> searchResults;
    public:
    virtual ostream& format(ostream &) = 0;
     OutputFormat& operator()(vector<SearchResults> &);
  };

  ostream& operator<<(ostream &out, OutputFormat &);
};

#endif

