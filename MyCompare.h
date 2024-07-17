#pragma once

#include <iostream>
using namespace std;
class MyCompare
{
public:
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& p) const {
		return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
	}
};

