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

string getContents(string fileName) {
  ifstream in(fileName.c_str());
  string buf;
  string s = "";
  getline(in, buf);
  while(!in.eof()) {
    s = s +  buf;
    getline(in, buf);
    if(!in.eof()) 
      s = s + "\n";
  }
  in.close();
  return s;
}

int main() {
  RegexTemplateGeneration regexTemplateGeneration(getContents("RegexTemplates.conf"));
  set<string> regexTemplateNames = regexTemplateGeneration.getRegexTemplateNames();
  cout <<"Choose regex template\n";
 string templateName;
 int exitChoice = regexTemplateNames.size() + 1;
 int choice = exitChoice;
 do {
   for(int i = 0; i < regexTemplateNames.begin();
 } while(choice != exitChoice);
  string spec = regexTemplateGeneration.getSpecByName(templateName);
RegexTemplate regexTemplate(spec, templateName);
set<string> propertyNames = regexTemplate.getPlaceHolderNames();
  cout <<"Enter template properties : \n";
  for(auto it = propertyNames.begin(); it != propertyNames.end(); it++) {
    cout << *it <<" : ";
    cin >> regexTemplate[*it];
}
  cout << regexTemplateGeneration.generateSpec(regexTemplate) <<endl;
  return 0;
}


