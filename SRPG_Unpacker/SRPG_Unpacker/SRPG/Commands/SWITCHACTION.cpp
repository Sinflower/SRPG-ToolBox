// Compatible up to v1.292

#include "SWITCHACTION.h"
#include "../CMenuOperation.h"

void SWITCHACTION::init(FileReader& fw)
{
	allocAndSetCMenuOp(&this_4, SRPGClasses::SWITCHACTIONDATA, fw);
	allocAndSetCMenuOp(&this_3, SRPGClasses::SWITCHACTIONDATA, fw);
	allocAndSetCMenuOp(&this_5, SRPGClasses::SWITCHACTIONDATA, fw);
}

void SWITCHACTION::dump(FileWriter& fw) const
{
	this_4->dump(fw);
	this_3->dump(fw);
	this_5->dump(fw);
}

// void SWITCHACTION::sub_D1B60()
//{
//	this_3 = new CMenuOperation(SRPGClasses::SWITCHACTIONDATA);
//	this_4 = new CMenuOperation(SRPGClasses::SWITCHACTIONDATA);
//	this_5 = new CMenuOperation(SRPGClasses::SWITCHACTIONDATA);
// }
