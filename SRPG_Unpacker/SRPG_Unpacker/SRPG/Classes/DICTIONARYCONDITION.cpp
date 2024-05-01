// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "DICTIONARYCONDITION.h"

void DICTIONARYCONDITION::init(FileReader& fw)
{
	initMemData(this_3, fw);
	allocAndSetCMenuOp(&pSwitchActionData, SRPGClasses::SWITCHACTIONDATA, fw);
}

void DICTIONARYCONDITION::dump(FileWriter& fw) const
{
	this_3.Write(fw);
	pSwitchActionData->dump(fw);
}
