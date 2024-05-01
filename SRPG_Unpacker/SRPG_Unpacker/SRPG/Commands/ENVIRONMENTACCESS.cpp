// Compatible up to v1.292

#include "ENVIRONMENTACCESS.h"
#include "../CMenuOperation.h"

void ENVIRONMENTACCESS::init(FileReader& fw)
{
	allocAndSetCMenuOp(&pTypeIDData1, SRPGClasses::TYPEIDDATA, fw);
	allocAndSetCMenuOp(&pTypeIDData2, SRPGClasses::TYPEIDDATA, fw);
	allocAndSetCMenuOp(&pTypeIDData3, SRPGClasses::TYPEIDDATA, fw);

	this_6 = fw.ReadDWord();
}

void ENVIRONMENTACCESS::dump(FileWriter& fw) const
{
	pTypeIDData1->dump(fw);
	pTypeIDData2->dump(fw);
	pTypeIDData3->dump(fw);

	fw.Write(this_6);
}
