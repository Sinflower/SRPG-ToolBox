#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct SKILLDATA : public EDITDATA, public LEGENDDATA
{
	DWORD res    = 0;
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	MemData this_10;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	DWORD this_17 = 0;
	DWORD this_20 = 0;
	MemData this_21;
	DWORD this_22[11]                    = { 0 };
	DWORD this_23[7]                     = { 0 };
	class CMenuOperation* m_pTypeIDData1 = nullptr;
	DWORD this_25                        = 0;
	DWORD this_26                        = 0;
	DWORD this_27                        = 0;
	class CMenuOperation* m_pTypeIDData2 = nullptr;
	DWORD this_29                        = 0;
	MemData this_30;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;

private:
	DWORD this_18 = 0;
	DWORD this_19 = 0;
	void sub_1046E0(FileReader& fw);
	void sub_10E310(FileReader& fw);
	void sub_10E620(FileReader& fw);
};
