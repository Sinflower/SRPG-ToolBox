// Compatible up to v1.292

#include "EVENTSTATECHANGE.h"
#include "../CMenuOperation.h"

void EVENTSTATECHANGE::init(FileReader& fw)
{
	allocAndSetCMenuOp(&pEventActionData1, SRPGClasses::EVENTACTIONDATA, fw);
	allocAndSetCMenuOp(&pEventActionData2, SRPGClasses::EVENTACTIONDATA, fw);
	allocAndSetCMenuOp(&pEventActionData3, SRPGClasses::EVENTACTIONDATA, fw);

	if (g_ArcVersion < 0x3F9)
		pEventActionData4 = new CMenuOperation(SRPGClasses::EVENTACTIONDATA);
	else
		allocAndSetCMenuOp(&pEventActionData4, SRPGClasses::EVENTACTIONDATA, fw);
}

void EVENTSTATECHANGE::dump(FileWriter& fw) const
{
	pEventActionData1->dump(fw);
	pEventActionData2->dump(fw);
	pEventActionData3->dump(fw);

	if (g_ArcVersion >= 0x3F9)
		pEventActionData4->dump(fw);
}
