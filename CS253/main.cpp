#include <WStem.h>
#include <PCwords.h>
#include <basic.h>
#include <Doc.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using std::map;
using std::cout;
using std::endl;
using std::string;
using std::vector;
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;
using std::stringstream;

#include <algorithm>
#include <iterator>
using std::iterator;
using std::sort;
using std::find;

using std::ofstream;

int main(int argc, char* argv[]){
	
	WStem w0;//Stemming stuff
	Basic b0;//basic stuff(printing, errors, counting)
	PCwords p0;//Punctuation and Capitalization
	
	if(argc != 5) return b0.Error0(argv[0]);//Incorrect number of arguments
	
	//Getting the reading level range of interest
	istringstream istr(argv[3]);
	double min;
	istr >> min;
	istringstream istr0(argv[4]);
	double max;
	istr0 >> max;
	if(min > max) return b0.Error8(argv[0]);
	
	vector<Doc> vDocs;//initialize vector to hold the documents
	vector<int> vNum;//Temporary vector to hold the frequency of words within a document
	
//Reading in the exceptions file===============================================================
	ifstream docFile(argv[2]);
	if(docFile.fail()) return b0.Error7(argv[0]);
	
	string filename;
	docFile>>filename;
	ifstream excepFile;
	excepFile.open(filename);
	if(excepFile.fail()) return b0.Error4(argv[0]);
	
	map<string, string> mRep;
	int x = 0;
	if(excepFile.is_open()){x = b0.ExcepRead(excepFile, argv[0], mRep);}
	if(x==-1){return -1;}
//Reading in the exceptions file===============================================================

//Reading in the first file=============================================================================
	ifstream file(argv[1]);
	if(file.fail()) return b0.Error1(argv[0]);
	
	string string0;
	file >> string0;
	if(file.fail()) return b0.Error2(argv[0], argv[1]);
	
	string name(argv[1]);
	Doc doc0(file, string0, name);
	vector<string> v0 = doc0.v0Acc();//Get the vector
		
	vector<string> vCap;
	p0.capCheck(v0, vCap);//Capitalization
	p0.ambCap(v0, vCap);
	
	int check = b0.Rlevel(v0, w0, doc0);
	if(check==-1){return b0.Error6(argv[0]);}
	w0.wStem(v0, mRep);//Stemming
	
	sort(v0.begin(), v0.end());//Sort the vector
			
	vNum = doc0.v1Acc();
	vector<string> v1;//Get the number of times the strings appear
	b0.Count(v0, v1, vNum);
	doc0.setv0(v1);
	doc0.setv1(vNum);
	
	vDocs.push_back(doc0);
//Reading in the first file=============================================================================

//Reading in the rest of the files======================================================================
	bool check0 = false;
	while(docFile >> filename){
		ifstream wordFile;
		wordFile.open(filename);
		if(wordFile.fail()) return b0.Error10(argv[0], filename);
		
		wordFile >> string0;
		if(wordFile.fail()) return b0.Error11(argv[0], filename);
		
		if(wordFile.is_open()){
			Doc d0(wordFile, string0, filename);//Read the file
			
			vector<string> v0 = d0.v0Acc();//Get the vector
			
			vector<string> vCap;
			p0.capCheck(v0, vCap);//Capitalization
			p0.ambCap(v0, vCap);
			
			int check = b0.Rlevel(v0, w0, d0);
			if(check==-1){return b0.Error6(argv[0]);}
			float CL = d0.cpCL();
			//Only stem and count documents if the CL score matches
			if(min < CL and CL < max){
				check0 = true;
				d0.setRL(true);
			}
			w0.wStem(v0, mRep);//Stemming
			
			sort(v0.begin(), v0.end());//Sort the vector
			
			vNum = d0.v1Acc();
			vector<string> v1;//Get the number of times the strings appear
			b0.Count(v0, v1, vNum);
			d0.setv0(v1);
			d0.setv1(vNum);
			d0.createm0();
			
			vDocs.push_back(d0);
			
			wordFile.close();
		}
	}
//Reading in the rest of the files======================================================================
	if(!check0) return b0.Error9(argv[0]);
	
	b0.TFIDF(vDocs, w0);
	
	//Find the Document with the most similarity to the input
	vDocs.at(0).computeSim(vDocs);
	
	return 0;//return 0 at the end
}




