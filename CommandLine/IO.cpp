#include "IO.h"

using namespace ProjSearch;

const char* ProjReadException :: what() const noexcept(true) {
	return "Error in reading filesystem details";
}
