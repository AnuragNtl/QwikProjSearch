#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

using namespace std;

class Io {
public:
	virtual bool fileExists(string filePath) = 0;
	virtual bool isDirectory(string);
	virtual bool isFile(string);
	virtual vector<string> listDirectory(string);
};

#endif
