// Compatible up to v1.292

#include "MAPPOSDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void MAPPOSDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void MAPPOSDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
