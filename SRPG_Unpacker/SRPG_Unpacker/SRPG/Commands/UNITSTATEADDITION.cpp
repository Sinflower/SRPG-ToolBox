// Compatible up to v1.292

#include "UNITSTATEADDITION.h"

void UNITSTATEADDITION::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 24);
}

void UNITSTATEADDITION::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 24);
}
