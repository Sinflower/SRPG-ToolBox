// Compatible up to v1.292

#include "MESSAGESHOW.h"

void MESSAGESHOW::init(FileReader& fw)
{
	position = fw.ReadDWord();
	type     = fw.ReadDWord();
	unit     = fw.ReadDWord();
	this_7   = fw.ReadDWord();

	initMemData(message, fw);
}

void MESSAGESHOW::dump(FileWriter& fw) const
{
	fw.Write(position);
	fw.Write(type);
	fw.Write(unit);
	fw.Write(this_7);

	message.Write(fw);
}

void MESSAGESHOW::print(std::ostream& os) const
{
	os << "Message: " << message << std::endl;
	os << "Position: " << position << std::endl;
	os << "Type: " << type << std::endl;
	os << "Unit: " << unit << std::endl;
	os << "this_7: " << this_7;
}
