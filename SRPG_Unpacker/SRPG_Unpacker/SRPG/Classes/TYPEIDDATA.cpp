// Compatible up to v1.292

#include "TYPEIDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void TYPEIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void TYPEIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
