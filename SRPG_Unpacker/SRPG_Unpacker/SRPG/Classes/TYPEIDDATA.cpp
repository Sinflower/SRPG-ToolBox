// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "TYPEIDDATA.h"

void TYPEIDDATA::init(FileReader& fw)
{
	id = fw.ReadDWord();
}

void TYPEIDDATA::dump(FileWriter& fw) const
{
	fw.Write(id);
}
