// Compatible up to v1.292

#include "UNITREMOVE.h"

void UNITREMOVE::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 28);
}

void UNITREMOVE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 28);
}
