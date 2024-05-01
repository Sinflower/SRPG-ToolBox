// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "CLASSTYPEDATA.h"

void CLASSTYPEDATA::init(FileReader& fw)
{
	this_8 = fw.ReadDWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();

	initMemData(this_13, fw);

	LEGENDDATA::init(fw);
}

void CLASSTYPEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);

	this_13.Write(fw);
	LEGENDDATA::dump(fw);
}
