#pragma once

#include "EDITDATA.h"

struct FONTDATA : public EDITDATA
{
	MemData this_3;
	MemData this_4;
	DWORD this_6  = 0;
	DWORD this_7  = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
