#include "IO_L.h"
#include <boost/filesystem/path.hpp>

using namespace ProjSearch;

IoL :: IoL() {}

bool IoL :: fileExists(string filePath) const {
	return boost :: filesystem :: exists(filePath);
}

bool IoL :: isFile(string filePath) const {
	return boost :: filesystem :: is_regular(filePath) || 
		boost :: filesystem :: is_symlink(filePath) || 
		boost :: filesystem :: is_other(filePath);
}

bool IoL :: isDirectory(string filePath) const {
	return boost :: filesystem :: is_directory(filePath);
}

vector<string> IoL :: listDirectory(string filePath) const {
	if(!isDirectory(filePath)) {
		throw ProjReadException();
	}
	vector<string> fileList;
	boost :: filesystem :: path directoryPath(filePath);
	for(boost :: filesystem :: directory_iterator it(directoryPath); 
		it != boost :: filesystem :: directory_iterator();
		 it++) {
		fileList.push_back(it->path().filename().string());
	}
	return fileList;
}
