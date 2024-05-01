// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "PARAMHEADDATA.h"

void PARAMHEADDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	initMemData(this_4, fw);
}

void PARAMHEADDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	this_4.Write(fw);
}
