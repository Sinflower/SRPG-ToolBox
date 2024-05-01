// Compatible up to v1.292

#include "ITEMCONDITIONDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ITEMCONDITIONDATA::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 16);
}

void ITEMCONDITIONDATA::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 16);
}
