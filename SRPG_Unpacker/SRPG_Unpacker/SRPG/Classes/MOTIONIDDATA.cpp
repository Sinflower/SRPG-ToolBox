// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "MOTIONIDDATA.h"

void MOTIONIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void MOTIONIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
