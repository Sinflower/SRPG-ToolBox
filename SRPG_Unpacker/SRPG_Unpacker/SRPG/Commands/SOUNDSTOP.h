#pragma once

#include "../Classes/EDITDATA.h"

struct SOUNDSTOP : public EDITDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

	DWORD this_3 = 0;
	DWORD this_4 = 0;
};
