#pragma once

#include "EDITDATA.h"

struct FRAMELIST : public EDITDATA
{
	class CMenuOperation* m_pFrameData = nullptr;
	DWORD this_4                       = 0;
	DWORD this_5                       = 0;
	DWORD this_6                       = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
