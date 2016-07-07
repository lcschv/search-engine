#include <htmlcxx/html/Node.h>
#include <htmlcxx/html/ParserDom.h>
#include <string>
#include <istream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <htmlcxx/html/Node.h>
#include <htmlcxx/html/utils.h>
#include <htmlcxx/html/Uri.h>
#include <algorithm> 
#include <htmlcxx/html/CharsetConverter.h>
#include <boost/tokenizer.hpp>
#include <vector> 
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include "include/CkString.h"
#include "include/CkSpider.h"
#include "WebGraph.h"
using namespace std;
using namespace boost;
using namespace htmlcxx;
using namespace HTML;

struct trupla{
	int termId;
	int doc_id;
	int freq;
};

struct idDoclen{
	int id;
	int doclen;
	string title;
};

struct idDf{
	int id;
	int df;
};

struct termDocFreq{
    int doc_id;
    int frequency;
};

struct TokenFile{
	string token;
	int tokenpos;
};

class Mapper {

	private:
		CkString tempUrl,aux1,aux2,aux3,aux4,newDomain;
		CkString tempBaseDomain;
		CkSpider spider;
		termDocFreq tempTermDocFreq;
		int numOfTriplas;
		int docCount;
		int vocTermId;
		string outlink;
	 	string url;
		set<string> stopwords;
		vector<termDocFreq> termPerDoc;
		vector<trupla> run;
		vector<trupla> runAnchor;
		
		unordered_map <string, int > LinkDocRef; // Hash que reserva LinkDocRef[URL] = docID;
		unordered_map <int,string> DocIdLink; // Hash que reserva DocIDLink[ID] = URL;
		unordered_map <string,idDoclen> ColectionLinks; // Hash que reserva DocIDLink[ID] = URL
		unordered_map <string,unordered_map <string,int>> DocUrlAnchorText; // Hash que reserva LINKS e os anchor texts que apontam para ele.
		
	public:
		unordered_map <int, TokenFile> TermIdRef; // hash que guarda termIdRef[IDDOTERMO] = token;
		int outFileNumber;
		unordered_map <string, idDf> VocabularyIdRef;
		unordered_map <string, vector<termDocFreq> > tokensHash; // Hash que reserva para cada token um vector de documentos em que ocorrem;
		int sumTruplas;
		int filesRuns;
		Mapper(){
			numOfTriplas = 1;
			outFileNumber=0;
			int sumTruplas =0;
			docCount = 0;
			vocTermId = 0;
			filesRuns=0;
			aux1 = "http://";
			aux2 = "https://";
			aux3 = "www.";
			aux4 = "ftp://";
		}
		WebGraph Graph;
		int getnumfilesRuns();
		void loadColectionUrls();
		void printVocabularyIdRef();
		void printTeste();
		void remove_accents(string &str);
		void loadStopWords();
		void readFilesColection(int numFiles);
		void parserTokenizer(string html);
		void printTokensHash();
		void printColectionLinks();
		void printTermIdRef();
		void printDocIdLink();
		int insertToken(string token);
		void insertAnchorToken(string token);
		void printDocUrlAnchorText();
		void WriteToFile(int outFileNumber);
		// void WriteAnchorsToFile(int outFileNumber);
		void ordenaAnchorstoFile();
		string parse_url(string outlink);
};
