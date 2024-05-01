#pragma once

#include "EDITDATA.h"
#include "ITEMBASE.h"

struct WEAPONDATA : public ITEMBASE
{
	DWORD res = 0;

	DWORD this_50 = 0;
	DWORD mt          = 0;
	DWORD rangeStart  = 0;
	DWORD rangeEnd    = 0;
	DWORD hit         = 0;
	DWORD crt         = 0;
	DWORD attackCount = 0;
	DWORD weaponLevel = 0;
	DWORD this_58 = 0;
	DWORD this_60 = 0;
	DWORD this_61 = 0;
	DWORD this_62 = 0;
	DWORD this_63 = 0;
	DWORD this_64 = 0;
	class CMenuOperation* m_pTypeIDData3 = nullptr;
	DWORD this_66 = 0;
	class CMenuOperation* m_pMotionIDData1 = nullptr;
	class CMenuOperation* m_pMotionIDData2 = nullptr;
	class CMenuOperation* m_pMotionIDData3 = nullptr;
	DWORD this_70 = 0;
	DWORD this_71 = 0;
	DWORD this_72 = 0;
	DWORD this_73 = 0;
	class CMenuOperation* m_pImageIDData1 = nullptr;
	class CMenuOperation* m_pImageIDData2 = nullptr;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	void sub_102420(FileReader& fw);
	void sub_100680(FileReader& fw);
	void sub_FFF20(FileReader& fw, int a3);
	void dump_sub_FFF20(FileWriter& fw, int a3) const;
	void sub_102390(FileReader& fw);

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
