// Compatible up to v1.292

#include "CLASSIDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void CLASSIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void CLASSIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
