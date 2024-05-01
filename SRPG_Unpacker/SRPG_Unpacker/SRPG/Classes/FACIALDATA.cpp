// Compatible up to v1.292

#include "FACIALDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FACIALDATA::init(FileReader& fw)
{
	LEGENDDATA::init(fw);
}

void FACIALDATA::dump(FileWriter& fw) const
{
	LEGENDDATA::dump(fw);
}
