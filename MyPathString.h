#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

class CompareABString {
public:
	bool operator()(const string& s1, const string& s2) const {
		string subS1 = s1.substr(1);
		string subS2 = s2.substr(1);

		int numS1 = stoi(subS1);
		int numS2 = stoi(subS2);

		return numS1 < numS2;
	}
};

class MyPathString
{
public:
	static MyPathString& getInstance();

	void mySplit(string str, map<string, int, CompareABString>& a_map, map<string, int, CompareABString>& b_map);

	string getStringDelta(string input);
};

