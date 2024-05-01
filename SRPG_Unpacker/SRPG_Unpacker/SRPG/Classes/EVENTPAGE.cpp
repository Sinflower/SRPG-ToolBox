// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "EVENTPAGE.h"

void EVENTPAGE::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();

	if (this_4)
		this_5.init(fw);

	allocAndSetCMenuOp(&this_3, SRPGClasses::EVENTCOMMAND, fw);
}

void EVENTPAGE::dump(FileWriter& fw) const
{
	fw.Write(this_4);

	if (this_4)
		this_5.dump(fw);

	this_3->dump(fw);
}

void EVENTPAGE::print(std::ostream& os) const
{
	os << "EVENTPAGE" << std::endl;
	os << "this_4: " << this_4 << std::endl;
	os << "EventPage Data: " << this_5 << std::endl;
	os << "EventCommand: " << *this_3 << std::endl;
}
