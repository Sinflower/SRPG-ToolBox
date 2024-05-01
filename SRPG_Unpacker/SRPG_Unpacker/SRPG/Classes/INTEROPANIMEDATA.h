#pragma once

#include "EDITDATA.h"
#include "INTEROPBASE.h"

struct INTEROPANIMEDATA : public EDITDATA, public INTEROPBASE
{
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
