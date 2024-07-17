#include "PetriNet.h"

PetriNet& PetriNet::getInstance(){
    static PetriNet instance;
    return instance;
}
