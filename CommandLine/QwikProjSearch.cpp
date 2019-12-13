#include <iostream>
#include <string>
#include "IO.h"
#include "IO_L.h"

using namespace std;

using namespace ProjSearch;

void showUsage();

int main(int argc, char *argv[]) {
  if(argc == 0) {
    showUsage();
  }
  char optString[] = "p:s:f:o:";
  int opt = getopt(argc, argv, optString);
  
  string projectFilter = ".*", searcher = "RegexTemplate". fileFilter = ".*", outputFormat = "Raw";
  while(opt != -1) {
    switch(opt) {
      case 'p':
        projectFilter = optArg;
        break;
      case 's':
        searcher = optArg;
        break;
      case 'f':
        fileFilter = optArg;
        break;
      case 'o':
        outputFormat = optArg;
        break;
    }
      opt = getopt(argc, argv, optString); 
  }
	IoL ioL;
	Io *io = &ioL;
	cout << io->fileExists("/tmp") << "\n";
	vector<string> dirList = io->listDirectory("/tmp");
	for(auto it = dirList.begin(); it != dirList.end(); it++) {
		cout << *it <<endl;
	}
  
	return 0;
}


void showUsage() {

string usage = "\tUsage:\nQwikProjSearch [...OPTIONS] [ProjectPaths...]\n\nReads Search specifiers from stdin and outputs the results\n-s [Plain/Regex/RegexTemplate] : Searcher to use. Default is RegexTemplate\n-f FileFilter : FileFilter to use\n-o [Raw/CSV/JSON] : OutputFormat to use\n-p Regex : Regex to use to filter projects\n\n";
cout << usage;

}

