// Compatible up to v1.292

#include "GRAPHICSHIDE.h"

void GRAPHICSHIDE::init(FileReader& fw)
{
	fw.ReadBytes(m_data.data(), 12);
}

void GRAPHICSHIDE::dump(FileWriter& fw) const
{
	fw.WriteBytes(m_data.data(), 12);
}
