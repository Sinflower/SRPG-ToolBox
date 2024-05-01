#pragma once

#include <string>

#include "FileHeader.h"

class DTSTool
{
public:
	DTSTool()  = default;
	~DTSTool() = default;

	bool Unpack(const std::wstring& dtsFile, const std::wstring& outputFolder)
	{
		m_fileHeader.Reset();
		m_fileHeader.Init(dtsFile);
		m_fileHeader.Unpack(outputFolder);

		return true;
	}

	bool Pack(const std::wstring& inputFolder, const std::wstring& dtsFile)
	{
		m_fileHeader.Reset();
		m_fileHeader.Init(inputFolder);
		m_fileHeader.Pack(dtsFile);

		return true;
	}

	const uint32_t& GetVersion() const
	{
		return m_fileHeader.GetVersion();
	}

	const uint32_t& GetResourceFlags() const
	{
		return m_fileHeader.GetResourceFlags();
	}

	std::vector<uint8_t> GetProjectData() const
	{
		return m_fileHeader.GetProjectData();
	}

private:
	FileHeader m_fileHeader = {};
};
