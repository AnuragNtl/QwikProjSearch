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
#include <fstream>

using namespace ProjSearch; 

int main() {
  RegexTemplateGeneration regexTemplateGeneration(getContents("RegexTemplates.conf"));
  set<string> regexTemplateNames = regexTemplateGeneration.getRegexTemplateNames();
  vector<RegexTemplate> regexTemplateGenerationList;
  cerr <<"Choose regex template\n";
 string templateName;
 int exitChoice = regexTemplateNames.size() + 1;
 int choice = exitChoice;
  do {
   int i = 0;
   vector<string> regexTemplateNamesList(regexTemplateNames.size());
   for(auto it = regexTemplateNames.begin(); it != regexTemplateNames.end()  ; i++, it++) {
     cerr << (i+1) << "." << *it <<endl;
     regexTemplateNamesList[i] = *it;
   }
   cerr << (i+1) << ".Exit\n";
  cin >> choice;
  if(choice > 0 && choice <= regexTemplateNamesList.size()) {
  templateName = regexTemplateNamesList[choice - 1];
  
  string spec = regexTemplateGeneration.getSpecByName(templateName);
RegexTemplate regexTemplate(spec, templateName);
set<string> propertyNames = regexTemplate.getPlaceHolderNames();
  cerr <<"Enter template properties : \n";
  for(auto it = propertyNames.begin(); it != propertyNames.end(); it++) {
    cerr << *it <<" : ";
    cin >> regexTemplate[*it];
}
regexTemplateGenerationList.push_back(regexTemplate);
  }
 } while(choice != exitChoice);
  cout << regexTemplateGeneration.generateSpec(regexTemplateGenerationList) <<endl;
  return 0;
}


