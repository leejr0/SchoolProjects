#include <WStem.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using std::map;
using std::string;
using std::vector;
using std::cout;
using std::endl;

//Rules=========================================================================================
bool WStem::isVowel(const string string0, const char c, const int i){
	if(c=='a' or c=='e' or c=='i' or c=='o' or c=='u'){return true;}
	
	else if(c=='y'){
		if(i==0){return false;}
		else if(isVowel(string0, string0.at(i-1), i-1)){return false;}
		else{return true;}
	}
	else{return false;}
}
bool WStem::isDouble(const string string0){
	char c0 = string0.back();
	char c1 = string0.front();
	if((c0=='b' and c1=='b') or (c0=='d' and c1=='d') or (c0=='f' and c1=='f') or
		(c0=='g' and c1=='g') or (c0=='m' and c1=='m') or
		(c0=='n' and c1=='n') or (c0=='p' and c1=='p') or
		(c0=='r' and c1=='r') or (c0=='t' and c1=='t')){return true;}
	else{return false;}
}
bool WStem::liEnding(const string string0){
	if(string0.at(string0.size()-3)=='c' or string0.at(string0.size()-3)=='d' or
		string0.at(string0.size()-3)=='e' or string0.at(string0.size()-3)=='g' or
		string0.at(string0.size()-3)=='h' or string0.at(string0.size()-3)=='k' or
		string0.at(string0.size()-3)=='m' or string0.at(string0.size()-3)=='n' or
		string0.at(string0.size()-3)=='r' or string0.at(string0.size()-3)=='t')
			{return true;}
	else{return false;}
}
string WStem::Region1(const string string0){
	string string1 = "";
	for(int i = 0; (unsigned)i != string0.size(); ++i){
		if(!isVowel(string0, string0.at(i), i) and i!=0){
			if(isVowel(string0, string0.at(i-1), i-1)){
				string1 = string0.substr(i+1);
				break;
			}
		}
	}
	return string1;
}
string WStem::Region2(const string R1){
	if(R1.front()!='y'){
		return Region1(R1);
	}
	else{
		string answer = "";
		for(int i = 1; (unsigned)i!=R1.size(); i++){
			if(!isVowel(R1, R1.at(i), i)){
				answer = R1.substr(i+1);
				break;
			}
		}
		return answer;
	}
}
bool WStem::ShortSyll(const string string0){
	if(string0.size()==2){
		if(isVowel(string0, string0.front(), 0) and
			!isVowel(string0, string0.back(), 1)){return true;}
	}
	else if(!isVowel(string0, *(string0.end()-3), string0.size()-3) and 
		isVowel(string0, *(string0.end()-2), string0.size()-2) and 
		!isVowel(string0, string0.back(), string0.size()-1)){
		if(string0.back()=='w' or string0.back()=='x' or string0.back()=='y'){
			return false;}
		else{return true;}
	}
	return false;
}
bool WStem::isShort(const string string0){
	string R1 = Region1(string0);
	if(!R1.empty()){return false;}
	else{
		if(ShortSyll(string0)){return true;}
		else{return false;}
	}
}
bool WStem::hasDigitUpper(const string string0){
	for(int i = 0; (unsigned)i != string0.size(); ++i){
		if(isupper(string0.at(i)) or isdigit(string0.at(i))){return true;}
	}
	return false;
}
bool WStem::findSuffix(const string string0, const string check){
	if(string0=="" or check==""){return false;}
	if(string0==check){return false;}//{return true;}
	if(string0.size() < check.size()){return false;} 
	int count = string0.size()-1;
	for(int i=check.size()-1; i >= 0; i=i-1){
		if(string0.at(count)!=check.at(i)){return false;}
		count=count-1;
	}
	return true;
}
void WStem::delWork(string &string0, string &erase){//deletes based on length of string erase
	while(erase != ""){//does not specifically delete certain suffixes
		if(string0==""){break;}
		string0.pop_back();
		erase.pop_back();
	}
}
bool WStem::containsVowel(const string string0){
	for(int i = 0; (unsigned)i!=string0.size(); ++i){
		if(isVowel(string0, string0.at(i), i)){return true;}
	}
	return false;
}
//================================================================================================


//Replacement stuff(PA5)==========================================================================
bool WStem::correctionCheck(string &string0, const map<string, string> &mRep){
	
	if(mRep.find(string0)!=mRep.end()){
		string0 = mRep.at(string0);
		return true;
	}
	return false;
}
bool WStem::isPunctString(const string string0){
	for(int i=0; (unsigned)i!=string0.size(); ++i){
		if(isalnum(string0.at(i)) or string0.at(i)=='\''){return false;}
	}
	return true;
}
//================================================================================================


//Actual work stuff===============================================================================
void WStem::wStem(vector<string> &v0, const map<string, string> &mRep){
	string string0 = "";
	for(auto it = v0.begin(); it != v0.end(); it++){
		wStemWork(*it, mRep);
	}
}
void WStem::wStemWork(string &string0, const map<string, string> &mRep){
	if(string0.size() <= 2){return;}//character is 2 chars long, return/do nothing
	if(string0.at(0) == '+'){return;}//Don't edit '+' words
	if(hasDigitUpper(string0)){return;}//If word has digit or uppercase, return
	if(isPunctString(string0)){return;}
	
	bool Ccheck = correctionCheck(string0, mRep);
	if(Ccheck==true){return;}

	Step1(string0);
	Step2(string0);
	string R1 = Region1(string0);
	Step3(string0, R1);
	Step4(string0);
	Step5(string0);
	R1 = Region1(string0);//Update R1 after the change
	Step6(string0, R1);
	R1 = Region1(string0);
	Step7(string0, R1);
	R1 = Region1(string0);
	Step8(string0, R1);
}
//=================================================================================


//STEP 1===========================================================================
void WStem::Step1(string &string0){
	if(string0.front() == '\''){string0.erase(0,1);}
	//Erase if first char is '
	if(findSuffix(string0, "'s'")){
		string0.pop_back();
		string0.pop_back();
		string0.pop_back();
	}
	else if(findSuffix(string0, "'s")){
		string0.pop_back();
		string0.pop_back();
	}
	else if(string0.back()=='\''){string0.pop_back();}
}
//==================================================================================


//STEP 2============================================================================
void WStem::Step2(string &string0){
	if(findSuffix(string0, "sses")){//sses
		string0.pop_back();
		string0.pop_back();
	}
	else if(findSuffix(string0, "ies") or findSuffix(string0, "ied")){
		if(string0.size() > 4){
			string0.pop_back();
			string0.pop_back();
		}
		else{string0.pop_back();}
	}
	else if(string0.back() == 's' and *(string0.end()-2) == 's'){}
	else if(string0.back() == 's' and *(string0.end()-2) == 'u'){}
	else if(string0.back() == 's'){Swork(string0);}
}
void WStem::Swork(string &string0){
	for(int i = 0; (unsigned)i != string0.size(); ++i){
		if(isVowel(string0,string0.at(i),i) and (unsigned)i!=string0.size()-2){
			string0.pop_back();
			break;
		}
	}
}
//==================================================================================


//STEP 3=============================================================================
void WStem::Step3(string &string0, const string R1){
	if(findSuffix(string0, "eed")){
		if(findSuffix(R1, "eed") or R1=="eed"){string0.pop_back();}
	}
	else if(findSuffix(string0, "eedly")){
		if(findSuffix(R1, "eedly") or R1=="eedly"){
			string0.pop_back();//eedly
			string0.pop_back();
			string0.pop_back();
		}
	}
	else{Step3extra(string0);}
	
}	
void WStem::Step3extra(string &string0){
	string temp;
	if(findSuffix(string0, "ed")){//ed
		temp = string0.substr(0, string0.size()-2);
		if(containsVowel(temp)){
			string0.pop_back();
			string0.pop_back();
			Step3Rep(string0);//Check for replacements
		}
	}
	else if(findSuffix(string0, "edly")){//edly
		temp = string0.substr(0, string0.size()-4);
		if(containsVowel(temp)){
			string erase = "edly";
			delWork(string0, erase);
			Step3Rep(string0);//Check for replacements
		}
	}
	else if(findSuffix(string0, "ing")){
		temp = string0.substr(0, string0.size()-3);//ing
		if(containsVowel(temp)){
			string erase = "ing";
			delWork(string0, erase);
			Step3Rep(string0);//Check for replacements
		}
	}
	else if(findSuffix(string0, "ingly")){
		temp = string0.substr(0, string0.size()-5);//ingly
		if(containsVowel(temp)){
			string erase = "ingly";
			delWork(string0, erase);
			Step3Rep(string0);//Check for replacements
		}
	}
}
void WStem::Step3Rep(string &string0){
	if(string0.size()<2){return;}
	string temp = string0.substr(string0.size()-2);
	if(temp=="at" or temp=="bl" or temp=="iz"){string0.push_back('e');}
	else if(isDouble(temp)){string0.pop_back();}
	else if(isShort(string0)){string0.push_back('e');}
	
}
//=======================================================================================


//STEP 4=================================================================================
void WStem::Step4(string &string0){
	string temp = "";
	if(string0.back() == 'y' and string0!="y"){
		if(!isVowel(string0, *(string0.end()-2), string0.size()-2)){
			if(string0.size() != 2){
				string0.pop_back();
				string0.push_back('i');
			}
		}
	}
}
//=======================================================================================


//STEP 5=================================================================================
void WStem::Step5(string &string0){
	if(findSuffix(string0, "tional") and !findSuffix(string0, "ational")){
		string0.pop_back();
		string0.pop_back();//leaves 'tion'
	}
	else if(findSuffix(string0, "enci") or findSuffix(string0, "anci")
		or findSuffix(string0, "abli")){
		string0.pop_back();
		string0.push_back('e');//leaves 'ence', 'ance', or 'abli'
	}
	if(findSuffix(string0, "entli")){
		string0.pop_back();
		string0.pop_back();//leaves 'ent'
	}
	else{Step5extra0(string0);}
}
void WStem::Step5extra0(string &string0){
	if(findSuffix(string0, "izer")){
		string0.pop_back();//leaves 'ize'
	}
	else if(findSuffix(string0, "ization")){
		string erase = "ation";
		delWork(string0, erase);//leaves 'ize'
		string0.push_back('e');
	}
	else{Step5extra1(string0);}
}
void WStem::Step5extra1(string &string0){
	if(findSuffix(string0, "ational")){
		string erase = "ional";
		delWork(string0, erase);//leaves 'at'
		string0.push_back('e');
	}
	else if(findSuffix(string0, "ation")){
		string erase = "ion";
		delWork(string0, erase);//leaves 'at'
		string0.push_back('e');
	}
	else if(findSuffix(string0, "ator")){
		string erase = "or";
		delWork(string0, erase);//leaves 'at'
		string0.push_back('e');
	}
	else{Step5extra2(string0);}
}
void WStem::Step5extra2(string &string0){
	if(findSuffix(string0, "alism")){
		string erase = "ism";
		delWork(string0, erase);//leaves 'al'
	}
	else if(findSuffix(string0, "aliti")){
		string erase = "iti";
		delWork(string0, erase);//leaves 'al'
	}
	else if(findSuffix(string0, "alli")){
		string0.pop_back();
		string0.pop_back();//leaves 'al'
	}
	else{Step5extra3(string0);}
}
void WStem::Step5extra3(string &string0){
	if(findSuffix(string0, "fulness") or findSuffix(string0, "ousness")
		or findSuffix(string0, "iveness")){//ness words
		string erase = "ness";
		delWork(string0, erase);//leaves 'ful', 'ous', or 'ive'
	}
	else if(findSuffix(string0, "ousli")){
		string0.pop_back();
		string0.pop_back();//leaves 'ous'
	}
	else if(findSuffix(string0, "iviti")){
		string erase = "iti";
		delWork(string0, erase);
		string0.push_back('e');//leaves 'ive'
	}
	else{Step5extra4(string0);}
}
void WStem::Step5extra4(string &string0){
	if(findSuffix(string0, "biliti")){
		string erase = "iliti";
		delWork(string0, erase);//leaves 'b'
		string0.push_back('l');
		string0.push_back('e');//leaves 'ble'
	}
	else if(findSuffix(string0, "bli")){
		string0.pop_back();
		string0.push_back('e');//leaves 'ble'
	}
	else{Step5extra5(string0);}
}
void WStem::Step5extra5(string &string0){
	if(findSuffix(string0, "ogi")){
		if(string0.at(string0.size()-4)=='l'){
			string0.pop_back();}//leaves 'og'
	}
	else if(findSuffix(string0, "fulli") or findSuffix(string0, "lessli")){
		string0.pop_back();
		string0.pop_back();//leaves 'ful' or 'less'
	}
	else if(findSuffix(string0, "li")){
		if(liEnding(string0)){
			string0.pop_back();
			string0.pop_back();
		}
	}
}
//======================================================================================


//STEP 6================================================================================
void WStem::Step6(string &string0, const string R1){
	if(findSuffix(string0, "ational")){
		if(findSuffix(R1, "ational") or R1=="ational"){
			string erase = "ional";
			delWork(string0, erase);
			string0.push_back('e');
		}
	}
	else if(findSuffix(string0, "tional")){
		if(findSuffix(R1, "tional") or R1=="tional"){
			string0.pop_back();
			string0.pop_back();
		}
	}
	else{Step6extra0(string0, R1);}
}
void WStem::Step6extra0(string &string0, const string R1){
	if(findSuffix(R1, "alize") or R1=="alize"){
		string erase = "ize";
		delWork(string0, erase);//leaves al
	}
	else if(findSuffix(R1, "icate") or findSuffix(R1, "iciti")
		or R1=="icate" or R1=="iciti"){
		string erase = "ate";//or "iti"
		delWork(string0, erase);//leaves 'ic'
	}
	else if(findSuffix(R1, "ical") or R1=="ical"){
		string0.pop_back();
		string0.pop_back();//leaves 'ic'
	}
	else{Step6extra1(string0, R1);}
}
void WStem::Step6extra1(string &string0, const string R1){
	string R2 = Region2(R1);//R2 is the region1 of region1
	if(findSuffix(R1, "ful") or R1=="ful"){
		string erase = "ful";
		delWork(string0, erase);//leaves nothing
	}
	else if(findSuffix(R1, "ness") or R1=="ness"){
		string erase = "ness";
		delWork(string0, erase);//leaves nothing
	}
	else if(findSuffix(R2, "ative") or R2=="ative"){
		string erase = "ative";
		delWork(string0, erase);//leaves nothing
	}
}
//=======================================================================================


//STEP 7=================================================================================
void WStem::Step7(string &string0, const string R1){
	string R2 = Region2(R1);
	if(findSuffix(string0, "ement")){
		if(findSuffix(R2, "ement") or R2=="ement"){
			string erase = "ement";//length 5 suffix
			delWork(string0, erase);//leaves nothing
		}
	}
	else if(findSuffix(R2, "al") or R2=="al"//length 2 suffix
		or findSuffix(R2, "er") or R2=="er"
		or findSuffix(R2, "ic") or R2=="ic"){
		string0.pop_back();
		string0.pop_back();
	}
	else{Step7extra0(string0, R2);}
}
void WStem::Step7extra0(string &string0, const string R2){//don't remake R2
	if(findSuffix(R2, "ance") or R2=="ance"//length 4 suffix
		or findSuffix(R2, "ence") or R2=="ence"
		or findSuffix(R2, "able") or R2=="able"
		or findSuffix(R2, "ible") or R2=="ible"){
		string erase = "ance";//or 'ence', 'able', or 'ible'
		delWork(string0, erase);//leaves nothing
	}
	else if(findSuffix(string0, "ment")){
		if(findSuffix(R2, "ment") or R2=="ment"){
			string erase = "ment";
			delWork(string0, erase);//leaves nothing
		}
	}
	else{Step7extra1(string0, R2);}
}
void WStem::Step7extra1(string &string0, const string R2){
	if(findSuffix(R2, "ant") or R2=="ant"//length 3 suffix
		or findSuffix(R2, "ent") or R2=="ent"
		or findSuffix(R2, "ism") or R2=="ism"
		or findSuffix(R2, "ate") or R2=="ate"
		or findSuffix(R2, "iti") or R2=="iti"
		or findSuffix(R2, "ous") or R2=="ous"
		or findSuffix(R2, "ive") or R2=="ive"
		or findSuffix(R2, "ize") or R2=="ize"){
		string0.pop_back();
		string0.pop_back();
		string0.pop_back();//leaves nothing
	}
	else if(findSuffix(R2, "ion") or R2=="ion"){
		if(string0.at(string0.size()-4)=='s' or string0.at(string0.size()-4)=='t'){
			string0.pop_back();
			string0.pop_back();
			string0.pop_back();//leaves 's' or 't'
		}
	}
}
//=======================================================================================


//STEP 8=================================================================================
void WStem::Step8(string &string0, const string R1){
	string R2 = Region2(R1);
	string temp = string0;
	temp.pop_back();
	if((findSuffix(R2, "e") or R2=="e")){
		string0.pop_back();//deletes 'e'
	}
	else if((findSuffix(R1, "e") or R1=="e") and !ShortSyll(temp)){
		string0.pop_back();//deletes 'e'
	}
	else if((findSuffix(R2, "l") or R2=="l") and string0.at(string0.size()-2)=='l'){
		string0.pop_back();//deletes 'l'
	}
}
//=======================================================================================

