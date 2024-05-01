#pragma once

#include "../Classes/EDITDATA.h"

struct FORCEBATTLE : public EDITDATA
{
	DWORD this_3                       = 0;
	DWORD this_4                       = 0;
	DWORD this_5                       = 0;
	DWORD this_6                       = 0;
	DWORD this_8                       = 0;
	class CMenuOperation* pForceEntry1 = nullptr;
	class CMenuOperation* pForceEntry2 = nullptr;
	DWORD this_11                      = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
