#ifndef PCWORDS_H_INCLUDE
#define PCWORDS_H_INCLUDE

#include <vector>
#include <string>
using std::string;
using std::vector;

#include<iostream>
#include<fstream>
using std::istream;
using std::ostream;

class PCwords {
public:
	
	//Punctuation work
	void punSep(string string0, vector<string> &v0);
	bool punCheck(char c);
	void punSepWork(const string &string0, string &string1, int count, vector<string> &vPush);
	void Punct(const string &string0, string &string1, int &count, vector<string> &vPush);
	void Alphanum(const string &string0, string &string1, int &count, vector<string> &vPush);
	bool commaWork(const string &string0, string &string1, int &count);
	bool periodWork(const string &string0, string &string1, int &count);

	//Capitalization work
	void capCheck(vector<string> &v0, vector<string> &vCap);
	bool numCheck(string string0);
	bool isNumString(string string0);
	bool isCap(string string1, vector<string> &vCap);
	void ambCap(vector<string> &v0, vector<string> &vCap);

private:
	int num0;
};

#endif
