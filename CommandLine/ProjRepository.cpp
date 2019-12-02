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

void Projectrepository :: searchInSpecificProjects(vector<string> projects, vector<string> searchRegexes) {
	for(auto project = projects.begin(); project != projects.end(); project++) {
		if(!projectPath.find(*project)) {
			searcher->searchFor()
		}
}
}

DirectoryFilter :: DirectoryFilter(vector<string> regexes) : regexes(regexes) {}

vector<string> DirectoryFilter :: operator(string directory) {
  
}

