// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "QUESTDATA.h"

void QUESTDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_15 = fw.ReadDWord();
	this_16 = fw.ReadDWord();

	if (this_16)
		this_17.init(fw);

	this_18 = fw.ReadDWord();

	if (this_18)
		this_19.init(fw);

	allocAndSetCMenuOp(&pRewardData, SRPGClasses::REWARDDATA, fw);

	initMemData(this_21, fw);
	LEGENDDATA::init(fw);
}

void QUESTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_15);
	fw.Write(this_16);

	if (this_16)
		this_17.dump(fw);

	fw.Write(this_18);

	if (this_18)
		this_19.dump(fw);

	pRewardData->dump(fw);

	this_21.Write(fw);
	LEGENDDATA::dump(fw);
}
