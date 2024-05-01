// Compatible up to v1.292

#include "MOTIONIDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void MOTIONIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void MOTIONIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
