// Compatible up to v1.292

#include "ITEMGROUPDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ITEMGROUPDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	if (g_ArcVersion >= 0x43D)
	{
		this_5 = fw.ReadDWord();
		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x4F3)
		allocAndSetCMenuOp(&m_pVariableConditionData, SRPGClasses::VARIABLECONDITIONDATA, fw);
}

void ITEMGROUPDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);

	if (g_ArcVersion >= 0x43D)
	{
		fw.Write(this_5);
		m_pTypeIDData->dump(fw);
	}

	if (g_ArcVersion >= 0x4F3)
		m_pVariableConditionData->dump(fw);
}
