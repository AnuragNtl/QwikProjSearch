#ifndef IO_L
#define IO_L

#include <boost/filesystem.hpp>
#include "IO.h"

#include <string>
#include <vector>

using namespace std;


namespace ProjSearch {
	class IoL : public Io {
	public:
		IoL();
		bool fileExists(string) const;
		bool isDirectory(string) const;
		bool isFile(string) const;
		vector<string> listDirectory(string) const;
	};
};

#include "IO_L.h"


#endif

