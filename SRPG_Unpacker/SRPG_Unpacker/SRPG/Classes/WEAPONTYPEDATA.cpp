// Compatible up to v1.292

#include "WEAPONTYPEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void WEAPONTYPEDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	initMemData(this_11, fw);

	LEGENDDATA::init(fw);

	allocAndSetCMenuOp(&m_pCompatibledata, SRPGClasses::COMPATIBLEDATA, fw);

	if (g_ArcVersion < 0x3FE)
	{
		this_12 = -1;
		this_13 = 0;
	}
	else
	{
		this_12 = fw.ReadDWord();
		this_13 = fw.ReadDWord();
	}

	if (g_ArcVersion < 0x438)
		this_14 = 1;
	else
		this_14 = fw.ReadDWord();

	if (g_ArcVersion >= 0x499)
		this_15 = fw.ReadDWord();
}

void WEAPONTYPEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);
	this_11.Write(fw);

	LEGENDDATA::dump(fw);

	m_pCompatibledata->dump(fw);

	if (g_ArcVersion >= 0x3FE)
	{
		fw.Write(this_12);
		fw.Write(this_13);
	}

	if (g_ArcVersion >= 0x438)
		fw.Write(this_14);

	if (g_ArcVersion >= 0x499)
		fw.Write(this_15);
}
