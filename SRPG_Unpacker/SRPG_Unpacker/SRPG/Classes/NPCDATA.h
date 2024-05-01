#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"

struct NPCDATA : public EDITDATA, public LEGENDDATA
{
	MemData this_8;
	class CMenuOperation* m_pImageIDData = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
