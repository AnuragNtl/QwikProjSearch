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
    public:
      explicit ProjectRepository(Io *io);
      void addProject(string projectPath);
      void addProjectContainerDirectory(string projectDirPath, set<string> exclude);
      void addProjectContainerDirectory(string projectDirPath);
      string searchInSpecificProjects(vector<string> projects, string regex);
      string searchInAllProjects(string regex);
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
};

#endif
