// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "DIFFICULTYDATA.h"

void DIFFICULTYDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();

	if (g_ArcVersion >= 0x418)
		allocAndSetCMenuOp(&m_pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 0x48E)
		allocAndSetCMenuOp(&m_pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);

	initMemData(this_12, fw);

	LEGENDDATA::init(fw);
}

void DIFFICULTYDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);

	if (g_ArcVersion >= 0x418)
		m_pTypeIDData1->dump(fw);

	if (g_ArcVersion >= 0x48E)
		m_pTypeIDData2->dump(fw);

	this_12.Write(fw);

	LEGENDDATA::dump(fw);
}
