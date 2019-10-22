#include <iostream>
#include <string>
#include "RegexTemplateSearcher.h"

using namespace std;

namespace ProjSearch {
  class RegexTemplateGeneration {
    private:
      map<string, string> regexTemplates;
    public:
      RegexTemplateGeneration(string source);
      string generateSpec(RegexTemplate regexTemplate);
  };
  vector<string> split(string, string);
};

