#include "PetriNet.h"

PetriNet& PetriNet::getInstance()
{
	// TODO: 在此处插入 return 语句
	static PetriNet instance;
	return instance;
}
