// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "RPASSDATA.h"

void RPASSDATA::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
}

void RPASSDATA::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);
}
