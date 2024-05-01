// Compatible up to v1.292

#include "UNITIDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void UNITIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void UNITIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
