#pragma once

#include "../Classes/EDITDATA.h"

struct MESSAGETEROP : public EDITDATA
{
	MemData this_3;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
