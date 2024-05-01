#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct RACEDATA : public EDITDATA, public LEGENDDATA
{
	MemData this_8;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
