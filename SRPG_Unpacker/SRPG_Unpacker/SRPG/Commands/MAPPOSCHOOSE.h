#pragma once

#include "../Classes/EDITDATA.h"

struct MAPPOSCHOOSE : public EDITDATA
{
	std::vector<DWORD> this_3;
	std::array<DWORD, 9> this_10;
	DWORD this_19                 = 0;
	class CMenuOperation* this_20 = nullptr;
	DWORD this_21                 = 0;
	DWORD this_22                 = 0;
	class CMenuOperation* this_23 = nullptr;

	std::array<DWORD, 12> this_24;
	std::array<DWORD, 12> this_25;
	DWORD this_26 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
