#include <basic.h>
#include <Doc.h>
#include <WStem.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using std::string;
using std::vector;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::getline;

//Error cases=================================================================================================
int Basic::Error0(char* arg0){
	std::cerr << "Error: " << arg0 << " Incorrect number of input files" << endl;
	return -1;
}
int Basic::Error1(char* arg0){
	std::cerr << "Error: " << arg0 << " First text file failed to open" << endl;
	return -1;
}
int Basic::Error2(char* arg0, char* arg1){
	std::cerr << "Error: " << arg0 << " Document '" << arg1 << "' is empty" << endl;
	return -1;
}
int Basic::Error3(char* arg0){
	std::cerr << "Error: " << arg0 << " Failed to read next word" << endl;
	return -1;
}
int Basic::Error4(char* arg0){
	std::cerr << "Error: " << arg0 << " Exception file failed to open" << endl;
	return -1;
}
int Basic::Error5(char* arg0){
	std::cerr << "Error: " << arg0 << " Incorrect format in exception file" << endl;
	return -1;
}
int Basic::Error6(char* arg0){
	std::cerr << "Error: " << arg0 << " Division by zero" << endl;
	return -1;
}
int Basic::Error7(char* arg0){
	std::cerr << "Error: " << arg0 << " File of documents failed to open" << endl;
	return -1;
}
int Basic::Error8(char* arg0){
	std::cerr << "Error: " << arg0 << " Reading level range empty" << endl;
	return -1;
}
int Basic::Error9(char* arg0){
	std::cerr << "Error: " << arg0 << " No document in reading level range" << endl;
	return -1;
}
int Basic::Error10(char* arg0, string filename){
	std::cerr << "Error: " << arg0 << " Document '" << filename << "' not found in 2nd input file" << endl;
	return -1;
}
int Basic::Error11(char* arg0, string filename){
	std::cerr << "Error: " << arg0 << " Document '" << filename << "' is empty" << endl;
	return -1;
}
//============================================================================================================


//Read in the exceptions======================================================================================
int Basic::ExcepRead(ifstream &excepFile, char* arg0, map<string, string> &mRep){
	string string0 = "";
	string string1 = "";
	string temp = "";
	getline(excepFile, temp);
	if(excepFile.fail()){return 0;}
	
	int x = stringSep(temp, string0, string1, arg0);
	if(x==-1){return -1;}
	mRep.insert(std::pair<string, string>(string0, string1));
	
	while(!excepFile.eof()){
		string0 ="";
		string1 ="";
		getline(excepFile, temp);
		if(temp=="" and excepFile.eof()){return 0;}
		x = stringSep(temp, string0, string1, arg0);
		if(x==-1){return -1;}
		if(temp!=""){
			mRep.insert(std::pair<string, string>(string0, string1));
		}
	}
	return 0;
}
int Basic::stringSep(string temp, string &string0, string &string1, char* arg0){
	if(temp==""){return 0;}	
	int i = 0;
	while((unsigned)i!=temp.size() and !isspace(temp.at(i))){
		string0.push_back(temp.at(i));
		i++;
	}
	
	if((unsigned)i==temp.size()){return Error5(arg0);}
	if(isspace(temp.at(i))){i++;}
	
	while((unsigned)i!=temp.size() and !isspace(temp.at(i))){
		string1.push_back(temp.at(i));
		i++;
	}
	
	if((unsigned)i!=temp.size()){return Error5(arg0);
	}
	if(string0=="" or string1==""){return Error5(arg0);}
	return 0;
}
//======================================================================================================


//Counting the strings in the vector====================================================================
void Basic::Count(vector<string> &v0, vector<string> &v1, vector<int> &vNum){
	//Delete the extra individual strings in v0 and note the number of individual strings
	string string0;
	int count = 0;
	
	for (auto it = v0.begin(); it != v0.end(); /*it++*/){
		string0 = *it;
		count = 0;
		v1.push_back(string0);
		while(string0 == *it){
			count++;
			it++;
		}
		vNum.push_back(count);
	}
}
//======================================================================================================


//PA7 word Counting=============================================================================================
int Basic::wordCount(const string &string0, vector<Doc> &vDocs){
	//This counts how many documents a certain word appears in
	//No need to count a word twice
	if(wordCounts.count(string0)!=0){return wordCounts[string0];}
	
	vector<string> v0;
	int count = 0;
	for(int i=0; (unsigned)i!=vDocs.size(); ++i){
		v0 = vDocs.at(i).v0Acc();
		if(std::find(v0.begin(), v0.end(), string0)!=v0.end()){
			count++;
		}
	}
	wordCounts[string0]=count;
	return count;
}
//===========================================================================================================


//PA6 TFIDF==================================================================================================
void Basic::TFIDF(vector<Doc> &vDocs, WStem &w0){
	double N = vDocs.size();
	double n = 0;
	int tf;
	long double idf = 0;
	string string0;
	vector<string> v0;
	//Computing the TFIDFs for all documents
	for(int i=0; (unsigned)i!=vDocs.size();++i){
		v0 = vDocs.at(i).v0Acc();
		for(int j=0; (unsigned)j!=v0.size();++j){
			string0 = vDocs.at(i).Getstring(j);
			if(w0.isPunctString(string0)){
				vDocs.at(i).TFIDFpunct();
			}//If a punctuation string, skip all this
			//Might have to do something with punctuation strings, but I need to push something
				//for the TFIDF score, to not mess up the order
			else{
				n = wordCount(string0, vDocs);//Compute idf
				idf = vDocs.at(i).IDF(N, n);
			
				tf = vDocs.at(i).Getnum(j);//Get the number of times the string appears
			
				vDocs.at(i).computeTFIDF(tf, idf);
			}
		}
	}//Maps, or sets, etc.->Data structure changes will make things faster
}//Growing size makes vector double in size if limit is reached
//===========================================================================================================
//TFIDF with maps
int Basic::newwordCount(const string &string0, vector<Doc> &vDocs){
	//This counts how many documents a certain word appears in
	if(wordCounts.count(string0)!=0){return wordCounts[string0];}
	
	map<string, int> m0;
	int count = 0;
	for(int i=0; (unsigned)i!=vDocs.size(); ++i){
		m0 = vDocs.at(i).getm0();
		if(m0.count(string0)!=0){
			count++;
		}
	}
	wordCounts[string0]=count;
	return count;
}
//===========================================================================================================


//Reading Level Work=========================================================================================
int Basic::Rlevel(vector<string> v0, WStem &w0, Doc &d0){
	int numWords = 0;
	int numLetters = 0;
	int numSent = 0;
	for(int i=0; (unsigned)i!=v0.size();++i){
		if(!w0.isPunctString(v0.at(i))){
			if(v0.at(i).at(0)=='+'){numLetters += v0.at(i).size()-1;}
			else{numLetters += v0.at(i).size();}
			numWords++;
		}
		else{
			if(v0.at(i).find('.')!= std::string::npos or 
				v0.at(i).find('!')!= std::string::npos or 
				v0.at(i).find('?')!= std::string::npos){numSent++;}
			}
	}
	int check = 0;
	check = d0.SetL(numLetters, numWords);
	if(check==-1){return check;}
	check = d0.SetS(numSent, numWords);
	return check;
}
//===========================================================================================================


//Print the vector===========================================================================================
void Basic::print(vector<string> &v0, vector<int> v1){

	for(int i = 0; (unsigned)i < v0.size(); i++){
		std::cout << v0.at(i) << " " << v1[i] << endl;
	}
}





