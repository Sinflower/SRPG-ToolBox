#pragma once

#include "EDITDATA.h"
#include "BASEPATTERN.h"

struct CUSTOMPATTERN : public BASEPATTERN
{
	MemData this_1;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
