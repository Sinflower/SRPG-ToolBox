// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "MOVETYPEDATA.h"

void MOVETYPEDATA::init(FileReader& fw)
{
	initMemData(this_3, fw);
}

void MOVETYPEDATA::dump(FileWriter& fw) const
{
	this_3.Write(fw);
}
