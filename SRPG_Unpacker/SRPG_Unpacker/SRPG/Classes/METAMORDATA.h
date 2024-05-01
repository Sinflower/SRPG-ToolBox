#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

#include <array>

struct METAMORDATA : public EDITDATA, public LEGENDDATA
{
	DWORD this_8 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	MemData this_16;
	std::array <DWORD, 12> this_17 = { 0 };
	std::array <DWORD, 12> this_29 = { 0 };
	DWORD this_41 = 0;
	DWORD this_42 = 0;
	class CMenuOperation* m_pTypeIDData1 = nullptr;
	class CMenuOperation* m_pItemConvertData = nullptr;
	MemData this_45;
	class CMenuOperation* m_pTypeIDData2 = nullptr;
	std::array <DWORD, 66> this_47 = { 0 };
	DWORD this_48 = 0;
	DWORD this_49 = 0;
	DWORD this_50 = 0;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;


	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
