// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "FACIALDATA.h"

void FACIALDATA::init(FileReader& fw)
{
	LEGENDDATA::init(fw);
}

void FACIALDATA::dump(FileWriter& fw) const
{
	LEGENDDATA::dump(fw);
}
