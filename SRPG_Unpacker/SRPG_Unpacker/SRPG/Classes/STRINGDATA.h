#pragma once

#include "EDITDATA.h"

struct STRINGDATA : public EDITDATA
{
	MemData data;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
