// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "SHOPDATA.h"

void SHOPDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	if (g_ArcVersion < 0x462)
		initMemData(this_4_old, fw, 60);
	else
		allocAndSetCMenuOp(&this_4, SRPGClasses::ITEMGROUPDATA, fw);
}

void SHOPDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);

	if (g_ArcVersion < 0x462)
		this_4_old.Write(fw);
	else
		this_4->dump(fw);
}
