#pragma once

#include "../Classes/EDITDATA.h"

struct CONSOLELOG : public EDITDATA
{
	DWORD this_3;
	DWORD this_4;
	MemData this_5;
	DWORD this_6;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
