#include <iostream>
#include <string>
#include "IO.h"
#include "IO_L.h"

using namespace std;

using namespace ProjSearch;

int main(int argc, char *argv[]) {
	IoL io;
	cout << io.fileExists("/tmp") << "\n";
	return 0;
}

