#pragma once

#include "EDITDATA.h"

struct CLASSGROUPENTRYDATA : public EDITDATA
{
	DWORD this_3 = 0;
	std::array <DWORD, 12> this_4 = { 0 };
	std::array <DWORD, 12> this_16 = { 0 };
	class CMenuOperation* m_pTypeIDData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
