#include <PCwords.h>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::cout;
using std::endl;

void PCwords::punSep(string string0, vector<string> &v0){
	//check the string for punctuation
	vector<string> vPush;//This will hold the edited strings, after the punctuation checks
	string string1 = "";//Temporary string variable to help with the editing
	int count = 0;

	string1 += string0.at(0);
	if(string0.size() == 1){//If the string is only one character long, skip all the extra stuff
		vPush.push_back(string1);
	}
	else{
		string1 = "";
		punSepWork(string0, string1, count,vPush);//vPush = someWork(string0, string1, count, vPush);
	}
	
	for(int i = 0; (unsigned)i != vPush.size(); i++){//Push the changed strings into v0
		v0.push_back(vPush[i]);
	}
}
void PCwords::punSepWork(const string &string0, string &string1, int count, vector<string> &vPush){
	while((unsigned)count!=string0.size()){
		if(punCheck(string0.at(count))){
			Punct(string0, string1, count, vPush);
			if((unsigned)count==string0.size()){return;}
		}
		else{
			Alphanum(string0, string1, count, vPush);
		}
	}
}
void PCwords::Punct(const string &string0, string &string1, int &count, vector<string> &vPush){
	while((unsigned)count!=string0.size() and punCheck(string0.at(count))){
		string1+=string0.at(count);
		count++;
	}
	if((unsigned)count!=string0.size() and isdigit(string0.at(count))){
		if(string1.size()==1 and string0.at(count-1)=='.'){
			Alphanum(string0, string1, count, vPush);
			return;
		}
	}
	vPush.push_back(string1);
	string1="";
	return;
}
void PCwords::Alphanum(const string &string0, string &string1, int &count, vector<string> &vPush){
	while((unsigned)count!=string0.size() and !punCheck(string0.at(count))){
		string1+=string0.at(count);
		count++;
	}
	if((unsigned)count!=string0.size() and string0.at(count)=='.'){
		bool x = periodWork(string0, string1, count);
		if(x){
			Alphanum(string0, string1, count, vPush);
			return;}
	}
	if((unsigned)count!=string0.size() and string0.at(count)==','){
		bool x = commaWork(string0, string1, count);
		if(x){
			Alphanum(string0, string1, count, vPush);
			return;}
	}
	vPush.push_back(string1);
	string1="";
	return;
}
bool PCwords::commaWork(const string &string0, string &string1, int &count){
	if((unsigned)count >= string0.size()-1){return false;}
	if(isdigit(string0.at(count-1)) and isdigit(string0.at(count+1))){
		string1+=string0.at(count);
		count++;
		return true;
	}
	else{return false;}
}
bool PCwords::periodWork(const string &string0, string &string1, int &count){
	if((unsigned)count >= string0.size()-1){return false;}
	if(isdigit(string0.at(count-1)) and isdigit(string0.at(count+1))){
		string1+=string0.at(count);
		count++;
		return true;
	}
	else if(isdigit(string0.at(count+1)) and string1==""){
		string1+=string0.at(count);
		count++;
		return true;
	}
	else{return false;}
}
bool PCwords::punCheck(char c){//Checking if a character is non-alphabetical, non-numerical, not "." or ","
	switch(c){
		case '~':
		case '`':
		case '!':
		case '@':
		case '#':
		case '$':
		case '%':
		case '^':
		case '&':
		case '*':
		case '(':
		case ')':
		case '_':
		case '-':
		case '+':
		case '=':
		case '\\':
		case '|':
		case '}':
		case ']':
		case '{':
		case '[':
		case '"':
		case ':':
		case ';':
		case '/':
		case '?':
		case '>':
		case '<':

		case '.'://Special cases
		case ',':
			return true;
			break;
		default:
			return false;
	}
}
//==============================================================================================================================



//Capitalization================================================================================================================
void PCwords::capCheck(vector<string> &v0, vector<string> &vCap){
	string string0 = v0.front();
	char c0 = string0[0];
	int check = 0;
	if(isupper(c0)){//check for capitalized alphabetical character
		if(!numCheck(v0.at(0))){//Check for no numeric character
			for(int i = 0; (unsigned)i < string0.size(); i++){//check for other capital letters, if it's an acronym
				c0 = string0[i];
				if(isupper(c0)){
					check++;
				}
			}
			if(check == 1){//do the insertion
				v0.front().insert(0,"+");
			}
		}
	}
	for(int i = 1; (unsigned)i < v0.size(); i++){
		string0 = v0.at(i);
		check = 0;
		if(isupper(string0[0])){//Check for uppercase first character
			if(v0.at(i-1).find('.')!= std::string::npos or 
				v0.at(i-1).find('!')!= std::string::npos or 
				v0.at(i-1).find('?')!= std::string::npos){//check for end of sentence character before
				if(!numCheck(string0) and !isNumString(v0.at(i-1))){//check for no number
					for(int j = 0; (unsigned) j < string0.size(); j++){
						c0 = string0[j];
						if(isupper(c0)){
							check++;
						}
					}
					if(check == 1){
						v0.at(i).insert(0,"+");
					}
				}
				else{vCap.push_back(v0.at(i));}
			}
			else{vCap.push_back(v0.at(i));}
		}
	}
}
bool PCwords::numCheck(string string0){
	if(string0.find('0') != string::npos or string0.find('1') != string::npos or
		string0.find('2') != string::npos or string0.find('3') != string::npos or
		string0.find('4') != string::npos or string0.find('5') != string::npos or
		string0.find('6') != string::npos or string0.find('7') != string::npos or
		string0.find('8') != string::npos or string0.find('9') != string::npos){return true;}
	else{return false;}
}
bool PCwords::isNumString(string string0){
	if(numCheck(string0) and string0.find('.') != string::npos){return true;}
	else{return false;}
}


bool PCwords::isCap(string string1, vector<string> &vCap){
	for(int i = 0; (unsigned)i != vCap.size(); ++i){
		if(string1 == vCap.at(i)){
			return true;
			vCap.erase(vCap.begin()+i-1);
		}
	}
	return false;
}
void PCwords::ambCap(vector<string> &v0, vector<string> &vCap){
	string string1 = "";
	for(int i=0; (unsigned)i!=v0.size(); ++i){
		if(v0.at(i).size()!=1 and v0.at(i).front()=='+' and isupper(v0.at(i).at(1))){
			string1 = v0.at(i).substr(1);
			if(isCap(string1, vCap)){v0.at(i).erase(0,1);}
			else{
				v0.at(i).erase(0,1);
				char c = v0.at(i).front();
				v0.at(i).front() = tolower(c);
			}
		}
	}
}
