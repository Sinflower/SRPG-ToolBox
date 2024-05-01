#pragma once

#include "BASEPATTERN.h"
#include "EDITDATA.h"

struct CUSTOMPATTERN : public BASEPATTERN
{
	MemData this_1;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
