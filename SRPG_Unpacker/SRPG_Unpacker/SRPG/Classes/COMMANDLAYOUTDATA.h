#pragma once

#include "EDITDATA.h"

struct COMMANDLAYOUTDATA : public EDITDATA
{
	MemData this_3;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	DWORD this_6 = 0;
	class CMenuOperation* m_pTypeIDData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
