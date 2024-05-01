#pragma once

#include "../Classes/EDITDATA.h"

struct SCREENSCROLL : public EDITDATA
{
	DWORD this_3  = 0;
	DWORD this_4  = 0;
	DWORD this_5  = 0;
	DWORD this_6  = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
