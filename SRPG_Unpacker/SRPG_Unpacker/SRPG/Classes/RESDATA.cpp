// Compatible up to v1.292

#include "RESDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void RESDATA::init(FileReader& fw)
{
	IMAGEDATA::init(fw);

	this_35 = fw.ReadDWord();
}

void RESDATA::dump(FileWriter& fw) const
{
	IMAGEDATA::dump(fw);

	fw.Write(this_35);
}
