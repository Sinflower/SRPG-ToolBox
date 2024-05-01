#pragma once

#include "../Classes/EDITDATA.h"

struct EVENTSTATECHANGE : public EDITDATA
{
	class CMenuOperation* pEventActionData1 = nullptr;
	class CMenuOperation* pEventActionData2 = nullptr;
	class CMenuOperation* pEventActionData3 = nullptr;
	class CMenuOperation* pEventActionData4 = nullptr;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
