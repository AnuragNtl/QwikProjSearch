GXX=g++
LDIR= -L ~/boost_1_67_0/stage/lib
IDIR= -I ~/boost_1_67_0/
CFLAGS= -std=c++11 -g
LIBS= -lboost_system -lboost_regex -lboost_filesystem -lpthread
SEARCHER_DEPENDENCY= Searcher.cpp PlainSearcher.cpp RegexSearcher.cpp RegexTemplateSearcher.cpp 
OUTPUT_FORMAT_DEPENDENCY= OutputFormat.cpp JsonOutputFormat.cpp TableOutputFormat.cpp CsvOutputFormat.cpp

RegexTemplateMenuGenerator : $(SEARCHER_DEPENDENCY) RegexTemplateGeneration.cpp RegexTemplateMenuGenerator.cpp
	$(GXX) $(CFLAGS) $(IDIR) $(LDIR) $^ -o bin/$@ $(LIBS)

QwikProjSearch : $(SEARCHER_DEPENDENCY) $(OUTPUT_FORMAT_DEPENDENCY) IO.cpp IO_L.cpp ProjRepository.cpp QwikProjSearch.cpp
	$(GXX) $(CFLAGS) $(IDIR) $(LDIR) $^ -o bin/$@ $(LIBS)
