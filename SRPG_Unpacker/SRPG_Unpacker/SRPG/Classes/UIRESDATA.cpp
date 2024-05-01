// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "UIRESDATA.h"

void UIRESDATA::init(FileReader& fw)
{
	IMAGEDATA::init(fw);
	this_35 = fw.ReadDWord();
}

void UIRESDATA::dump(FileWriter& fw) const
{
	IMAGEDATA::dump(fw);
	fw.Write(this_35);
}
