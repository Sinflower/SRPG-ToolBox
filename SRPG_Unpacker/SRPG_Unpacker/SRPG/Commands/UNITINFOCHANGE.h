#pragma once

#include "../Classes/EDITDATA.h"

struct UNITINFOCHANGE : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	DWORD this_8 = 0;
	DWORD this_9 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	MemData this_14;
	MemData this_15;
	class CMenuOperation* pImageIDData1 = nullptr;
	class CMenuOperation* pTypeIDData = nullptr;
	class CMenuOperation* pImageIDData2 = nullptr;
	class CMenuOperation* pImageIDData3 = nullptr;
	class CMenuOperation* pImageIDData4 = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
