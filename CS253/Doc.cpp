#include <Doc.h>
#include <WStem.h>
#include <PCwords.h>
//#include <basic.h>

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ofstream;

#include <vector>
#include <string>
using std::string;
using std::vector;
using std::cout;
using std::endl;
#include <algorithm>

#include <math.h>

//Constructor========================================================================================
Doc::Doc(ifstream &wordFile, string &string0, string &filename):filename(filename){//Reading in documents
	PCwords p0;
	if(wordFile.is_open()){	
		p0.punSep(string0, v0);
		while(wordFile >> string0){//Put the strings into a single vector
			p0.punSep(string0, v0);
		}
	}
	wordFile.close();
	RL = false;
}
//===================================================================================================


//Replacement and Access=============================================================================
vector<string>& Doc::v0Acc(){//Returns the vector of strings
	return v0;
}
void Doc::setv0(vector<string> x){//Resets v0
	v0 = x;
}
vector<int>& Doc::v1Acc(){//Returns the vector of numbers that associate with the strings
	return v1;
}
void Doc::setv1(vector<int> x){//Resets v1
	v1 = x;
}

string Doc::Getstring(int index){//Returns a string at a given index in v0
	return v0[index];
}
int Doc::Getnum(int index){//Returns the integer at a given index in v1
	return v1[index];
}

vector<long double>& Doc::TFIDFAcc(){//Returns TFIDF vector
	return TFIDF;
}
long double Doc::GetTFIDF(int index){//Returns TFIDF score at an index
	return TFIDF[index];
}

string Doc::getName(){
	return filename;
}
void Doc::setRL(bool x){
	RL = x;
}
bool Doc::getRL(){
	return RL;
}
//===================================================================================================


//New Efficiency=====================================================================================
void Doc::createm0(){
	for(int i = 0; (unsigned) i != v0.size(); ++i){
		m0[v0[i]] = v1[i];
	}
}
map<string, int>& Doc::getm0(){
	return m0;
}
//===================================================================================================


//Computing the CL(doc)==============================================================================
int Doc::SetL(int numLetters, int numWords){
	if(numWords==0){return -1;}
	L = 0.0;
	L = (float)numLetters / numWords;
	L = L * 100;
	return 0;
}

int Doc::SetS(int numSent, int numWords){
	if(numWords==0){return -1;}
	S = 0.0;
	S = (float)numSent / numWords;
	S = S * 100;
	return 0;
}
//Compute and print CL(doc)
float Doc::cpCL(){
	CL = (0.0588*L) - (0.296*S) - 15.8;
	return CL;
}
//===================================================================================================


//Computing TFIDF====================================================================================
void Doc::computeTFIDF(int tf, long double IDF){//Computes TFIDF and pushes it into a vector
	long double answer = tf*IDF;
	TFIDF.push_back(answer);
}
long double Doc::IDF(double N, double n){//Computes IDF
	long double answer = log10(N/n);
	return answer;
}
void Doc::TFIDFpunct(){
	TFIDF.push_back(0);
}
//====================================================================================================


//Similarity Computation===============================================================================
long double Doc::simWords(Doc doc2){//Similarity work
	
	vector<string> temp = doc2.v0Acc();
	vector<string> answer;
	long double Sim = 0.0;
	long double mult = 0.0;
	for(int i=0; (unsigned)i!=v0.size();++i){
		if(std::find(temp.begin(), temp.end(), v0.at(i))!=temp.end()){
			int j = int(std::find(temp.begin(), temp.end(), v0.at(i))-temp.begin());
			mult = TFIDF.at(i)*doc2.GetTFIDF(j);
			Sim = mult + Sim;
		}
	}
	return Sim;
}
void Doc::computeSim(vector<Doc> &vDocs){//Computing the similarity between Documents
	long double Sim = -1.0;
	long double temp = 0.0;
	string name = "foo";
	for(int i=1; (unsigned)i!=vDocs.size(); ++i){
		temp = simWords(vDocs.at(i));
		if(temp > Sim and vDocs.at(i).getRL()==true){
			Sim = temp;
			name = vDocs.at(i).getName();
		}
	}
	std::cout<<name<<endl;
}
//=====================================================================================================




