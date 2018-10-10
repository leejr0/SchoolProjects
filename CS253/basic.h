#ifndef BASIC_H_INCLUDE
#define BASIC_H_INCLUDE

#include <Doc.h>
#include <WStem.h>
#include <vector>
#include <string>
#include <map>
using std::map;
using std::string;
using std::vector;

#include <iostream>
#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;

class Basic {
public:
	
	//Error cases
	int Error0(char* arg0);//Number of input files
	int Error1(char* arg0);//Text file failed to open
	int Error2(char* arg0, char* arg1);//Empty file
	int Error3(char* arg0);//Reading file failure
	int Error4(char* arg0);//Exception file failed to open
	int Error5(char* arg0);//Incorrect exception file format
	int Error6(char* arg0);//Division by zero
	int Error7(char* arg0);//File of documents failed
	int Error8(char* arg0);//Min is greater than max
	int Error9(char* arg0);//No Document in reading level range
	int Error10(char* arg0, string filename);//Document is not found in Docfile
	int Error11(char* arg0, string filename);//Document is empty
	
	//Exception file
	int ExcepRead(ifstream &excepFile, char* arg0, map<string, string> &mRep);
	int stringSep(string temp, string &string0, string &string1, char* arg0);

	int wordCount(const string &string0, vector<Doc> &vDocs);
		//Count how many documents a word appears in
	void TFIDF(vector<Doc> &vDocs, WStem &w0);
		//Compute the TFIDF scores of all documents
	int newwordCount(const string &string0, vector<Doc> &vDocs);
		//See if we can speed up the TFIDF process: not faster
	
	//Vector work
	void Count(vector<string> &v0, vector<string> &v1, vector<int> &vNum);
		//Count the number of each individual string that appears in a document
	void print(vector<string> &v0, vector<int> v1);
		//Print the document and string counts
	
	//Reading level work
	int Rlevel(vector<string> v0, WStem &w0, Doc &d0);
	
private:
	map<string, int> wordCounts;//Holds the number of documents each word appears in
};

#endif
