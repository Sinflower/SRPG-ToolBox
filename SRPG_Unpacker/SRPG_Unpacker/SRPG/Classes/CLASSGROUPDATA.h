#pragma once

#include "EDITDATA.h"

struct CLASSGROUPDATA : public EDITDATA
{
	class CMenuOperation* m_pClassGroupntryData = nullptr;
	MemData this_4;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
