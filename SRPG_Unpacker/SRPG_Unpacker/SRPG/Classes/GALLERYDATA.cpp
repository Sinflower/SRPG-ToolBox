// Compatible up to v1.292

#include "GALLERYDATA.h"
#include "../CMenuOperation.h"

void GALLERYDATA::init(FileReader& fw)
{
	allocAndSetCMenuOp(&this_11, SRPGClasses::GALLERYGROUPDATA ,fw);

	this_8 = fw.ReadDWord();
	this_9 = fw.ReadDWord();

	initMemData(this_10, fw);

	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	initMemData(this_6, fw);
	initMemData(this_7, fw);
}

void GALLERYDATA::dump(FileWriter& fw) const
{
	this_11->dump(fw);
	fw.Write(this_8);
	fw.Write(this_9);

	this_10.Write(fw);

	fw.Write(this_4);
	fw.Write(this_5);

	this_6.Write(fw);
	this_7.Write(fw);
}
