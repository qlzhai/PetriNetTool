#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

class MyCompareABString {
public:
	bool operator()(const string& s1, const string& s2) const {
		string subS1 = s1.substr(1);
		string subS2 = s2.substr(1);

		int numS1 = stoi(subS1);
		int numS2 = stoi(subS2);

		return numS1 < numS2;
	}
};

class MyString
{
public:
	static MyString& getInstance();

	void mySplit(string str, map<string, int, MyCompareABString>& a_map, map<string, int, MyCompareABString>& b_map);

	string getStringDelta(string input);
};

