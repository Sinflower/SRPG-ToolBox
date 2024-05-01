// Compatible up to v1.292

#include "MOVEOBJECTSHOW.h"
#include "../CMenuOperation.h"

void MOVEOBJECTSHOW::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 44);

	allocAndSetCMenuOp(&m_pLinePosData, SRPGClasses::LINEPOSDATA, fw);
}

void MOVEOBJECTSHOW::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 44);

	m_pLinePosData->dump(fw);
}
