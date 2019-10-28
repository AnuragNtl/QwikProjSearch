#include <iostream>
#include <string>
#include "RegexTemplateSearcher.h"

using namespace std;

namespace ProjSearch {
  class RegexTemplateGeneration {
    private:
      map<string, RegexTemplate> regexTemplates;
    public:
      RegexTemplateGeneration(string source);
      string generateSpec(RegexTemplate);
      RegexTemplate getRegexTemplateByName(string);
      string getSpecByName(string);
  };
};

