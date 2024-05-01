// Compatible up to v1.292

#include "ITEMCHANGE.h"

void ITEMCHANGE::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 24);
}

void ITEMCHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 24);
}
