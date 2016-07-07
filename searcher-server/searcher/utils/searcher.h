#ifndef SEARCHER_H
#define SEARCHER_H


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

class Searcher
{
private:
	string query;
	vector<string> queryvect;
public:
	vector<string> getQuery(string userQuery);
	void remove_accents(string &str);
	int getQuerySize(vector<string> words);
	string getsearchType();
};




#endif