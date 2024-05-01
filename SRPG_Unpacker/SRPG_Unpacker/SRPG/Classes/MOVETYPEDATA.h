#pragma once

#include "EDITDATA.h"

struct MOVETYPEDATA : public EDITDATA
{
	MemData this_3;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
