// Compatible up to v1.292

#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "EVENTCOMMAND.h"

void EVENTCOMMAND::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	res = fw.ReadDWord();

	if (HIWORD(res) == 1)
		initMemData(comment, fw);

	this_4 = static_cast<WORD>(res);
	this_5 = fw.ReadDWord();

	if (this_5)
		this_6.init(fw);

	this_7 = createCommand(this_3);
	this_7->id = fw.ReadDWord();
	this_7->init(fw);
}

void EVENTCOMMAND::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(res);

	if (HIWORD(res) == 1)
		comment.Write(fw);

	fw.Write(this_5);

	if (this_5)
		this_6.dump(fw);

	fw.Write(this_7->id);
	this_7->dump(fw);

}

void EVENTCOMMAND::print(std::ostream& os) const
{
	os << "EVENTCOMMAND" << std::endl;
	os << "this_3: " << this_3 << std::endl;
	os << "this_4: " << this_4 << std::endl;
	os << "this_5: " << this_5 << std::endl; // Maybe trigger present
	os << "this_6: " << this_6 << std::endl;
	//os << "this_7: " << *this_7 << std::endl;
	os << "Comment: " << comment << std::endl;
}
