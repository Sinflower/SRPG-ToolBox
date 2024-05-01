#pragma once

#include "EDITDATA.h"

struct UNITCONDITIONDATA : public EDITDATA
{
	DWORD this_3                      = 0;
	DWORD this_4                      = 0;
	DWORD this_5                      = 0;
	DWORD this_6                      = 0;
	DWORD this_7                      = 0;
	DWORD this_8                      = 0;
	DWORD this_9                      = 0;
	std::array<DWORD, 12> this_10     = { 0 };
	std::array<DWORD, 12> this_22     = { 0 };
	DWORD this_34                     = 0;
	DWORD this_35                     = 0;
	class CMenuOperation* pTypeIDData = nullptr;
	DWORD this_37                     = 0;
	DWORD this_38                     = 0;
	DWORD this_39                     = 0;
	DWORD this_40                     = 0;
	DWORD this_41                     = 0;
	DWORD this_42                     = 0;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
