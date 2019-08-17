#ifndef PROJ_REPOSITORY_H
#define PROJ_REPOSITORY_H

#include <string>
#include <vector>
#include "Io.h"

#define FILE_TYPE_BINARY 0
#define FILE_TYPE_TEXT 1

namespace ProjSearch {
  class ProjectRepository {
    private:
    	Io *io;
      map<string, vector<string> > projectPath;
    public:
      ProjectRepository(Io *io);
      void addProject(string projectPath);
      void addProjectContainerDirectory(string projectDirPath);
      string searchInSpecificProjects(vector<string> projects);
  };
};

#endif

