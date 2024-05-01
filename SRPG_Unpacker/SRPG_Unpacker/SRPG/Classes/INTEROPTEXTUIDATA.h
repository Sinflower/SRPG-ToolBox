#pragma once

#include "EDITDATA.h"
#include "INTEROPBASE.h"

struct INTEROPTEXTUIDATA : public EDITDATA, public INTEROPBASE
{
	DWORD this_5  = 0;
	DWORD this_6  = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

private:
};
