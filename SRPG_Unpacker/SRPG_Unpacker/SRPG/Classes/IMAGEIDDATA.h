#pragma once

#include "EDITDATA.h"

struct IMAGEIDDATA : public EDITDATA
{
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
