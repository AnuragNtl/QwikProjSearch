#include "ProjRepository.h"


using namespace ProjSearch;

ProjectListFilter :: ProjectListFilter(ProjectRepository *ProjectRepository, set<string> excludedDirectories) : projectRepository(projectRepository) {
	this->excludedDirectories = excludedDirectories;
}

ProjectListFilter :: ProjectListFilter(ProjectRepository *projectRepository) : projectRepository(projectRepository) {}

bool ProjectListFilter :: operator()(string directory) {
 return excludedDirectories.find(directory) != excludedDirectories.end() || projectRepository->io->isFile();
}

ProjectRepository :: ProjectRepository(Io *io, Searcher *s) : io(io), searcher(s) {}

void ProjectRepository :: addProject(string projectPath) {
	vector<string> projectPathVector;
	projectPathVector.push_back(projectPath);
	projectPath.insert(pair<string, vector<string> >(projectPath, projectPathVector));
}



void ProjectRepository :: addProjectContainerDirectory(string projectDirPath, set<string> exclude) {
	vector<string> contents = io->listDirectory(projectDirPath);
	vector<string> :: iterator filteredPaths = remove_if(contents.begin(), contents.end(), ProjectListFilter(this, exclude));
	vector<string> containerDirectory;
	for_each(contents.begin(), filteredpaths, [&containerDirectory] (string path) {
		containerDirectory.push_back(path);
	});
	projectPath.insert(pair<string, vector<string> >(projectDirPath, containerdirectory));
}

void ProjectRepository :; addProjectContainerDirectory(string projectDirPath) {
	addProjectContainerDirectory(projectDirPath, set<string>());
}

vector<SearchResults> ProjectRepository :: searchInSpecificProjects(vector<string> projects, vector<string> searchRegexes) {
  vector<SearchResults> searchResults;
  for(auto project = projects.begin(); project != projects.end(); project++) {
		if(!projectPath.find(*project)) {
      for_each(projectPath[*project].begin(), projectPath[*project].end(), [](string projectDir) {
          vector<SearchResults> subSearchResults = searchInSpecificProjects(projectDir);
          for_each(subSearchResults.begin(), subSearchResults.end(), [](SearchResults searchResult) {
              searchResults.push_back(searchResult);
              });
          });
		} else {
      //scan dir for files and apply to each file contents

    }

}
return searchResults;
}

DirectoryFilter :: DirectoryFilter(IO *io, vector<string> regexes) : regexes(regexes) {}


vector<string> DirectoryFilter :: operator(string directory) {
  vector<string> fileList = io->listDirectory(directory);
  vector<string> matchingFiles;
  RegexSearcher regexSearcher;
  for_each(fileList.begin(), fileList.end(), [&matchingFiles](string file) {
    if(io->isFile(file)) {
      vector<SearchResults> searchResults = regexSearcher.searchFor(file.c_str(), regexes);
      for_each(searchResults.begin(), searchResults.end(), [&matchingFiles](SearchResults searchResult) {
        matchingFiles.push_back(directory + "/" + searchResult.match);
        });
      } else {
        vector<string> sublist = (*this)(directory);
        for_each(subList.begin(), subList.end(), [&matchingFiles](string subDirFile) {
          matchingFiles.push_back(subDirFile);
          });
      }
      });
  return matchingFiles;
}

vector<SearchResults> ProjSearch :: searchInFile(string filePath) {
  string fileContents = getContents(filepath);
  return searcher->searchFor(fileContents.c_str(), regexes);
}

