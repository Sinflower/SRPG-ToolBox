// Compatible up to v1.292

#include "ANIMEIDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ANIMEIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void ANIMEIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
