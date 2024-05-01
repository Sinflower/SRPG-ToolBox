#pragma once

#include "EDITDATA.h"

struct COMPATIBLEDATA : public EDITDATA
{
	std::array <DWORD, 8> m_data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
