#pragma once

#include "EDITDATA.h"
#include "INTEROPBASE.h"

struct INTEROPSCREENDATA : public EDITDATA, public INTEROPBASE
{
	DWORD this_6 = 0;
	DWORD this_7 = 0;
	DWORD this_8 = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	class CMenuOperation* m_pInterOptextUIData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
