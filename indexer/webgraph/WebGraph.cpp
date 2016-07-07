#include "../include/WebGraph.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>


void WebGraph::teste(){
	cout << "Funcionei!";
};

void WebGraph::insereInlink(int inlinkID, int urlID){
	inlinks[urlID].push_back(inlinkID);
	numoutlinks[inlinkID] +=1;
	pageRank[inlinkID] = 1.0f;
	pageRank[urlID] = 1.0f;


};

void WebGraph::printPageRank(){
    ofstream pagerankfile;
    pagerankfile.open("searchfiles/pagerank.txt");
    for (auto it:pageRank){
        pagerankfile <<it.first<<"\t"<<it.second<<endl;
    }
    pagerankfile.close();
};


void WebGraph::printWebGraph(){
	for (auto it:inlinks){
		cout << "Pagina: "<<it.first<<endl;
		cout << "Outbound:" << numoutlinks[it.first]<<endl;	
		for (auto it2:inlinks[it.first]){
			cout <<"Inlinks: "<<it2 << endl;
		}
		cout << "\n\n";
	}
};


void WebGraph::pagerank(int iterations){
    float d = 0.7;
    int i = 0;
    unordered_map<int,float> pageRank2 = pageRank; 

    while (i++ < iterations){
        // current_gama = 0;
        // cout << i<<" iteracao.."<<endl;
        for (auto it:inlinks){
            float rank = 0.0f;
            for (auto it2:inlinks[it.first]){
                rank += pageRank[it2]/numoutlinks[it2];
            }
            rank = 1.0f -d + d*rank;
            pageRank[it.first] = rank;
            // cout << "Doc:"<<it.first<<" pagerank:"<<pageRank[it.first]<<endl;
        }
    }
    // while ( i++ < iterations && current_gama > 0.00001f) {
    //     current_gama = 0;
        
    //     for (auto node = 0; node < size_ ;++node) {
            
    //         float rank = 0.0f;
            
    //         for (auto ip : get_inlinks(node)) {
                
    //             rank += (*opagerank)[ip]/get_outlink_count(ip);
    //         }
    //         rank = 1.0f -d + d*rank;
            
    //         (*npagerank)[node] = rank;
            
            
    //     }
    //     for (int i = 0; i < size_ ; ++i) {
    //         float diff = abs((*npagerank)[i] - (*opagerank)[i]);
    //         current_gama = diff > current_gama ? diff : current_gama;
           
    //     }
    //     cout << current_gama << endl;

    //     for (int i = 0; i < size_ ; ++i) {
    //         (*opagerank)[i] =  (*npagerank)[i];
            
    //     }
        
    // }
    // delete npagerank;
    // cout << "n iterations " << i << endl;
    // return opagerank;
}