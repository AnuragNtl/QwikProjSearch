#ifndef TABLE_OUTPUT_FORMAT_H
#define TABLE_OUTPUT_FORMAT_H

#include "OutputFormat.h"

namespace ProjSearch {
  class TableOutputFormat : public OutputFormat {
    public:
      ostream& format(ostream &);
  };
};

#endif

