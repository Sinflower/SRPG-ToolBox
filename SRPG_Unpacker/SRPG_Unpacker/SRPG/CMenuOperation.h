#pragma once

#include <Windows.h>
#include <fstream>
#include <nlohmann\json.hpp>
#include <vector>

#include "../FileAccess.h"
#include "Types.h"

class CMenuOperation
{
public:
	CMenuOperation(SRPGClasses const& type);
	CMenuOperation(DWORD const& type);
	~CMenuOperation();

	void init(FileReader& fw);
	void dump(FileWriter& fw) const;
	nlohmann::ordered_json ToJson() const;

	std::size_t GetElemCount() const;
	friend std::ostream& operator<<(std::ostream& os, CMenuOperation const& dt);
	friend std::wostream& operator<<(std::wostream& os, CMenuOperation const& dt);

private:
	std::vector<class EDITDATA*> m_data;
	DWORD m_type = 0;
};

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const SRPGClasses& type, FileReader& fw);
void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const DWORD& type, FileReader& fw);
