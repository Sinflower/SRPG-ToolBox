#pragma once

#include "../Classes/EDITDATA.h"

struct MAPSTATECHANGE : public EDITDATA
{
	DWORD this_3 = 0;
	std::vector<DWORD> this_4;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
