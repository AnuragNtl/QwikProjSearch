/************************************************************************************//**
 *  @file       RegexTemplateMenuGenerator.cpp
 *
 *  @brief      Brief descriptinon of RegexTemplateMenuGenerator.cpp 
 *
 *  @date       2019-10-26 17:20
 *
 ***************************************************************************************/

#include "RegexTemplateGeneration.h"
#include <iostream>

using namespace ProjSearch; 


int main() {
  string templateName;
  cout << "Enter template Name:\n";
  cin >> templateName;
  RegexTemplateGeneration regexTemplateGeneration("RegexTemplates.conf");
RegexTemplate regexTemplate;
regexTemplateGeneration.getSpecByName(templateName);
set<string> propertyNames = regexTemplate.getPropertyNames();
  cout <<"Enter template properties : \n";
  return 0;
}


