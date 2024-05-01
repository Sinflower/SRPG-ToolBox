#pragma once

#include "../Classes/EDITDATA.h"

struct GOLDCHANGE : public EDITDATA
{
	DWORD this_3;
	DWORD this_4;
	DWORD this_5;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
