#include "read.h"

#define INPUT_FILE_NAME "../pnt/recipe 1.pnt"

int main()
{   
    ReadFileInfo::getInstance().initPetriNet(INPUT_FILE_NAME);

    return 0;
}