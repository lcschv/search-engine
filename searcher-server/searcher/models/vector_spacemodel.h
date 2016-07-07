#ifndef VECTOR_SPACEMODEL_H
#define VECTOR_SPACEMODEL_H


#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "../utils/loaders.h"
#include <boost/algorithm/string.hpp>

using namespace std;

struct result
{
	int doc;
	float score;
};


class Vector_SpaceModel{
private:
	Loaders* loader;
	vector<result> HITs;
public:
	Vector_SpaceModel(Loaders* loader);
	vector<result> search(vector<string> query_terms);
	vector<result> searchAnchor(vector<string> query_terms);
};



#endif