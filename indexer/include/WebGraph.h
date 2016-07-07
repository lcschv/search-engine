#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <istream>
#include <sstream>
#include <fstream>

using namespace std;


class WebGraph {
    private:
        
    public:
    	unordered_map <int, vector<int>> inlinks; // Hash que reserva inlinks de cada uma das urls da colecao;
        unordered_map <int, int> numoutlinks;
        unordered_map <int,float> pageRank;
    void teste();
    void insereInlink(int inlinkID, int urlID);
    void printWebGraph();
    void pagerank(int iterations);
    void printPageRank();
};
