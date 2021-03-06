#ifndef JSON_OUTPUT_FORMAT_H
#define JSON_OUTPUT_FORMAT_H

#include "OutputFormat.h"

namespace ProjSearch {
  class JsonOutputFormat : public OutputFormat {
    public:
      ostream& format(ostream &);
  };
};

#endif

