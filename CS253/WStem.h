#ifndef WStem_H_INCLUDE
#define WStem_H_INCLUDE

#include <vector>
#include <string>
#include <map>
using std::map;
using std::string;
using std::vector;

#include<iostream>
#include<fstream>
using std::istream;
using std::ostream;

class WStem {
public:

	bool isVowel(const string string0, const char c, const int i);
	bool isDouble(const string string0);
	bool liEnding(const string string0);
	string Region1(const string string0);
	string Region2(const string R1);
	bool ShortSyll(const string string0);
	bool isShort(const string string0);
	bool hasDigitUpper(const string string0);

	bool findSuffix(const string string0, const string check);
	void delWork(string &string0, string &erase);
	bool containsVowel(const string string0);
	
	bool correctionCheck(string &string0, const map<string, string> &mRep);
	bool isPunctString(const string string0);
	
	void wStem(vector<string> &v0, const map<string, string> &mRep);
	void wStemWork(string &string0, const map<string, string> &mRep);
	void Step1(string &string0);
	
	void Step2(string &string0);
	void Swork(string &string0);
	
	void Step3(string &string0, const string R1);
	void Step3extra(string &string0);
	void Step3Rep(string &string0);

	void Step4(string &string0);
	
	void Step5(string &string0);
	void Step5extra0(string &string0);
	void Step5extra1(string &string0);
	void Step5extra2(string &string0);
	void Step5extra3(string &string0);
	void Step5extra4(string &string0);
	void Step5extra5(string &string0);

	void Step6(string &string0, const string R1);
	void Step6extra0(string &string0, const string R1);
	void Step6extra1(string &string0, const string R1);

	void Step7(string &string0, const string R1);
	void Step7extra0(string &string0, const string R2);
	void Step7extra1(string &string0, const string R2);

	void Step8(string &string0, const string R1);

private:
	int num0;
};

#endif
