// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "FORCESORTIEDATA.h"

void FORCESORTIEDATA::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
}

void FORCESORTIEDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
}
