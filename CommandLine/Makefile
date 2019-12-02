GXX=g++
LDIR= -L ~/boost_1_67_0/stage/lib
IDIR= -I ~/boost_1_67_0/
CFLAGS= -std=c++11 -g
LIBS= -lboost_system -lboost_regex -lboost_filesystem

RegexTemplateMenuGenerator : Searcher.cpp RegexSearcher.cpp RegexTemplateSearcher.cpp RegexTemplateGeneration.cpp RegexTemplateMenuGenerator.cpp
	$(GXX) $(CFLAGS) $(IDIR) $(LDIR) $^ -o bin/$@ $(LIBS)

QwikProjSearch : IO.cpp IO_L.cpp QwikProjSearch.cpp
	$(GXX) $(CFLAGS) $(IDIR) $(LDIR) $^ -o bin/$@ $(LIBS)
