// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "UNITIDDATA.h"

void UNITIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void UNITIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
