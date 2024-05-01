// Compatible up to v1.292

#include "MAPINFOCHANGE.h"
#include "../CMenuOperation.h"

void MAPINFOCHANGE::init(FileReader& fw)
{
	fw.ReadBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));

	initMemData(this_22, fw);
	allocAndSetCMenuOp(&this_23, SRPGClasses::FORCESORTIEDATA, fw);
	allocAndSetCMenuOp(&this_24, SRPGClasses::STRINGDATA, fw);
	allocAndSetCMenuOp(&this_25, SRPGClasses::STRINGDATA, fw);
}

void MAPINFOCHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(this_3.data(), static_cast<DWORD>(this_3.size() * sizeof(DWORD)));
	this_22.Write(fw);
	this_23->dump(fw);
	this_24->dump(fw);
	this_25->dump(fw);
}
