#pragma once

#include "EDITDATA.h"

struct LEGENDDATA
{
	QWORD icon = 0;
	MemData name;
	MemData description;
	virtual void init(FileReader& fw);
	virtual void dump(FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
