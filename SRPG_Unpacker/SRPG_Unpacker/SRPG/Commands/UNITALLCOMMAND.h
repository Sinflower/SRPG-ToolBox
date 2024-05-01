#pragma once

#include "../Classes/EDITDATA.h"

struct UNITALLCOMMAND : public EDITDATA
{
	DWORD this_3;
	DWORD this_4;
	DWORD this_5;
	DWORD this_6;
	DWORD this_7;
	DWORD this_8;
	class CMenuOperation* pTypeIDData = nullptr;
	EDITDATA* this_10;
	DWORD this_11;
	DWORD this_12;
	DWORD this_13;
	DWORD this_14;
	DWORD this_15;
	DWORD this_16;
	DWORD this_17;

	std::array<DWORD, 12> this_24;
	std::array<DWORD, 12> this_25;
	DWORD this_26 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
