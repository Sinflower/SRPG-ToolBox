#pragma once

#include "../Classes/EDITDATA.h"

struct UNITCAPACITYCHANGE : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	std::vector<DWORD> this_6;
	std::vector<DWORD> this_32;
	DWORD this_50 = 0;
	DWORD this_51 = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
