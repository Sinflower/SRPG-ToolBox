#pragma once

#include "EDITDATA.h"

struct ITEMGROUPDATA : public EDITDATA
{
	DWORD this_3 = 0;
	DWORD this_4 = 0;
	DWORD this_5 = 0;
	class CMenuOperation* m_pTypeIDData = nullptr;
	class CMenuOperation* m_pVariableConditionData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
