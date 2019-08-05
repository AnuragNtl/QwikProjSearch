#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

using namespace std;

namespace ProjSearch {
	class ProjReadException : public exception {
		virtual const char* what() const noexcept(true);
	};
	class Io {
	public:
		virtual bool fileExists(string filePath) const = 0;
		virtual bool isDirectory(string) const = 0;
		virtual bool isFile(string) const = 0;
		virtual vector<string> listDirectory(string) const = 0;
	};
};

#endif
