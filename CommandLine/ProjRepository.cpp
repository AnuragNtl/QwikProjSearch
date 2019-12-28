#include "ProjRepository.h"
#include <algorithm>
#include "RegexSearcher.h"
#include <thread>

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
	this->projectPath[projectPath] = vector<string>();
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
		if(projectPath.find(*project) != projectPath.end() && projectPath[*project].size() > 0) {
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
      //thread filterThread([&directoryFilter](string project) { directoryFilter(project); }, *project);
      thread filterThread(directoryFilter, *project);
      /*for(vector<string> :: iterator it = fileNamelist.begin(); it != fileNamelist.end(); it++) {
        string filePath = *it;
        //cout << "Searching in " << filePath <<"\n";
        vector<SearchResults> fileSearchResults = searcher->searchFor(getContents(filePath).c_str(), searchRegexes);
        for_each(fileSearchResults.begin(), fileSearchResults.end(), [&searchResults] (SearchResults searchResult) {
            searchResults.push_back(searchResult);
            });
      }
      */
      while(!directoryFilter.isDone()) {
        string filePath;
        directoryFilter >> filePath;
        cerr << "Searching in " << filePath <<"\n";
        vector<SearchResults> fileSearchResults = searcher->searchFor(getContents(filePath).c_str(), searchRegexes); 
        for_each(fileSearchResults.begin(), fileSearchResults.end(), [&searchResults, filePath] (SearchResults searchResult) {
            searchResult.filePath = filePath;
            searchResults.push_back(searchResult);
            });
      }
        filterThread.join();
        //cout << "Done\n";
    }

}
return searchResults;
}

DirectoryFilter :: DirectoryFilter(Io *io, vector<string> regexes) : io(io), regexes(regexes), done(new bool(false)), filteredPathsMutex(new mutex), filteredPaths(new queue<string>) {}

/*  DirectoryFilter :: DirectoryFilter(const DirectoryFilter &directoryFilter) : DirectoryFilter(directoryFilter.io, directoryFilter.regexes) {
  this->filteredPaths = directoryFilter.filteredPaths;
  this->filteredPathsMutex = directoryFilter.filteredPathsMutex;
  
}
*/

DirectoryFilter :: ~DirectoryFilter() {
  if(isDone()) {
    delete done;
    delete filteredPathsMutex;
    delete filteredPaths;
  }
}

bool DirectoryFilter :: isDone() const {
  return *done && filteredPaths->empty();
}

vector<string> DirectoryFilter :: operator()(string directory) {
  *done = false;
  vector<string> filtered = filterDirectory(directory);
  *done = true;
  return filtered;
}

DirectoryFilter& DirectoryFilter :: operator>>(string &directory) {
  while(true) {
    filteredPathsMutex->lock();
    bool isNotEmpty = !filteredPaths->empty();
    filteredPathsMutex->unlock();
    if(isNotEmpty) {
      break;
    }
  }
  filteredPathsMutex->lock();
  directory = filteredPaths->front();
  filteredPaths->pop();
  filteredPathsMutex->unlock();
  return *this;
}

vector<string> DirectoryFilter :: filterDirectory(string directory) {
  if(directory[directory.size() - 1] != '/') {
    directory = directory + "/";
  }
  vector<string> fileList = io->listDirectory(directory);
  vector<string> matchingFiles;
  RegexSearcher regexSearcher;
  for_each(fileList.begin(), fileList.end(), [&matchingFiles, &regexSearcher, this, &directory](string file) {
      cerr << "Scanning " <<file <<"\n";
      file = directory + file;
      if(io->isFile(file)) {
      vector<SearchResults> searchResults = regexSearcher.searchFor(file.c_str(), regexes);
        if(searchResults.size() > 0) {
          filteredPathsMutex->lock();
          filteredPaths->push(file.c_str());
          filteredPathsMutex->unlock();
          matchingFiles.push_back(file);
        }
      } else if(io->isDirectory(file)) {
        vector<string> subList = (*this)(file);
        for_each(subList.begin(), subList.end(), [&matchingFiles](string subDirFile) {
          matchingFiles.push_back(subDirFile);
          });
      }
      });
  return matchingFiles;
}


vector<SearchResults> ProjectRepository :: searchInAllProjects(vector<string> regexes) {
  vector<SearchResults> searchResults;
  for(auto it = projectPath.begin(); it != projectPath.end(); it++) {
    vector<SearchResults> searchResultsSubList = searchInSpecificProjects(it->second, regexes);
    for_each(searchResultsSubList.begin(), searchResultsSubList.end(), [&searchResults](SearchResults searchResult) {
        searchResults.push_back(searchResult);
        });
  }
  return searchResults;
}


vector<string> ProjectRepository :: findProjects(string regex) {
  vector<string> regexList{regex};
  vector<string> matchedFiles;
  for(auto it = projectPath.begin(); it != projectPath.end(); it++) {
    RegexSearcher regexSearcher;
    vector<string> projectDirectories = it->second;
    projectDirectories.push_back(it->first);
    for_each(projectDirectories.begin(), projectDirectories.end(), [regexSearcher, regexList, &matchedFiles](string projectDirectory) {
        if(regexSearcher.searchFor(projectDirectory.c_str(), regexList).size() > 0) {
        matchedFiles.push_back(projectDirectory);
        }
        });
  }
  return matchedFiles;
}

