// Compatible up to v1.292

#include "TESTMEMBER.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void TESTMEMBER::init(FileReader& fw)
{
	allocAndSetCMenuOp(&this_3, SRPGClasses::UNITDATA, fw);
}

void TESTMEMBER::dump(FileWriter& fw) const
{
	this_3->dump(fw);
}
