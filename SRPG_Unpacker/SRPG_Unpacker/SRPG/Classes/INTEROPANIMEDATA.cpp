// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "INTEROPANIMEDATA.h"

void INTEROPANIMEDATA::init(FileReader& fw)
{
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	INTEROPBASE::init(fw);
}

void INTEROPANIMEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_6);
	fw.Write(this_7);
	INTEROPBASE::dump(fw);
}
