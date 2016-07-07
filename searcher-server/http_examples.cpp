#include "server_http.hpp"
#include "client_http.hpp"

#include <fstream>
#include <limits>
#include <iostream>
#include "searcher/utils/loaders.h"
#include "searcher/utils/searcher.h"
#include "searcher/models/vector_spacemodel.h"
#include <boost/algorithm/string.hpp>

//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


//Added for the default_resource example
#include <fstream>
#include <boost/filesystem.hpp>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

#include <fstream>
#include <limits>
#include <iostream>

















using namespace std;
using namespace boost::property_tree;


typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;

bool comparefinalscore(const result &a, const result &b) {
    return a.score > b.score;
}


Loaders loader;
Searcher s;


int main() {

    HttpServer server(8080, 1);


    


    server.default_resource["GET"]=[&server](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request) {
        const auto web_root_path=boost::filesystem::canonical("web");
        boost::filesystem::path path=web_root_path;
        path =request->path;


        string caminho = path.string();

        string model = caminho.substr(1,1);
        string query = caminho.substr(3);



        // declaração das variaveis
        vector<result> Hits;
        vector<result> Hits2;
        result tempresult;
        vector<result> results;
        unordered_map <int,float> resultHash;

        vector<string> query_terms;
        query_terms = s.getQuery(query);


        cout <<"\nquery: " << query << endl; 

        Vector_SpaceModel vectormodel(&loader);

        if (model == "1"){
        
            Hits = vectormodel.search(query_terms);

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
            Hits = results;
        }else if(model == "2"){
            Hits = vectormodel.search(query_terms);
            for (int i= 0;i<int(Hits.size()); i++){
                // cout << loader.getdocPR(Hits[i].doc)<<endl;
                Hits[i].score += loader.getdocPR(Hits[i].doc);
            }
            sort(Hits.begin(),Hits.end(),comparefinalscore);
        } else {
            cout << "requisição desconsiderada!\n";
        }

        if (Hits.size() >5){
           Hits.resize(5);
        }


        //realize a busca aki


        stringstream saida;

        saida << "{\"results\": [ ";

        int i = 1;
        for (auto doc:Hits){

            string textdescription = "no text description";
            saida << "{\"title\": \"" << loader.getdocurl(doc.doc) << "\", \"url\": \""<< loader.getdocurl(doc.doc)<<"\",\"snippet\": \""<< textdescription << "\"}";
            
            if (i<5) { saida << ",\n"; }
            ++i;
        }

         saida << "\n]\n}";

        //saida << "{ \"query\": \"" << "query" << "\", \"tipo\": \"" << tipo << "\" }\n";
        //saida << "{\"results\": [ {\"title\": \""<< query << " "<< model << "\",\"url\": \"/lucas\",\"snippet\": \"esse texto de snipet é um exemplo de teste a ser verificado\"}\n]\n}";


        string textsaida = saida.str();
        cout <<  "Houve uma requisição\n";
        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << textsaida.length() << "\r\n\r\n" << textsaida;    
        return;
        
    };
    
    thread server_thread([&server](){
        //Start server
        server.start();
    });
    
    cout << "running..."<<endl;
   
    server_thread.join();
    
    return 0;
}

