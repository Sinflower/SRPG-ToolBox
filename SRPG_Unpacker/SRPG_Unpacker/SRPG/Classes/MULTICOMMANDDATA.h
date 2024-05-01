#pragma once

#include "EDITDATA.h"

struct MULTICOMMANDDATA : public EDITDATA
{
	MemData this_3;
	DWORD this_4 = 0;
	void init(FileReader& fw);
	void dump([[maybe_unused]] FileWriter& fw) const;
};
