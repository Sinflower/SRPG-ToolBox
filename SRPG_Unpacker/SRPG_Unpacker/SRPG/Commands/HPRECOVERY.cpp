// Compatible up to v1.292

#include "HPRECOVERY.h"

void HPRECOVERY::init(FileReader& fw)
{
	fw.ReadBytes(m_data.data(), 28);
}

void HPRECOVERY::dump(FileWriter& fw) const
{
	fw.WriteBytes(m_data.data(), 28);
}
