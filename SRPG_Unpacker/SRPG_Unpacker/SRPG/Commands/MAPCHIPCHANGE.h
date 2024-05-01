#pragma once

#include "../Classes/EDITDATA.h"

struct MAPCHIPCHANGE : public EDITDATA
{
	DWORD this_3 = 0;
	MemData this_4;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
