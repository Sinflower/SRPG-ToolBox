// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "CLASSIDDATA.h"

void CLASSIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void CLASSIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
