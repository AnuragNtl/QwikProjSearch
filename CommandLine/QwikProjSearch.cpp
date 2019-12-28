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
}

vector<string> loadProjects(Io *io);
vector<string> loadProjectContainerDirectories(Io *io);

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
  IoL *ioL = new IoL;
  ProjectRepository projectRepository(ioL, chosenSearcher);
  vector<string> projectDirectories = loadProjects(ioL);
  vector<string> projectContainerDirectories = loadProjectContainerDirectories(ioL);
  for_each(projectDirectories.begin(), projectDirectories.end(),[&projectRepository] (string directory) {
      projectRepository.addProject(directory);
      });
  for_each(projectContainerDirectories.begin(), projectContainerDirectories.end(), [&projectRepository] (string directory) {
      projectRepository.addProjectContainerDirectory(directory);
      });
  projectDirectories.push_back("/sdcard/I/QwikProjSearch/CommandLine/");
  vector<string> toSearch = {"the", "earch"};
  vector<string> fileList = ioL->listDirectory(projectDirectories[0]);
  for(auto it = fileList.begin(); it != fileList.end(); it++) {
    cout << *it <<endl;
  }
  projectRepository.setFileFilters({".*\\.cpp$", ".*\\.h$"});
  cout << projectRepository.searchInSpecificProjects(projectDirectories, toSearch);
  /*  vector<string> projects = {"the quick brown fox\njumps\nover the lazy dog"};
  vector<string> regexes = {"t.", ".o."};
  vector<SearchResults> searchResults = (new RegexSearcher)->searchFor(projects[0].c_str(), regexes);
  cout << searchResults;*/
  //projectRepository.searchInSpecificProjects(projects, regexes); 
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

