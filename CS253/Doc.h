#ifndef DOC_H_INCLUDE
#define DOC_H_INCLUDE

#include <vector>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;

#include <fstream>
using std::ifstream;

class Doc{
public:
	//Constructor
	Doc(ifstream &wordFile, string &string0, string &filename);
	
	vector<string>& v0Acc();
	void setv0(vector<string> x);
	vector<int>& v1Acc();
	void setv1(vector<int> x);
	
	vector<long double>& TFIDFAcc();
	long double GetTFIDF(int index);
	
	string getName();
		//Get the name of a document(for errors)
	
	void setRL(bool x);
		//To know whether or not a document is within the reading level
	bool getRL();
		//Boolean access
	
	void createm0();
		//Create a map from the strings and the counts
	map<string, int>& getm0();
		//Accessing the map
	
	//Reading level computation
	int SetL(int numLetters, int numWords);
	int SetS(int numSent, int numWords);
	float cpCL();
	
	//TFIDF computation
	void computeTFIDF(int tf, long double IDF);
	long double IDF(double N, double n);
	void TFIDFpunct();
	
	string Getstring(int index);
	int Getnum(int index);
	
	//Similarity computation
	long double simWords(Doc doc2);
	void computeSim(vector<Doc> &vDocs);
	

private:
	vector<string> v0;//strings
	vector<int> v1;//counts
	map<string, int> m0;//strings and counts
	vector<long double> TFIDF;//Holds the TFIDF scores for each word in the document
	//floats hold the Reading level values
	float L;
	float S;
	float CL;
	string filename;//Name of file
	bool RL;//Boolean to check if this document is in the specified reading level
};

#endif
