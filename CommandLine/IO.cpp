#include "IO.h"
#include "IO_L.h"

using namespace ProjSearch;

const char* ProjReadException :: what() const noexcept(true) {
	return "Error in reading filesystem details";
}

Io* getDefaultIoProvider() {
  return new IoL;
  }
