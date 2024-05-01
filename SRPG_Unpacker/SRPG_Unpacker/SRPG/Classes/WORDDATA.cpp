// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "WORDDATA.h"

void WORDDATA::init(FileReader& fw)
{
	this_12 = fw.ReadDWord();
	this_13 = fw.ReadDWord();

	initMemData(this_8, fw);
	allocAndSetCMenuOp(&pDictionaryCondition, SRPGClasses::DICTIONARYCONDITION, fw);

	LEGENDDATA::init(fw);

	if (g_ArcVersion >= 0x48D)
	{
		this_10 = fw.ReadDWord();
		this_11 = fw.ReadDWord();
	}
}

void WORDDATA::dump(FileWriter& fw) const
{
	fw.Write(this_12);
	fw.Write(this_13);

	this_8.Write(fw);
	pDictionaryCondition->dump(fw);

	LEGENDDATA::dump(fw);

	if (g_ArcVersion >= 0x48D)
	{
		fw.Write(this_10);
		fw.Write(this_11);
	}
}
