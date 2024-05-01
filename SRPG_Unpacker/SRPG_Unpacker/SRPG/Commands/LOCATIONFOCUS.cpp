// Compatible up to v1.292

#include "LOCATIONFOCUS.h"

void LOCATIONFOCUS::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 20);
}

void LOCATIONFOCUS::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 20);
}
