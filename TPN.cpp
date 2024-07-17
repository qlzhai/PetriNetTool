#include "TPN.h"

TPN& TPN::getInstance() {
	// TODO: 在此处插入 return 语句
	static TPN instance;
	return instance;
}