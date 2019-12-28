#ifndef CSV_OUTPUT_FORMAT_H
#define CSV_OUTPUT_FORMAT_H

#include "OutputFormat.h"

namespace ProjSearch {
  class CsvOutputFormat : public OutputFormat {
    public:
      ostream& format(ostream &);
  };
};

#endif

