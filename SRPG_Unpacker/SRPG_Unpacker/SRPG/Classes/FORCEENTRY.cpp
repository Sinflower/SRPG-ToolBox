// Compatible up to v1.292

#include "FORCEENTRY.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FORCEENTRY::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void FORCEENTRY::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
