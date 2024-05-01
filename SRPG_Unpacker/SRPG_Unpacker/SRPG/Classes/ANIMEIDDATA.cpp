// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "ANIMEIDDATA.h"

void ANIMEIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void ANIMEIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}

