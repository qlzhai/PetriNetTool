#include "MyPathString.h"

MyPathString& MyPathString::getInstance()
{
	// TODO: 在此处插入 return 语句
	static MyPathString instance;
	return instance;
}

void MyPathString::mySplit(string str, map<string, int, CompareABString>& a_map, map<string, int, CompareABString>& b_map) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, '+')) {
		if (token.size() == 2) {
			//cout << token << endl;
			b_map[token]++;
		}
		if (token.size() > 2) {
			istringstream tokenStreamTemp(token);
			string temp;
			while (std::getline(tokenStreamTemp, temp, '-')) {
				//cout << temp << endl;
				if (temp[0] == 'b') {
					b_map[temp]++;
				}
				else {
					a_map[temp]++;
				}
			}
		}
	}
}

string MyPathString::getStringDelta(string input) {
	map<string, int, CompareABString> a_map;
	map<string, int, CompareABString> b_map;
	mySplit(input, a_map, b_map);

	string str = "";
	for (auto b : b_map) {
		if (b.second == 1) {
			str = str + "+" + b.first;
		}
		else {
			str = str + "+" + to_string(b.second) + "*" + b.first;
		}
	}

	for (auto a : a_map) {
		if (a.second == 1) {
			str = str + "-" + a.first;
		}
		else {
			str = str + "-" + to_string(a.second) + "*" + a.first;
		}
	}
	str = str.substr(1, str.size() - 1);
	return str;
}