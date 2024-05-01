#pragma once

#include "EDITDATA.h"

struct SUPPORTDATA : public EDITDATA
{
	DWORD this_3                 = 0;
	class CMenuOperation* this_4 = nullptr;
	DWORD this_5                 = 0;
	DWORD this_6                 = 0;
	DWORD this_7                 = 0;
	DWORD this_8                 = 0;
	DWORD this_9                 = 0;
	DWORD this_10                = 0;
	DWORD this_11                = 0;

	class CMenuOperation* this_12 = nullptr;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
