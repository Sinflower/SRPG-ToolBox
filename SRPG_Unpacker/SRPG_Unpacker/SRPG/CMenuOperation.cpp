#include "CMenuOperation.h"
#include "Classes/EDITDATA.h"
#include "Functions.h"

CMenuOperation::CMenuOperation(SRPGClasses const& type) :
	m_type(static_cast<uint32_t>(type))
{
}

CMenuOperation::CMenuOperation(DWORD const& type) :
	m_type(type)
{
}

CMenuOperation::~CMenuOperation()
{
	for (EDITDATA*& p : m_data)
		delete (p);
}

std::size_t CMenuOperation::GetElemCount() const
{
	return m_data.size();
}

void CMenuOperation::init(FileReader& fw)
{
	DWORD objCnt = fw.ReadDWord();

	for (DWORD i = 0; i < objCnt; i++)
	{
		// v9 points to the class object
		EDITDATA* pObj = createSRPGClass(m_type);
		pObj->id       = fw.ReadDWord();
		pObj->init(fw);

		m_data.push_back(pObj);
	}
}

void CMenuOperation::dump(FileWriter& fw) const
{
	fw.Write(static_cast<DWORD>(m_data.size()));

	for (const EDITDATA* p : m_data)
	{
		fw.Write(p->id);
		p->dump(fw);
	}
}

nlohmann::ordered_json CMenuOperation::ToJson() const
{
	nlohmann::ordered_json j;

	for (const EDITDATA* p : m_data)
	{
		const nlohmann::ordered_json data = p->ToJson();
		if (!data.empty())
			j.push_back(data);
	}

	return j;
}

std::ostream& operator<<(std::ostream& os, CMenuOperation const& dt)
{
	os << "CMenuOperation: " << dt.m_type << std::endl;
	for (const EDITDATA* p : dt.m_data)
		os << *p << std::endl;

	return os;
}

std::wostream& operator<<(std::wostream& os, CMenuOperation const& dt)
{
	os << L"CMenuOperation: " << dt.m_type << std::endl;
	for (const EDITDATA* p : dt.m_data)
		os << *p << std::endl;

	return os;
}

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const SRPGClasses& type, FileReader& fw)
{
	if (*ppCMenuOperation == nullptr)
		*ppCMenuOperation = new CMenuOperation(type);
	(*ppCMenuOperation)->init(fw);
}

void allocAndSetCMenuOp(CMenuOperation** ppCMenuOperation, const DWORD& type, FileReader& fw)
{
	if (*ppCMenuOperation == nullptr)
		*ppCMenuOperation = new CMenuOperation(type);
	(*ppCMenuOperation)->init(fw);
}
