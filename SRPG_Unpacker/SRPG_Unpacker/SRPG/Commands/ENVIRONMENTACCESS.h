#pragma once

#include "../Classes/EDITDATA.h"

struct ENVIRONMENTACCESS : public EDITDATA
{
	class CMenuOperation* pTypeIDData1 = nullptr;
	class CMenuOperation* pTypeIDData2 = nullptr;
	class CMenuOperation* pTypeIDData3 = nullptr;
	DWORD this_6                       = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
