#include "../include/mapper.h"
// using namespace htmlcxx;

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

bool compare_entry( const trupla & e1, const trupla & e2) {
	if( e1.termId != e2.termId)
		return (e1.termId < e2.termId);
  	return (e1.doc_id < e2.doc_id);
};
void Mapper::printTokensHash(){ 
	// cout << "O valor de teste eh: "<<this->teste<<endl;
	cout << "NumofTruplas:"<<tokensHash.size()<<endl;
	for (auto it:tokensHash){
		for (auto it2:tokensHash[it.first]){	
			// cout <<it.first<<"	docid: " <<it2.doc_id<< "	Frequency:"<<it2.frequency<<endl;
		}
	}
};

void Mapper::printDocUrlAnchorText(){
	// for (auto it:DocUrlAnchorText){
	// 	cout <<"Url: " <<it.first<<endl;
	// 	cout << "anchor_text:	";
	// 	for (auto it2:DocUrlAnchorText[it.first]){
	// 		cout <<it2<<" ";
	// 	}
	// 	cout << "\n";
	// }
};
void Mapper::printVocabularyIdRef(){
	ofstream vocabulary;
	vocabulary.open("searchfiles/vocabulary.txt");
	// cout <<"NumOftokens:" <<VocabularyIdRef.size()<<endl;
	for (auto it:VocabularyIdRef){
		// TOKEN  ID  DocFreqToken	TokenStartPos
		vocabulary << it.first << "	"<< it.second.id<<"	"<<it.second.df<<"	"<<TermIdRef[it.second.id].tokenpos<<endl;
	}
	vocabulary.close();
};
void Mapper::printDocIdLink(){
	for (auto it:DocIdLink){
		cout <<it.second<<endl;
	}
}

void Mapper::printTermIdRef(){
	for (auto it:TermIdRef){
		cout << "TermId:"<<it.first<<"	Termo:"<<it.second.token<<"	pos:"<<it.second.tokenpos<<endl;
	}
};

void Mapper::printColectionLinks(){
	ofstream urlsfile;
	urlsfile.open("searchfiles/urlslen.txt");
	for (auto it:ColectionLinks){
		urlsfile << it.first<<"	"<<it.second.id<<"	"<<it.second.doclen<<"	"<<it.second.title<<endl;
	}
	urlsfile.close();
}

void Mapper::remove_accents(string &str) {
    for(unsigned int i=0;i<str.length();i++) {
        str.at(i) = tolower(str.at(i));
        unsigned char c = str.at(i);
        if ((c == 0xc3) && ((i+1)<str.length())) {
            str.erase (i,1);
            c = str.at(i);
            c = tolower(c);
        }
        if ((c >= 0x30 && c <= 0x39) || (str.at(i) >= 0x61 && str.at(i) <= 0x7a)) {
            //à, á, â, ã, ä
        }else if (( c >= 0xa0 && c <= 0xa4)){
            str[i]='a';
            //ç
        }else if (c == 0xa7) {
            str[i]='c';
            //è, é, ê , ë
        } else if ((c >= 0xa8 && c <= 0xab)){
            str[i]='e';
            //ì, í, î, ï
        } else if ((c >= 0xac && c <= 0xaf)){
            str[i]='i';
            //ñ
        } else if (c == 0xb1) {
            str[i]='n';
            //ò, ó, ô, õ, ö
        } else if ((c >= 0xb2 && c <= 0xb6)){
            str[i]='o';
            //ù, ú, û, ü
        } else if ((c >= 0xb9 && c <= 0xbc)){
            str[i]='u';
            //Se nao for espaco
        }
        else if(c!=0x20){
            unsigned int x;
            x=str[i];
            if((x>=4294967265)&&(x<=4294967270)){ str[i]='a';}else
                if((x>=4294967272)&&(x<=4294967275)){ str[i]='e';}else
                    if((x>=4294967276)&&(x<=4294967279)) {str[i]='i';}else
                        if(((x>=4294967282)&&(x<=4294967287))||(x==4294967280)){ str[i]='o';}else
                            if(x==4294967281){ str[i]='n';}else
                                if((x>=4294967289)&&(x<=4294967292)) {str[i]='u';}else
                                    if(x==4294967271){ str[i]='c';}else{str.replace (i,1," ");}
        }
    }
};
void Mapper::loadStopWords(){
	string word;
	ifstream stopWordsFile;
	stopWordsFile.open("stopwords.txt");
	
	while (!stopWordsFile.eof()){
		getline(stopWordsFile,word);
		// cout << word[word.size()]<<endl;
		stopwords.insert(word);
	}
	stopWordsFile.close();
};
void Mapper::loadColectionUrls(){
	string urlsfromfile;
	ifstream urlsfile;
	urlsfile.open("urls.txt");
	int id = 0;
	while (!urlsfile.eof()){
		getline(urlsfile,urlsfromfile);
		// cout << word[word.size()]<<endl;
		ColectionLinks[urlsfromfile].id = id;
		ColectionLinks[urlsfromfile].doclen = 0;
		id++;
	}
	urlsfile.close();
};

void Mapper::readFilesColection(int numFiles){
	ifstream file;
	string line;
	int cont;
	// string url;
	string htmlofPage;
	int filenumber;
	char c;
	string sentinel = "";
	for (int filenumber=0;filenumber<numFiles;filenumber++){
		string namefile = "files/" + to_string(filenumber);
		file.open(namefile.c_str());
		cont=0;
		while (!file.eof()){
			file.get(c);
			if (c == '|'){
				sentinel+=c;
				file.get(c);
				if (c == '|'){
					sentinel+=c;
					file.get(c);									
					if (c == '|'){
						sentinel+=c;
						file.get(c);
						if (c == ' '){
							sentinel+=c;
							file.get(c);
							if (c=='h'){
								if (cont==0){
									url+=c;
									do{
										file.get(c);
										url+=c;
									} while (c!='|');
									url.pop_back();
									url.pop_back();
									sentinel.clear();
									file.get(c);
								}else{
									// url.erase(std::remove(url.begin(), url.end(), '\r'), url.end());
									// cout << url<<endl;
									LinkDocRef[url] = docCount;
									// Realiza escrita em arquivo do DocID, para retornar na busca posteriormente.
									DocIdLink[docCount] = url;
									parserTokenizer(htmlofPage);
									url.clear();
									docCount++;
									htmlofPage.clear();
									url+=c;
									do{
										file.get(c);
										url+=c;
									} while (c!='|');
									url.pop_back();
									url.pop_back();
									sentinel.clear();
									file.get(c);
								}
								cont=1;
							}	
						}			
					}
				}
			}
			htmlofPage+=sentinel;
			htmlofPage+=c;
			
			sentinel.clear();
		}
		// url.erase(std::remove(url.begin(), url.end(), '\r'), url.end());
		// cout <<url<<endl;
		// htmlofPage.replace(std::remove(htmlofPage.begin(), htmlofPage.end(), '\n'), htmlofPage.end());
		// trim(htmlofPage);
		// cout << htmlofPage<<endl;
		parserTokenizer(htmlofPage);
		LinkDocRef[url] = docCount;
		// Realiza escrita em arquivo do DocID, para retornar na busca posteriormente.
		DocIdLink[docCount] = url;
		docCount++;
		url.clear();
		htmlofPage.clear();
		if (numOfTriplas > 6000){
			WriteToFile(outFileNumber);
			// WriteAnchorsToFile(outFileNumber);
			outFileNumber++;
			filesRuns++;
			sumTruplas +=numOfTriplas;
			numOfTriplas = 0;
		}
		// htmlofPage.erase(std::remove(htmlofPage.begin(), htmlofPage.end(), '\r'), htmlofPage.end());
		file.close();
	}
	if (numOfTriplas != 0){
		WriteToFile(outFileNumber);
		// WriteAnchorsToFile(outFileNumber);
		outFileNumber++;
		filesRuns++;
		sumTruplas +=numOfTriplas;
		numOfTriplas = 0;
	}
};

int Mapper::insertToken(string token){
	auto search = stopwords.find(token);
	if(search == stopwords.end() && token.size() > 1 && token.size() < 20){
		numOfTriplas++;
		// cout << token<<endl;
		// cout << url<<endl;
		ColectionLinks[url].doclen +=1;
		if (tokensHash.find(token) == tokensHash.end()){
	    	tempTermDocFreq.doc_id = ColectionLinks[url].id;

	    	if (VocabularyIdRef.find(token) == VocabularyIdRef.end()){
	    		VocabularyIdRef[token].id = vocTermId;
				// termsRefFile << token<<endl;
	    		TermIdRef[vocTermId].token = token;
	    		vocTermId++;
	    		VocabularyIdRef[token].df =1;
	    	}
	//     		// Adiciona a posicao do token no documento
	    	tempTermDocFreq.frequency = 1;
	    	// Adiciona ao vetor de posiçõess a posição em que ocorreu.
	    	tokensHash[token].push_back(tempTermDocFreq);
	    }
		else{
			if (tokensHash[token].back().doc_id == ColectionLinks[url].id){
				tokensHash[token].back().frequency +=1;
				// cout << "entrei aqui.."<<endl;
			}
			else{
				tempTermDocFreq.doc_id = ColectionLinks[url].id;
				tempTermDocFreq.frequency =1;
				// cout << "Entrei de ca..";
				VocabularyIdRef[token].df +=1;
				tokensHash[token].push_back(tempTermDocFreq);

			}
		}
	}else{
		return 0;
	}
	tempTermDocFreq = {};
	return 1;
};

void Mapper::insertAnchorToken(string token){
	// cout << token<<endl;
	if (DocUrlAnchorText[outlink].find(token) == DocUrlAnchorText[outlink].end()){
    	DocUrlAnchorText[outlink][token] = 1 ;
    	// cout << "New word for anchor text.."<< token<< "	"<< VocabularyIdRef[token]<<endl;

    } else{
    	DocUrlAnchorText[outlink][token] += 1;
    	// cout << "Added frequency for anchor text.."<<endl;	
    }
};

//Checking outlinks that are pointing to the same urldomain..
string Mapper::parse_url(string outlink){
	
	if ((outlink.size() > 4) && (outlink.substr (0,4) == "http")){
		tempUrl = outlink.c_str();
		tempUrl.removeFirst(aux1);
		tempUrl.removeFirst(aux2);
		tempUrl.removeFirst(aux3);
		tempUrl.removeFirst(aux4);
		spider.GetUrlDomain(tempUrl,newDomain);
		tempBaseDomain = spider.getBaseDomain(newDomain);
		string tempBaseDomainStr = tempBaseDomain.getString();
		return tempBaseDomainStr;
	}else{
		return "";
		// cout <<"ignorando:	"<< outlink<<endl;
	}
};

int Mapper::getnumfilesRuns(){
	return filesRuns;
};

void Mapper::ordenaAnchorstoFile(){
	trupla TempTrupla;
	ofstream fileout;
	fileout.open("searchfiles/indexAnchor.txt");
	ofstream fileout2;
	fileout2.open("searchfiles/TermPositionAnchor.txt");


	for (auto it:DocUrlAnchorText){
		TempTrupla.doc_id = ColectionLinks[it.first].id;
		for (auto it2:DocUrlAnchorText[it.first]){
			TempTrupla.termId = VocabularyIdRef[it2.first].id;
			TempTrupla.freq = it2.second;
			runAnchor.push_back(TempTrupla);
		}
	}
	DocUrlAnchorText.clear();
	sort( runAnchor.begin(), runAnchor.end(), compare_entry);
	//Escreve run em disco.
	int posicao = 1;
	int tempid=-1;
	for (auto i:runAnchor){
		if (i.termId != tempid){
			tempid = i.termId;
			fileout2 <<TermIdRef[i.termId].token<<"	"<<i.termId<<"	"<<posicao<<endl;
		}
		fileout <<i.termId<<"	"<<i.doc_id<< "	"<<i.freq<<endl;
		posicao++;
	}
	runAnchor.clear();
	runAnchor.shrink_to_fit();
	fileout.close();
};

// void Mapper::WriteAnchorsToFile(int outFileNumber){
// 	trupla TempTrupla;
// 	ofstream fileout;
// 	string namefileout = "indexoutAnchors/" + to_string(outFileNumber);
// 	fileout.open(namefileout.c_str());

// 	for (auto it:DocUrlAnchorText){
// 		TempTrupla.doc_id = ColectionLinks[it.first];
// 		for (auto it2:DocUrlAnchorText[it.first]){
// 			TempTrupla.termId = VocabularyIdRef[it2.first];
// 			TempTrupla.freq = it2.second;
// 			runAnchor.push_back(TempTrupla);
// 		}
// 	}
// 	DocUrlAnchorText.clear();

// 	sort( runAnchor.begin(), runAnchor.end(), compare_entry);
// 	//Escreve run em disco.
// 	for (auto i:runAnchor){
// 		fileout <<i.termId<<"	"<<i.doc_id<< "	"<<i.freq<<endl;
// 		// cout <<i.termId<<"	"<<i.doc_id<< "	"<<i.freq<<endl;
// 	}
// 	runAnchor.clear();
// 	runAnchor.shrink_to_fit();
// 	fileout.close();
// };

void Mapper::WriteToFile(int outFileNumber){
	trupla TempTrupla;
	ofstream fileout;
	string namefileout = "indexout/" + to_string(outFileNumber);
	fileout.open(namefileout.c_str());

	//Realiza push de todos tokens e suas ocorrencias em cada documento para o vetor RUN, para que seja ordenado e escrito em disco..
	for (auto it:tokensHash){
		for (auto it2:tokensHash[it.first]){
			TempTrupla.termId = VocabularyIdRef[it.first].id;
			TempTrupla.doc_id = it2.doc_id;
			TempTrupla.freq = it2.frequency;
			run.push_back(TempTrupla);
		}
	}
	tokensHash.clear();
	//Realiza ordenacao da run..

	sort( run.begin(), run.end(), compare_entry);
	//Escreve run em disco.
	for (auto i:run){
		fileout <<i.termId<<"	"<<i.doc_id<< "	"<<i.freq<<endl;
		// cout <<i.termId<<"	"<<i.doc_id<< "	"<<i.freq<<endl;
	}
	run.clear();
	run.shrink_to_fit();
	fileout.close();
};

void Mapper::parserTokenizer(string htmlofPage){
	
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	htmlcxx::HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(htmlofPage);
	boost::char_separator<char> sep{" \n\t\r"};
	// Print whole DOM tree
	// cout << dom;
	string s;
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();

	//Dump all text of the document
	it = dom.begin();
	end = dom.end();
  	//Removing scripts, styles, etc.
  	int flag = 0;
	for (; it != end; ++it){
		if(it.node != 0 && dom.parent(it) != NULL){
		  string parent_tag = dom.parent(it)->tagName();
		  transform(parent_tag.begin(), parent_tag.end(), parent_tag.begin(), ::tolower);
		  if(parent_tag == "script" || parent_tag == "noscript" || parent_tag== "style"){
		  	// cout<< "To aqui ..";
		      it.skip_children();
		      continue;
		  } else if(parent_tag == "title"){
		  	string title;
		  	string aux;
		  	aux = it->text();
		  	flag = 1;
		  	if (aux.length() > 2){
		  		remove_accents(aux);
		  		tokenizer tok{aux, sep};
				for (const auto &token : tok){
					// cout << "token: "<<token<<endl;
					title += token + " ";
					ColectionLinks[url].title = title;
				}
		  	}
		  }
		}
		if ((!it->isTag()) && (!it->isComment())){	
			s = it->text();
			remove_accents(s);
			tokenizer tok{s, sep};
			
			for (const auto &token : tok){
				// cout << "token: "<<token<<endl;
				insertToken(token);
			}
		} 
		// PEGAR ANCHOR, MAS NAO ADICIONAR LINK AO PAGERANK .. IDEIA INTERESSANTE ...
		else if (it->tagName() == "a"){	
			it->parseAttributes();
			// cout << url<<"---->" <<"	<a href="<< it->attribute("href").second<<">"<<endl;
			outlink = it->attribute("href").second;
			string domainOutlink = parse_url(outlink);
			string domainUrl = parse_url(url);
			if (ColectionLinks.find(outlink) != ColectionLinks.end()){
					// cout << "Entrei aqui ...";
				// inlinks[urlID].push_back(inlinkID);
				if (find(Graph.inlinks[ColectionLinks[outlink].id].begin(), Graph.inlinks[ColectionLinks[outlink].id].end(), ColectionLinks[url].id) == Graph.inlinks[ColectionLinks[outlink].id].end()){

				
					if (domainOutlink != "" && domainOutlink != domainUrl){
						Graph.insereInlink(ColectionLinks[url].id,ColectionLinks[outlink].id);
					}
					string anchor_text;
			            int children = it.number_of_children();
			            for(int i=0; i<children; i++){
			                it++;
			                if(it == dom.end()) return;
			                if(!it->isTag()) anchor_text += it->text();
			            }
			            tokenizer tok{anchor_text, sep};
			            
			            for (auto token: tok){
			            	remove_accents(token);
			            	int aux = insertToken(token);
			            	if (aux != 0){
			            		insertAnchorToken(token);
			            	}
			            	// cout << token<<" ";
		           		}
				}
			}
			// cout << it->text()<<"dentrodatag"<<endl;	
		}
	}
	if (ColectionLinks[url].title.size() < 3){
		ColectionLinks[url].title = url;
	}
}