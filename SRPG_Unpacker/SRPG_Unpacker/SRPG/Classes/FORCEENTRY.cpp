// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "FORCEENTRY.h"

void FORCEENTRY::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void FORCEENTRY::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
