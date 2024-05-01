// Compatible up to v1.292

#include "FRAMELIST.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FRAMELIST::init(FileReader& fw)
{
	allocAndSetCMenuOp(&m_pFrameData, SRPGClasses::FRAMEDATA, fw);

	this_5 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
}

void FRAMELIST::dump(FileWriter& fw) const
{
	m_pFrameData->dump(fw);
	fw.Write(this_5);
	fw.Write(this_4);
	fw.Write(this_6);
}
