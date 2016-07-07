#include "vector_spacemodel.h"
#include <math.h>
#include <vector>

Vector_SpaceModel::Vector_SpaceModel(Loaders* loader){
    this->loader = loader;
};

bool compareByScore(const result &a, const result &b)
{
    return a.score > b.score;
}

vector<result> Vector_SpaceModel::search(vector<string> query_terms){
    vector<TermDocTF> docsTf;
    unordered_map<int,float> accumulators;
    for(auto token:query_terms){
        string t = token;
        int termfrequency = 0;
        if (loader->gettokenId(t) != -1){
            docsTf = loader->getvectorofdocs(loader->gettokenId(t), loader->gettokenPos(t));
            termfrequency = docsTf.size();
            float term_weight = 1 + log(1491/termfrequency);
            for (auto it:docsTf){
                if (accumulators.find(it.doc_id) == accumulators.end()){
                    accumulators[it.doc_id] = 0;
                }
                accumulators[it.doc_id] += log(1 + it.TF)*term_weight;
            }
        }
        docsTf.clear();
    }
    for (auto it:accumulators){
        int doclen = loader->getdocLen(it.first);
        if (doclen > 0) {
            accumulators[it.first] /= sqrt(doclen);
        }
    }
    vector<result> resultvect;
    for (auto item: accumulators){
        result tempresult;
        tempresult.doc = item.first;
        tempresult.score = item.second;
        resultvect.push_back(tempresult);
    }
    
    sort(resultvect.begin(),resultvect.end(),compareByScore);

    if (resultvect.size()>100){
        resultvect.resize(100);        
    }

    accumulators = {};
    return resultvect;
}


vector<result> Vector_SpaceModel::searchAnchor(vector<string> query_terms){
    vector<TermDocTF> docsTf;
    unordered_map<int,float> accumulators;
    for(auto token:query_terms){
        string t = token;
        // cout << "token:"<<loader->gettokenIdAnchor(t)<<endl;
        int termfrequency = 0;
        if (loader->gettokenIdAnchor(t) != -1){
            docsTf = loader->getvectorofdocsAnchor(loader->gettokenIdAnchor(t), loader->getAnchortokenPos(t));
            termfrequency = docsTf.size();
            // cout <<"Tamanho vetor:" <<termfrequency<<endl;
            float term_weight = 1 + log(1491/termfrequency);
            for (auto it:docsTf){
                if (accumulators.find(it.doc_id) == accumulators.end()){
                    accumulators[it.doc_id] = 0;
                }
                accumulators[it.doc_id] += log(1 + it.TF)*term_weight;
            }
        }
        docsTf.clear();
    }
    // cout << "print passei aqui .."<<endl;
    for (auto it:accumulators){
        int doclen = loader->getdocLen(it.first);
        if (doclen > 0) {
            accumulators[it.first] /= sqrt(doclen);
        }
    }
    vector<result> resultvect;
    for (auto item: accumulators){
        result tempresult;
        tempresult.doc = item.first;
        tempresult.score = item.second;
        resultvect.push_back(tempresult);
    }
    
    sort(resultvect.begin(),resultvect.end(),compareByScore);
    if (resultvect.size()>100){
        resultvect.resize(100);        
    }
    
    accumulators = {};
    return resultvect;
}