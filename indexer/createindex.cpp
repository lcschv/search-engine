#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "include/indexer.h"

int main(int argc, char** argv){
	// Mapper mapper;
	Indexer indexer;
	// WebGraph webgraph;
	// mapper.printTeste();
	// cout << " >> Loading stopwords.." << endl;
	// webgraph.teste();


	indexer.mapper.loadStopWords();	
	indexer.mapper.loadColectionUrls();
	indexer.mapper.readFilesColection(10);
	indexer.OrdExterna(indexer.mapper.getnumfilesRuns());
	indexer.mapper.ordenaAnchorstoFile();
	indexer.mapper.printColectionLinks();
	indexer.mapper.printVocabularyIdRef();
	indexer.mapper.Graph.pagerank(40);
	indexer.mapper.Graph.printPageRank();

	// mapper.printTokensHash();
	// indexer.mapper.printDocUrlAnchorText();
	
	// indexer.mapper.printTermIdRef();
	// mapper.printDocIdLink();
	// mapper.Graph.printWebGraph();

	// indexer.printTokensHash();
}