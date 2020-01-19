#include "CsvOutputFormat.h"
#include "Searcher.h"

using namespace ProjSearch;
using namespace std;

ostream& CsvOutputFormat :: format(ostream &out) {
  vector<string> headings = {"row", "col", "filePath", "offset", "fileType", "match"};
  out << join(headings, ",") << "\n";
  for(vector<SearchResults> :: iterator it = searchResults.begin(); it != searchResults.end(); it++) {
   string row = join({to_string(it->row), to_string(it->col), it->filePath, to_string(it->offset), to_string(it->fileType), it->match}, ",");
   out << row <<"\n";
  } 
  return out;
}

string CsvOutputFormat :: escape(string data) {
  return "\"" + replace(data, "\"", "\\\"") + "\"";
}

string CsvOutputFormat :: join(vector<string> data, string delim) {
  string row = "";
  int i;
  for(i = 0; i < data.size() - 1; i++) {
    row = row + data[i] + ",";
  }
  row = row + data[i];
  return row;
}

