#include "mapper.h"

struct truplas{
	int termId;
	int doc_id;
	int freq;
};
struct truplaFromFile{
	int termId;
	int doc_id;
	int freq;
	int fileid;
};

class Indexer
{
private:
	int outFileNumber;
	vector<truplaFromFile> truplaQueue;
public:

	Indexer(){
	}
	Mapper mapper;
	// void WriteToFile(int outFileNumber);
	void OrdExternaAnchor(int filesRuns);
	void OrdExterna(int filesRuns);
	void printTokensHash();
	truplaFromFile MyHeapPop();
	void MyHeapPush(truplaFromFile truplas);
};