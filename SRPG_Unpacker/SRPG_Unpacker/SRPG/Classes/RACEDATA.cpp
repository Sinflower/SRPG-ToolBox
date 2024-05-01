// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "RACEDATA.h"

void RACEDATA::init(FileReader& fw)
{
	initMemData(this_8, fw);
	LEGENDDATA::init(fw);
}

void RACEDATA::dump(FileWriter& fw) const
{
	this_8.Write(fw);
	LEGENDDATA::dump(fw);
}
