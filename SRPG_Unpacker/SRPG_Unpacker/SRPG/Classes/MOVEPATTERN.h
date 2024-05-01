#pragma once

#include "BASEPATTERN.h"
#include "EDITDATA.h"

struct MOVEPATTERN : public BASEPATTERN
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
};
