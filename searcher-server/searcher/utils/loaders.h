#ifndef LOADERS_H
#define LOADERS_H

#include <string>
#include <istream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;


struct IdDoclen
{
	string url;
	int doc_len;
};

struct vocabinfo
{
	int id;
	int df;
	int pos;
};

struct TermDocTF
{
	int doc_id;
	int TF;
};
struct anchinf
{
	int id;
	int pos;
};


class Loaders{
	private:
		typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
		unordered_map <int, IdDoclen> urlLenHash;
		unordered_map <int,float> pagerankHash;
		unordered_map <string,vocabinfo> vocabularyHash;
		unordered_map <string,anchinf> VocabularyAnchorHash;

		vector<TermDocTF> docsTerm;
		fstream index;
		fstream indexAnchor;
	public:
		Loaders(){
			loadUrlLen();
			loadPageRank();
			loadVocabulary();
			loadIndex();
			loadAnchorIndex();
			loadAnchorVocabulary();
		};
		void loadUrlLen();
		void loadPageRank();
		void loadVocabulary();
		void loadIndex();
		float getdocPR(int doc_id);
		string getdocurl(int doc_id);
		int getdocLen(int doc_id);
		int gettokenId(string token);
		int gettokenDf(string token);
		int gettokenPos(string token);
		vocabinfo gettokenInfo(string token);
		fstream& GotoLine(int num);
		vector<TermDocTF> getvectorofdocs(int id, int pos);
		void loadAnchorIndex();
		void loadAnchorVocabulary();
		int getAnchortokenPos(string token);
		int gettokenIdAnchor(string token);
		fstream& GotoLineAchor(int num);
		vector<TermDocTF>getvectorofdocsAnchor(int id, int pos);

};



#endif