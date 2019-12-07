#include "ProjRepository.h"
#include <algorithm>
#include "RegexSearcher.h"

using namespace ProjSearch;

ProjectListFilter :: ProjectListFilter(ProjectRepository *ProjectRepository, set<string> excludedDirectories) : projectRepository(projectRepository) {
	this->excludedDirectories = excludedDirectories;
}

ProjectListFilter :: ProjectListFilter(ProjectRepository *projectRepository) : projectRepository(projectRepository) {}

bool ProjectListFilter :: operator()(string directory) {
 return excludedDirectories.find(directory) != excludedDirectories.end() || projectRepository->io->isFile(directory);
}

ProjectRepository :: ProjectRepository(Io *io, Searcher *s) : io(io), searcher(s) {
  fileFilterRegexes.push_back(".*");
}

void ProjectRepository :: addProject(string projectPath) {
	vector<string> projectPathVector;
	projectPathVector.push_back(projectPath);
	this->projectPath.insert(pair<string, vector<string> >(projectPath, projectPathVector));
}



void ProjectRepository :: addProjectContainerDirectory(string projectDirPath, set<string> exclude) {
	vector<string> contents = io->listDirectory(projectDirPath);
	vector<string> :: iterator filteredPaths = remove_if(contents.begin(), contents.end(), ProjectListFilter(this, exclude));
	vector<string> containerDirectory;
	for_each(contents.begin(), filteredPaths, [&containerDirectory] (string path) {
		containerDirectory.push_back(path);
	});
	projectPath.insert(pair<string, vector<string> >(projectDirPath, containerDirectory));
}

void ProjectRepository :: addProjectContainerDirectory(string projectDirPath) {
	addProjectContainerDirectory(projectDirPath, set<string>());
}

void ProjectRepository :: setFileFilters(vector<string> fileFilterRegexes) {
  this->fileFilterRegexes = fileFilterRegexes;
}

vector<SearchResults> ProjectRepository :: searchInSpecificProjects(vector<string> projects, vector<string> searchRegexes) {
  vector<SearchResults> searchResults;
  for(auto project = projects.begin(); project != projects.end(); project++) {
		if(projectPath.find(*project) != projectPath.end()) {
      for_each(projectPath[*project].begin(), projectPath[*project].end(), [&searchResults, searchRegexes, this](string projectDir) {
          vector<string> projectDirList = {projectDir};
          vector<SearchResults> subSearchResults = searchInSpecificProjects(projectDirList, searchRegexes);
          for_each(subSearchResults.begin(), subSearchResults.end(), [&searchResults](SearchResults searchResult) {
              searchResults.push_back(searchResult);
              });
          });
		} else {
      //scan dir for files and apply to each file contents
      DirectoryFilter directoryFilter(this->io, fileFilterRegexes);
      vector<string> fileNamelist = directoryFilter(*project);
      for(vector<string> :: iterator it = fileNamelist.begin(); it != fileNamelist.end(); it++) {
        string filePath = *it;
        vector<SearchResults> fileSearchResults = searcher->searchFor(getContents(filePath).c_str(), searchRegexes);
        for_each(fileSearchResults.begin(), fileSearchResults.end(), [&searchResults] (SearchResults searchResult) {
            searchResults.push_back(searchResult);
            });
      }
    }

}
return searchResults;
}

DirectoryFilter :: DirectoryFilter(Io *io, vector<string> regexes) : regexes(regexes) {}


vector<string> DirectoryFilter :: operator()(string directory) {
  vector<string> fileList = io->listDirectory(directory);
  vector<string> matchingFiles;
  RegexSearcher regexSearcher;
  for_each(fileList.begin(), fileList.end(), [&matchingFiles, &regexSearcher, this](string file) {
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


vector<SaerchResults> ProjectRepository :: searchInAllProjects(vector<string> regexes) {
  for(auto it = projectPath.begin(); it != projectPath.end(); it++) {
    searchInSpecificProjects(it->second, regexes);
  }
}

