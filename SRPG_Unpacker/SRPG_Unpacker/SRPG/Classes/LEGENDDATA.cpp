// Compatible up to v1.292

#include "LEGENDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void LEGENDDATA::init(FileReader& fw)
{
	icon = fw.ReadQWord();
	initMemData(name, fw);
	initMemData(description, fw);
}

void LEGENDDATA::dump(FileWriter& fw) const
{
	fw.Write(icon);
	name.Write(fw);
	description.Write(fw);
}

void LEGENDDATA::print(std::ostream& os) const
{
	os << "Icon: " << icon << std::endl
	   << "Name: " << name << std::endl
	   << "Description: " << description;
}
