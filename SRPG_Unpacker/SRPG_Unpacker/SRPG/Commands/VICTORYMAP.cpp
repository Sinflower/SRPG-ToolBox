// Compatible up to v1.292

#include "VICTORYMAP.h"

void VICTORYMAP::init(FileReader& fw)
{
	fw.ReadBytes(m_data.data(), 12);
}

void VICTORYMAP::dump(FileWriter& fw) const
{
	fw.WriteBytes(m_data.data(), 12);
}
