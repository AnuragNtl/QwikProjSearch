#include <iostream>
#include <string>
#include "IO.h"
#include "IO_L.h"
#include <unistd.h>
#include <map>
#include "Searcher.h"
#include "PlainSearcher.h"
#include "RegexSearcher.h"
#include "RegexTemplateSearcher.h" 
#include "ProjRepository.h"
#include "OutputFormat.h"
#include "JsonOutputFormat.h"
#include "TableOutputFormat.h"
#include "CsvOutputFormat.h"

using namespace std;

using namespace ProjSearch;

void showUsage();

ostream& operator<<(ostream &out, vector<SearchResults> searchResults) {
  out <<"[ ";
  for(vector<SearchResults> :: iterator it = searchResults.begin(); it != searchResults.end(); it++) {
    out << (string)*it;
   if(it + 1 != searchResults.end()) {
     out << ",";
   }
  }
  out <<"]";
  out <<"\n";
  return out;
}

vector<string> loadProjects(Io *io);
vector<string> loadProjectContainerDirectories(Io *io);

map<char, Searcher*> chosenSearcherMap;
map<char, OutputFormat*> chosenOutputFormatMap;

void initChosenSearchers(Io *io) {
  chosenSearcherMap['p'] = new PlainSearcher;
  chosenSearcherMap['r'] = new RegexSearcher;
  if(io->fileExists("RegexTemplates.conf")) {
    chosenSearcherMap['R'] = new RegexTemplateSearcher(loadRegexTemplates(getContents("RegexTemplates.conf")));
  } else {
    chosenSearcherMap['R'] = new RegexTemplateSearcher;
  }
}

void initChosenOutputFormat() {
  chosenOutputFormatMap['s'] = new TableOutputFormat;
  chosenOutputFormatMap['t'] = new CsvOutputFormat;
  chosenOutputFormatMap['u'] = new JsonOutputFormat;
}

int main(int argc, char *argv[]) {
  if(argc <= 1) {
    showUsage();
    return 0;
  }
  Io *ioL = new IoL;
  initChosenSearchers(ioL);
  initChosenOutputFormat();
  char optString[] = "prRf:stun:";
  int opt = getopt(argc, argv, optString);
  
  string projectFilter = ".*", fileFilter = ".*";
  Searcher *chosenSearcher = NULL;
  OutputFormat *chosenOutputFormat = NULL;
  while(opt != -1) {
    switch(opt) {
      case 'p':
      case 'r':
      case 'R':
        chosenSearcher = chosenSearcherMap[opt];
        break;
      case 'f':
        fileFilter = optarg;
        break;
      case 's':
      case 't':
      case 'u':
        chosenOutputFormat = chosenOutputFormatMap[opt];
        break;
      case 'n':
        projectFilter = optarg;
        break;
      default:
        cout << "Invalid option " << (char)opt <<endl;
        showUsage();
        return 1;
    }
      opt = getopt(argc, argv, optString); 
  }
  if(chosenSearcher == NULL) {
    chosenSearcher = new RegexTemplateSearcher;
  }
  if(chosenOutputFormat == NULL) {
    chosenOutputFormat = new TableOutputFormat;
  }
  ProjectRepository projectRepository(ioL, chosenSearcher);
  vector<string> projectDirectories = loadProjects(ioL);
  vector<string> projectContainerDirectories = loadProjectContainerDirectories(ioL);
  for_each(projectDirectories.begin(), projectDirectories.end(),[&projectRepository] (string directory) {
      projectRepository.addProject(directory);
      });
  for_each(projectContainerDirectories.begin(), projectContainerDirectories.end(), [&projectRepository] (string directory) {
      projectRepository.addProjectContainerDirectory(directory);
      });
  projectRepository.setFileFilters(splitString(fileFilter, ","));
  vector<string> toSearch;
  
  while(!cin.eof()) {
    string spec;
    getline(cin, spec);
    if(!cin.eof())
      toSearch.push_back(spec);
  }
  vector<SearchResults> searchResults = projectRepository.searchInSpecificProjects(projectDirectories, toSearch);
  
  OutputFormat &outputFormat = *chosenOutputFormat;
  cout << outputFormat(searchResults);
    
	return 0;
}


void showUsage() {

string usage = "\tUsage:\nQwikProjSearch [...OPTIONS] [ProjectPaths...]\n\nReads Search specifiers from stdin and outputs the results\n-p Use Plain searcher\n-r Use regex searcher\n-R Default Use RegexTemplateSearcher\n-f FileFilter : FileFilter to use\n-s Use Table output format\n-t Use CSV output format\n-u Use JSON output format \n-n Regex : Regex to use to filter projects\n\n";
cout << usage;

}

vector<string> loadProjects(Io *io) {
  if(!io->fileExists("Projects.conf")) {
    return vector<string>(); 
  }
  return splitString(getContents("Projects.conf"), "\n");
}
vector<string> loadProjectContainerDirectories(Io *io) {
  if(!io->fileExists("ProjectContainers.conf")) {
    return vector<string>();
  }
  return splitString(getContents("ProjectContainers.conf"), "\n");
}

