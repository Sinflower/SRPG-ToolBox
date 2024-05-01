// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "CUSTOMPATTERN.h"

void CUSTOMPATTERN::init(FileReader& fw)
{
	initMemData(this_1, fw);
}

void CUSTOMPATTERN::dump(FileWriter& fw) const
{
	this_1.Write(fw);
}
