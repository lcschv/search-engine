#include "../include/indexer.h"


struct cmp {
  bool operator()( const truplaFromFile & e1, const truplaFromFile & e2) {
    if( e1.termId != e2.termId)
      return (e1.termId > e2.termId);
    return (e1.doc_id > e2.doc_id);
}
};

void Indexer::MyHeapPush(truplaFromFile truplas) {
    truplaQueue.push_back(truplas);
    push_heap(truplaQueue.begin(), truplaQueue.end(), cmp());
};


// Pop da heap, retorna uma truplafromfile, eh utilizado o cmp para verificar qual eh o menor termId que deve ser retirado.
truplaFromFile Indexer::MyHeapPop() {

    truplaFromFile tempTrupla = truplaQueue.front();
    //Essa operação irá mover o link de menor nível para o fim do vector.
    pop_heap(truplaQueue.begin(), truplaQueue.end(), cmp());
    //Remove o último elemento do vector, o qual é a URL de menor nível;
    truplaQueue.pop_back();
  // PriorityQueue.shrink_to_fit();
    return tempTrupla;
};


void Indexer::OrdExterna(int filesRuns){
	ofstream index;
	index.open("searchfiles/index.txt");
	string line;
	vector<string> strs;
	int aux;
	int tempId = -1;
	int linenumber=1;
	aux = filesRuns-1;
	//Vetor de ponteiros para files..
	vector<ifstream> filesVector (filesRuns);
	truplaFromFile tempTrupla;
	for (int i=0;i<filesVector.size();i++){	
		filesVector[i].open("indexout/"+ to_string(aux));
		getline(filesVector[i],line);
		boost::split(strs, line, boost::is_any_of("\t "));
		// Trupla temporaria que salva o endereco de qual RUN veio a trupla
		tempTrupla.termId = stoi(strs[0]);
		tempTrupla.doc_id = stoi(strs[1]);
		tempTrupla.freq = stoi(strs[2]);
		tempTrupla.fileid = i;

		MyHeapPush(tempTrupla);
		aux--;
	}
	// cout << "Terminei primeiro for com sucesso..."<<endl;
	// Enquanto a Heap nao estiver vazia, realiza Pop das truplas e insere recupera novas truplas das runs.
	while (!truplaQueue.empty()){
	    truplaFromFile saida = MyHeapPop();
	  
	    if (tempId != saida.termId){
			mapper.TermIdRef[saida.termId].tokenpos = linenumber;
	    }
	     tempId = saida.termId;
	     linenumber++;
	    //Realiza a escrita do indice invertido
	    index << saida.termId << " "<<saida.doc_id<<" "<<saida.freq<<endl;
	    if (getline(filesVector[saida.fileid],line)){
	    	boost::split(strs, line, boost::is_any_of("\t "));
	    	//divide a linha recuperada das runs por tabulacoes;
	    	tempTrupla.termId = stoi(strs[0]);
			tempTrupla.doc_id = stoi(strs[1]);
			tempTrupla.freq = stoi(strs[2]);
			tempTrupla.fileid = saida.fileid;
			MyHeapPush(tempTrupla);
	    }
	}
	index.close();
};

void Indexer::OrdExternaAnchor(int filesRuns){
	ofstream index;
	index.open("searchfiles/indexAnchor.txt");
	string line;
	vector<string> strs;
	int aux;
	aux = filesRuns-1;
	truplaQueue.clear();
	//Vetor de ponteiros para files..
	vector<ifstream> filesVector (filesRuns);
	truplaFromFile tempTrupla;
	for (int i=0;i<filesVector.size();i++){	
		filesVector[i].open("indexoutAnchors/"+ to_string(aux));
		getline(filesVector[i],line);
		boost::split(strs, line, boost::is_any_of("\t "));
		// Trupla temporaria que salva o endereco de qual RUN veio a trupla
		tempTrupla.termId = stoi(strs[0]);
		tempTrupla.doc_id = stoi(strs[1]);
		tempTrupla.freq = stoi(strs[2]);
		tempTrupla.fileid = i;

		MyHeapPush(tempTrupla);
		aux--;
	}
	// cout << "Terminei primeiro for com sucesso..."<<endl;
	// Enquanto a Heap nao estiver vazia, realiza Pop das truplas e insere recupera novas truplas das runs.
	while (!truplaQueue.empty()){
	    truplaFromFile saida = MyHeapPop();
	    //Realiza a escrita do indice invertido

	    index << saida.termId << " "<<saida.doc_id<<" "<<saida.freq<<endl;
	    if (getline(filesVector[saida.fileid],line)){
	    	boost::split(strs, line, boost::is_any_of("\t "));
	    	//divide a linha recuperada das runs por tabulacoes;
	    	tempTrupla.termId = stoi(strs[0]);
			tempTrupla.doc_id = stoi(strs[1]);
			tempTrupla.freq = stoi(strs[2]);
			tempTrupla.fileid = saida.fileid;
			MyHeapPush(tempTrupla);
	    }
	}
	index.close();
};

void Indexer::printTokensHash(){ 
	// cout << "O valor de teste eh: "<<this->teste<<endl;
	cout << "NumofTruplas:"<<mapper.tokensHash.size()<<endl;
	for (auto it:mapper.tokensHash){
		for (auto it2:mapper.tokensHash[it.first]){	
			cout <<mapper.VocabularyIdRef[it.first].id<<"	docid: " <<it2.doc_id<< "	Frequency:"<<it2.frequency<<endl;
		}
	}
};