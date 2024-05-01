// Compatible up to v1.292

#include "EVENTACTIONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void EVENTACTIONDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void EVENTACTIONDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
