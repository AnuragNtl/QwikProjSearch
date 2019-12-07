#ifndef PROJ_REPOSITORY_H
#define PROJ_REPOSITORY_H

#include <string>
#include <vector>
#include "Io.h"

#define FILE_TYPE_BINARY 0
#define FILE_TYPE_TEXT 1

using namespace std;

namespace ProjSearch {
  class ProjectRepository {
    private:
    	Io *io;
      map<string, vector<string> > projectPath;
      Searcher *searcher;
    public:
      explicit ProjectRepository(Io *io, Searcher *);
      void addProject(string projectPath);
      void addProjectContainerDirectory(string projectDirPath, set<string> exclude);
      void addProjectContainerDirectory(string projectDirPath);
      vector<SearchResults> searchInSpecificProjects(vector<string> projects, vector<string> regex);
      vector<SearchResults> searchInAllProjects(vector<string> regex);
      vector<string> findProjects(string regex);
      friend class ProjectListFilter;
  };

  class ProjectListFilter {
  private:
    ProjectRepository *projectRepository;
    set<string> excludedDirectories;
  public:
    explicit ProjectListFilter(ProjectRepository *);
    ProjectListFilter(ProjectRepository *, set<string>);
    bool operator()(string directory);
  };

  class DirectoryFilter {
    private:
      vector<string> regexes;
      IO *io;
    public:
      DirectoryFilter(IO *io, vector<string>);
      vector<string> operator()(string directory);
  };
  vector<SearchResults> searchInFile(string filePath);
};

#endif

