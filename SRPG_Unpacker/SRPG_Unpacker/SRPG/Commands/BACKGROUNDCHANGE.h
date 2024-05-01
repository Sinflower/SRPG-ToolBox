#pragma once

#include "../Classes/EDITDATA.h"

struct BACKGROUNDCHANGE : public EDITDATA
{
	std::array <DWORD, 7> data;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
