// Compatible up to v1.292

#include "FRAMEORIGINAL.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FRAMEORIGINAL::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	initMemData(this_5, fw);
}

void FRAMEORIGINAL::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	this_5.Write(fw);
}
