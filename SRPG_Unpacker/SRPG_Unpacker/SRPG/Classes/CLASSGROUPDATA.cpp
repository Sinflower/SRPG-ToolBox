// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "CLASSGROUPDATA.h"

void CLASSGROUPDATA::init(FileReader& fw)
{
	initMemData(this_4, fw);
	allocAndSetCMenuOp(&m_pClassGroupntryData, SRPGClasses::CLASSGROUPENTRYDATA, fw);
}

void CLASSGROUPDATA::dump(FileWriter& fw) const
{
	this_4.Write(fw);
	m_pClassGroupntryData->dump(fw);
}
