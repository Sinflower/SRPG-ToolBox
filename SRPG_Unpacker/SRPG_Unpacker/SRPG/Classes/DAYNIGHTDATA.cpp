// Compatible up to v1.292

#include "DAYNIGHTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void DAYNIGHTDATA::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadByte();
	this_6 = fw.ReadByte();
	initMemData(this_3, fw);
}

void DAYNIGHTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	this_3.Write(fw);
}
