// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "INTEROPGRAPHICSDATA.h"

void INTEROPGRAPHICSDATA::init(FileReader& fw)
{
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	this_8 = fw.ReadDWord();
	INTEROPBASE::init(fw);
}

void INTEROPGRAPHICSDATA::dump(FileWriter& fw) const
{
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	INTEROPBASE::dump(fw);
}
