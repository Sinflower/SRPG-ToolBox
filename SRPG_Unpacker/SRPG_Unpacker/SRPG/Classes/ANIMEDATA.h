#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct ANIMEDATA : public EDITDATA, public LEGENDDATA
{
	class CMenuOperation* m_pFrameList = nullptr;
	WORD this_9 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	MemData this_13;
	class CMenuOperation* m_pTypeIDData = nullptr;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	DWORD this_17 = 0;
	MemData this_18;
	DWORD this_19 = 0;
	DWORD this_20 = 0;
	DWORD this_21 = 0;
	DWORD this_22 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

private:
	void sub_36EF00(FileReader& fw);
};
