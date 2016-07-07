#include "loaders.h"



// Relacionados ao Index normal
fstream& Loaders::GotoLine(int num){
    this->index.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        this->index.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return this->index;
};

void Loaders::loadIndex(){
	index.open("searcher/searchfiles/index.txt");
};

void Loaders::loadUrlLen(){
	string line;
	ifstream urlsfile;
	vector<string> words (3);
	urlsfile.open("searcher/searchfiles/urlslen.txt");
	while (!urlsfile.eof()){
		getline(urlsfile,line);
		if (line != ""){
			boost::split(words, line, boost::is_any_of("\t"));
			urlLenHash[stoi(words[1])].url = words[0];
			urlLenHash[stoi(words[1])].doc_len = stoi(words[2]);
		};
	};
	urlsfile.close();
};

string Loaders::getdocurl(int doc_id){
	return urlLenHash[doc_id].url;
};

int Loaders::getdocLen(int doc_id){
	return urlLenHash[doc_id].doc_len;
};

void Loaders::loadVocabulary(){
	string line;
	ifstream vocfile;
	vector<string> words (4);
	vocfile.open("searcher/searchfiles/vocabulary.txt");
	while (!vocfile.eof()){
		getline(vocfile,line);
		if (line != ""){
			boost::split(words, line, boost::is_any_of("\t"));
			vocabularyHash[words[0]].id = stoi(words[1]);
			vocabularyHash[words[0]].df = stoi(words[2]);
			vocabularyHash[words[0]].pos = stoi(words[3]);
		};
	};
	vocfile.close();
};

int Loaders::gettokenId(string token){
	if (vocabularyHash.find(token) == vocabularyHash.end()){
		return -1;
	}else{
		return vocabularyHash[token].id;
	}
};
int Loaders::gettokenDf(string token){
	if (vocabularyHash.find(token) == vocabularyHash.end()){
		return -1;
	}else{
		return vocabularyHash[token].df;
	}
};
int Loaders::gettokenPos(string token){
	if (vocabularyHash.find(token) == vocabularyHash.end()){
		return -1;
	}else{
		return vocabularyHash[token].pos;
	}
};

vocabinfo Loaders::gettokenInfo(string token){
	if (vocabularyHash.find(token) == vocabularyHash.end()){
		return {0,0,0};
	}else{
		return vocabularyHash[token];
	}
};




// Methods relacionados ao pagerank
void Loaders::loadPageRank(){
	string line;
	ifstream pagerankfile;
	vector<string> words (2);
	pagerankfile.open("searcher/searchfiles/pagerank.txt");
	while (!pagerankfile.eof()){
		getline(pagerankfile,line);
		if (line != ""){
			boost::split(words, line, boost::is_any_of("\t"));
			pagerankHash[stoi(words[0])] = stof(words[1]);
		};
	};
	pagerankfile.close();
};

float Loaders::getdocPR(int doc_id){
	return pagerankHash[doc_id];
};


// Methods relacionados ao AnchorText
fstream& Loaders::GotoLineAchor(int num){
    this->indexAnchor.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        this->indexAnchor.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return this->indexAnchor;
};



void Loaders::loadAnchorIndex(){
	indexAnchor.open("searcher/searchfiles/indexAnchor.txt");
};


int Loaders::gettokenIdAnchor(string token){
	if (VocabularyAnchorHash.find(token) == VocabularyAnchorHash.end()){
		return -1;
	}else{
		return VocabularyAnchorHash[token].id;
	}
};


void Loaders::loadAnchorVocabulary(){
	string line;
	vector<string> words (3);
	ifstream vocancfile;
	vocancfile.open("searcher/searchfiles/TermPositionAnchor.txt");
	while (!vocancfile.eof()){
		getline(vocancfile,line);
		if (line !=""){
			boost::split(words, line, boost::is_any_of("\t"));
			VocabularyAnchorHash[words[0]].id = stoi(words[1]);
			VocabularyAnchorHash[words[0]].pos =  stoi(words[2]);	
		}
	};
	vocancfile.close();
};

int Loaders::getAnchortokenPos(string token){
	if (VocabularyAnchorHash.find(token) == VocabularyAnchorHash.end()){
		return -1;
	}else{
		return VocabularyAnchorHash[token].pos;
	}
};


// // Funcao que retorna vetor com documentos que possuem o termo pesquisado..
vector<TermDocTF> Loaders::getvectorofdocs(int id, int pos){
	vector<TermDocTF> hits;
	string line;
	TermDocTF termpTupl;
	int term;
	if (id != -1){
		this->GotoLine(pos);
		index >> term >> termpTupl.doc_id >> termpTupl.TF;
		while (!index.eof() && term == id){
			hits.push_back(termpTupl);
			index >> term >> termpTupl.doc_id >> termpTupl.TF;
		}	
	}
	return hits;
};




vector<TermDocTF> Loaders::getvectorofdocsAnchor(int id, int pos){
	vector<TermDocTF> hits;
	string line;
	TermDocTF termpTupl;
	int term;
	if (id != -1){
		this->GotoLineAchor(pos);
		indexAnchor >> term >> termpTupl.doc_id >> termpTupl.TF;
		while (!index.eof() && term == id){
			hits.push_back(termpTupl);
			indexAnchor >> term >> termpTupl.doc_id >> termpTupl.TF;
		}	
	}
	return hits;
};