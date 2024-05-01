// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "RESTSHOPDATA.h"

void RESTSHOPDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();

	allocAndSetCMenuOp(&pItemGroupData, SRPGClasses::ITEMGROUPDATA, fw);

	this_10 = fw.ReadDWord();

	if (this_10)
		this_11.init(fw);

	initMemData(this_12, fw);
	LEGENDDATA::init(fw);
}

void RESTSHOPDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);

	pItemGroupData->dump(fw);

	fw.Write(this_10);

	if (this_10)
		this_11.dump(fw);

	this_12.Write(fw);
	LEGENDDATA::dump(fw);
}
