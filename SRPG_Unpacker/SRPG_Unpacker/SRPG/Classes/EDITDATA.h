#pragma once

#include <Windows.h>
#include <array>
#include <fstream>
#include <vector>

#include <nlohmann\json.hpp>

#include "../../FileAccess.h"
#include "../../Utils.h"
#include "../Functions.h"
#include "../Version.h"

class EDITDATA
{
public:
	EDITDATA();
	virtual ~EDITDATA();
	std::string name() const;
	std::wstring wname() const;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
	virtual void print(std::wostream& os) const;
	nlohmann::ordered_json ToJson() const;

	friend std::ostream& operator<<(std::ostream& os, EDITDATA const& dt)
	{
		dt.print(os);
		return os;
	}

	friend std::wostream& operator<<(std::wostream& os, EDITDATA const& dt)
	{
		dt.print(os);
		return os;
	}

protected:
	virtual nlohmann::ordered_json toJson() const
	{
		return nlohmann::ordered_json();
	}

public:
	EDITDATA* pNext = nullptr;
	DWORD id        = 0;
};
