#pragma once

#include "EDITDATA.h"

struct NEWSKILLDATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
