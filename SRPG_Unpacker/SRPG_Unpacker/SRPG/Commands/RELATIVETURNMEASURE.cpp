// Compatible up to v1.292

#include "RELATIVETURNMEASURE.h"

void RELATIVETURNMEASURE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
}

void RELATIVETURNMEASURE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
}
