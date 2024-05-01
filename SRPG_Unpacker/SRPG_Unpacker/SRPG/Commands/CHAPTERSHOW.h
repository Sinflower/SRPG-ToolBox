#pragma once

#include "../Classes/EDITDATA.h"

struct CHAPTERSHOW : public EDITDATA
{
	DWORD this_3 = 0;
	MemData this_4;
	MemData this_5;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
