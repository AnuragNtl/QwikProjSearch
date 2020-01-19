#ifndef CSV_OUTPUT_FORMAT_H
#define CSV_OUTPUT_FORMAT_H

#include "OutputFormat.h"


namespace ProjSearch {
  class CsvOutputFormat : public OutputFormat {
    private:
      string escape(string);
      string join(vector<string> data, string delim);
    public:
      ostream& format(ostream &);
  };
};

#endif

