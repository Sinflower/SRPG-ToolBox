// Compatible up to v1.292

#include "FORCEBATTLE.h"
#include "../CMenuOperation.h"

void FORCEBATTLE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_8 = fw.ReadDWord();

	allocAndSetCMenuOp(&pForceEntry1, SRPGClasses::FORCEENTRY, fw);
	allocAndSetCMenuOp(&pForceEntry2, SRPGClasses::FORCEENTRY, fw);

	if (g_ArcVersion < 0x418)
		this_11 = -1;
	else
		this_11 = fw.ReadDWord();
}

void FORCEBATTLE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_8);

	pForceEntry1->dump(fw);
	pForceEntry2->dump(fw);

	if (g_ArcVersion >= 0x418)
		fw.Write(this_11);
}
