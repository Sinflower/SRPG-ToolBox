#pragma once

#include "../Classes/EDITDATA.h"

struct VICTORYMAP : public EDITDATA
{
	std::array <DWORD, 3> m_data;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
