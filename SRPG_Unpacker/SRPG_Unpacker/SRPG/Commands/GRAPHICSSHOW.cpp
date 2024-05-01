// Compatible up to v1.292

#include "GRAPHICSSHOW.h"

void GRAPHICSSHOW::init(FileReader& fw)
{
	if (g_ArcVersion < 0x434)
		m_data.resize(14);
	else
		m_data.resize(15);

	fw.ReadBytes(m_data.data(), static_cast<DWORD>(m_data.size() * sizeof(DWORD)));
}

void GRAPHICSSHOW::dump(FileWriter& fw) const
{
	fw.WriteBytes(m_data.data(), static_cast<DWORD>(m_data.size() * sizeof(DWORD)));
}
