#pragma once

#include "../Classes/EDITDATA.h"

struct SCRIPTEXECUTE : public EDITDATA
{
	DWORD this_3 = 0;
	MemData this_4;
	MemData this_5;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

private:
	DWORD this_6                        = 0;
	DWORD this_7                        = 0;
	DWORD this_8                        = 0;
	DWORD this_9                        = 0;
	DWORD this_10                       = 0;
	DWORD this_12                       = 0;
	DWORD this_13                       = 0;
	DWORD this_14                       = 0;
	DWORD this_15                       = 0;
	DWORD this_16                       = 0;
	DWORD this_17                       = 0;
	DWORD this_18                       = 0;
	DWORD this_19                       = 0;
	DWORD this_20                       = 0;
	class CMenuOperation* m_pTypeIDData = nullptr;
	MemData this_22;
	DWORD this_26 = 0;

	void sub_EB6050(FileReader& fw);
};
