#include <fstream>
#include <limits>
#include <iostream>
#include "utils/loaders.h"
#include "utils/searcher.h"
#include "models/vector_spacemodel.h"
#include <boost/algorithm/string.hpp>

#include "server_http.cpp"
//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

//Added for the default_resource example
#include <boost/filesystem.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;
//Added for the json-example:
using namespace boost::property_tree;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

bool comparefinalscore(const result &a, const result &b) {
    return a.score > b.score;
}





int maiwren(int argc, char** argv) {

	Loaders loader;
	Searcher search;
	vector<result> Hits;
	vector<result> Hits2;
	result tempresult;
	vector<result> results;
	unordered_map <int,float> resultHash;

	vector<string> query_terms;
	
	string model = search.getsearchType();
	query_terms = search.getQuery();
	Vector_SpaceModel vectormodel(&loader);

	if (model == "1"){
		
		Hits = vectormodel.search(query_terms);
		Hits.resize(10);
		for (auto doc:Hits){
    		cout << loader.getdocurl(doc.doc)<<"	Score:"<<doc.score<<endl;
    	}
		// cout << "Ate aqui tudo certo .."<<endl;
	} else if(model == "3"){
		
		Hits = vectormodel.search(query_terms);
		Hits2 = vectormodel.searchAnchor(query_terms);
		for (auto it:Hits){
			resultHash[it.doc] = it.score;
		}
		for (auto it:Hits2){
			if (resultHash.find(it.doc) == resultHash.end()){
				resultHash[it.doc] = it.score;	
			}else{
				resultHash[it.doc] += it.score;
			}
		}
		for (auto it:resultHash){
	        tempresult.doc = it.first;
	        tempresult.score = it.second;
	        results.push_back(tempresult);
		}
		sort(results.begin(),results.end(),comparefinalscore);
		if (results.size()>5){
        	results.resize(5);        
    	}
    	for (auto doc:results){
    		cout << loader.getdocurl(doc.doc)<<"	Score:"<<doc.score<<endl;
    	}
	}else if(model == "2"){
		Hits = vectormodel.search(query_terms);
		for (int i= 0;i<Hits.size(); i++){
			// cout << loader.getdocPR(Hits[i].doc)<<endl;
    		Hits[i].score += loader.getdocPR(Hits[i].doc);
    	}
    	sort(Hits.begin(),Hits.end(),comparefinalscore);
    	if (Hits.size() >5){
        	Hits.resize(5);
    	}
    	for (auto doc:Hits){
    		cout << loader.getdocurl(doc.doc)<<"	Score:"<<doc.score<<endl;
    	}
	}
}