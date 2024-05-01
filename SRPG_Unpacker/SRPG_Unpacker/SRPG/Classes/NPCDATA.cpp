// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "NPCDATA.h"

void NPCDATA::init(FileReader& fw)
{
	initMemData(this_8, fw);

	LEGENDDATA::init(fw);

	if (g_ArcVersion < 0x3F1)
		m_pImageIDData = new CMenuOperation(SRPGClasses::IMAGEIDDATA);
	else
		allocAndSetCMenuOp(&m_pImageIDData, SRPGClasses::IMAGEIDDATA, fw);
}

void NPCDATA::dump(FileWriter& fw) const
{
	this_8.Write(fw);

	LEGENDDATA::dump(fw);

	if (g_ArcVersion >= 0x3F1)
		m_pImageIDData->dump(fw);
}
