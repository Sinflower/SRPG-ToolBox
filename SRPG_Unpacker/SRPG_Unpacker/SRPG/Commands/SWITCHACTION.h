#pragma once

#include "../Classes/EDITDATA.h"

struct SWITCHACTION : public EDITDATA
{
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	//void sub_D1B60();
	class CMenuOperation* this_3 = nullptr;
	class CMenuOperation* this_4 = nullptr;
	class CMenuOperation* this_5 = nullptr;
};
