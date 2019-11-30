#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "RegexTemplateSearcher.h"

using namespace std;

namespace ProjSearch {
  class RegexTemplateGeneration {
    private:
      map<string, RegexTemplate> regexTemplates;
    public:
      RegexTemplateGeneration(string source);
      string generateSpec(vector<RegexTemplate>);
      RegexTemplate getRegexTemplateByName(string);
      string getSpecByName(string);
      set<string>  getRegexTemplateNames();
      vector<RegexTemplate> getRegexTemplates();
  };
};

