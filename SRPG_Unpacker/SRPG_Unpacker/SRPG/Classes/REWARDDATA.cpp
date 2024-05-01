// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "REWARDDATA.h"

void REWARDDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	this_8 = fw.ReadDWord();

	initMemData(this_9, fw);
}

void REWARDDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);

	this_9.Write(fw);
}
