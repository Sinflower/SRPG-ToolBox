#include "EDITDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

EDITDATA::EDITDATA()
{
}

EDITDATA::~EDITDATA()
{
}

std::string EDITDATA::name() const
{
	return typeid(*this).name();
}

std::wstring EDITDATA::wname() const
{
	return s2ws(std::string(typeid(*this).name()));
}

void EDITDATA::init(FileReader& fw)
{
	std::cerr << __FUNCSIG__ << " - IMPLEMENT ME - " << name() << std::endl;
	exit(-1);
}

void EDITDATA::dump(FileWriter& fw) const
{
	std::cerr << __FUNCSIG__ << " - IMPLEMENT ME - " << name() << std::endl;
	exit(-1);
}

void EDITDATA::print(std::ostream& os) const
{
	os << "Printing of " << name() << " currently not implemented";
}

void EDITDATA::print(std::wostream& os) const
{
	os << L"Printing of " << wname() << L" currently not implemented";
}

nlohmann::ordered_json EDITDATA::ToJson() const
{
	nlohmann::ordered_json j;
	const nlohmann::ordered_json data = toJson();

	if (data.empty())
		return j;

	j["id"]   = id;
	j["data"] = data;
	return j;
}
