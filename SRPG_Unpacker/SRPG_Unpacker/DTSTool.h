/*
 *  File: DTSTool.h
 *  Copyright (c) 2024 Sinflower
 *
 *  MIT License
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#pragma once

#include <filesystem>
#include <string>

#include "FileHeader.h"

class DTSTool
{
public:
	DTSTool()  = default;
	~DTSTool() = default;

	bool Unpack(const std::filesystem::path& dtsFile, const std::filesystem::path& outputFolder)
	{
		m_fileHeader.Reset();
		m_fileHeader.Init(dtsFile);
		m_fileHeader.Unpack(outputFolder);

		return true;
	}

	bool Pack(const std::filesystem::path& inputFolder, const std::filesystem::path& dtsFile)
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

	nlohmann::ordered_json GetJson() const
	{
		return Config.GetJson();
	}

private:
	FileHeader m_fileHeader = {};
};
