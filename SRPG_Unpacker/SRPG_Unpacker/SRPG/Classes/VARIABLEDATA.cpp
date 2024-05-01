// Compatible up to v1.292

#include "VARIABLEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void VARIABLEDATA::init(FileReader& fw)
{
	LEGENDDATA::init(fw);
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();
}

void VARIABLEDATA::dump(FileWriter& fw) const
{
	LEGENDDATA::dump(fw);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);
}
