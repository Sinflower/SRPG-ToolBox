// Compatible up to v1.292

#include "CUSTOMPATTERN.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void CUSTOMPATTERN::init(FileReader& fw)
{
	initMemData(this_1, fw);
}

void CUSTOMPATTERN::dump(FileWriter& fw) const
{
	this_1.Write(fw);
}
