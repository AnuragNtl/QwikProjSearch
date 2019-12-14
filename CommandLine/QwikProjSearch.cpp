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

using namespace std;

using namespace ProjSearch;

void showUsage();

map<char, Searcher*> chosenSearcherMap;
void initChosenSearchers() {
  chosenSearcherMap['p'] = new PlainSearcher;
  chosenSearcherMap['r'] = new RegexSearcher;
  chosenSearcherMap['R'] = new RegexTemplateSearcher;
}

int main(int argc, char *argv[]) {
  if(argc <= 1) {
    showUsage();
    return 0;
  }
  initChosenSearchers();
  char optString[] = "prRf:stun:";
  int opt = getopt(argc, argv, optString);
  
  string projectFilter = ".*", fileFilter = ".*";
  Searcher *chosenSearcher = NULL;
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
        break;
      case 'n':
        projectFilter = optarg;
        break;
      default:
        cout << "Invalid option " << (char)opt <<endl;
        break;
    }
      opt = getopt(argc, argv, optString); 
  }
  if(chosenSearcher == NULL) {
    chosenSearcher = new RegexTemplateSearcher;
  }
  ProjectRepository projectRepository(new IoL, chosenSearcher);
  vector<string> projects = {"."};
  vector<string> regexes = {".*"};
  ProjectRepository.searchInSpecificProjects(projects, regexes); 
	/*IoL ioL;
	Io *io = &ioL;
	cout << io->fileExists("/tmp") << "\n";
	vector<string> dirList = io->listDirectory("/tmp");
	for(auto it = dirList.begin(); it != dirList.end(); it++) {
		cout << *it <<endl;
	}*/
  
	return 0;
}


void showUsage() {

string usage = "\tUsage:\nQwikProjSearch [...OPTIONS] [ProjectPaths...]\n\nReads Search specifiers from stdin and outputs the results\n-p Use Plain searcher\n-r Use regex searcher\n-R Default Use RegexTemplateSearcher\n-f FileFilter : FileFilter to use\n-s Use raw output format\n-t Use CSV output format\n-u Use \n-n Regex : Regex to use to filter projects\n\n";
cout << usage;

}

