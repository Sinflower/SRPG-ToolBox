#pragma once

#include "EDITDATA.h"

struct INTEROPBASE
{
	MemData this_3;
	MemData this_4;
	void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
