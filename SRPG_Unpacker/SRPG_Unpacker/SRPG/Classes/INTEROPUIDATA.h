#pragma once

#include "EDITDATA.h"
#include "INTEROPBASE.h"

struct INTEROPUIDATA : public EDITDATA, public INTEROPBASE
{
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
