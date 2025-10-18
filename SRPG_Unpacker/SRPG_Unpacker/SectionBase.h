/*
 *  File: SectionBase.h
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

#include <cstdint>
#include <deque>
#include <vector>

#include "ConfigManager.h"
#include "FileAccess.h"
#include "Types.h"

template<typename T>
class SectionBase
{
public:
	SectionBase(const uint32_t &sections = 1) :
		m_sections(sections)
	{
	}

	virtual ~SectionBase() = default;

	void Init(FileReader *pFileReader, const bool &present, std::deque<SecInfo> &secInfos)
	{
		m_pFileReader = pFileReader;

		if (present)
			loadSections(secInfos);
		else
			consumeSections(secInfos);
	}

	virtual std::vector<uint32_t> SecSizes() const
	{
		std::vector<uint32_t> sizes;

		std::size_t dataIdx = 0;

		if (!m_secElemCnt.empty())
		{
			for (const auto &[secIdx, cnt] : m_secElemCnt)
			{
				uint32_t size = 0;
				size += 4; // Element count

				size += cnt * 4; // Element offsets

				for (uint32_t i = 0; i < cnt; i++)
					size += m_data[dataIdx + i].Size();

				dataIdx += cnt;

				sizes.push_back(size);
			}
		}
		else
		{
			for (uint32_t i = 0; i < m_sections; i++)
				sizes.push_back(0);
		}

		return sizes;
	}

	void Unpack(const std::wstring &outputFolder) const
	{
		std::cout << std::format("Unpacking {} ... ", name()) << std::flush;

		unpack(outputFolder);

		Config.Add(name(), m_secElemCnt);

		std::cout << "Done" << std::endl;
	}

	void Reset()
	{
		m_data.clear();
	}

	void Build(const std::wstring &inputFolder)
	{
		std::cout << std::format("Building {} ... ", name()) << std::flush;

		m_secElemCnt = Config.Get<SecMap>(name());

		build(inputFolder);

		std::cout << "Done" << std::endl;
	}

	void Pack(FileWriter &fileWriter) const
	{
		std::cout << std::format("Packing {} ... ", name()) << std::flush;
		writeSections(fileWriter);
		std::cout << "Done" << std::endl;
	}

protected:
	virtual void build(const std::wstring &inputFolder)
	{
		for (const auto &[secIdx, cnt] : m_secElemCnt)
		{
			for (uint32_t i = 0; i < cnt; i++)
				m_data.push_back(T(inputFolder, secIdx));
		}
	}

	virtual void loadSections(std::deque<SecInfo> &secInfos)
	{
		for (uint32_t i = 0; i < m_sections; i++)
		{
			SecInfo secInfo = secInfos.front();
			secInfos.pop_front();

			uint32_t startOffset  = m_pFileReader->GetOffset();
			uint32_t elementCount = m_pFileReader->ReadUInt32();

			if (startOffset != secInfo.second)
				throw std::runtime_error(std::format("Offset mismatch - Expected {:#x}, At {:#x}", secInfo.second, startOffset));

			m_secElemCnt[secInfo.first] = elementCount;

			// std::cout << std::format("Loading section {} ...", SECTION_NAMES[secInfo.first]) << std::endl;

			std::vector<uint32_t> dataOffsets = {};

			for (uint32_t elem = 0; elem < elementCount; elem++)
				dataOffsets.push_back(m_pFileReader->ReadUInt32() + startOffset);

			for (const uint32_t &offset : dataOffsets)
			{
				if (offset != m_pFileReader->GetOffset())
					throw std::runtime_error(std::format("Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

				m_data.push_back(T(m_pFileReader, secInfo.first));
			}
		}
	}

	virtual void consumeSections(std::deque<SecInfo> &secInfos)
	{
		for (uint32_t i = 0; i < m_sections; i++)
			secInfos.pop_front();
	}

	virtual void unpack(const std::wstring &outputFolder) const
	{
		for (const T &data : m_data)
			data.Unpack(outputFolder);
	}

	virtual void writeSections(FileWriter &fileWriter) const
	{
		std::size_t dataIdx = 0;

		for (const auto &[secIdx, cnt] : m_secElemCnt)
		{
			uint32_t offset = cnt * 4 + 4;
			fileWriter.Write<uint32_t>(cnt);

			if (cnt == 0)
				continue;

			for (uint32_t i = 0; i < cnt; i++)
			{
				fileWriter.Write<uint32_t>(offset);
				offset += m_data[dataIdx + i].Size();
			}

			for (uint32_t i = 0; i < cnt; i++)
				m_data[dataIdx + i].Pack(fileWriter);

			dataIdx += cnt;
		}
	}

	virtual std::string name() const
	{
		std::string name = typeid(*this).name();
		// Remove the class name prefix
		std::size_t p = name.find_first_of(" ");
		if (p != std::string::npos)
			name = name.substr(p + 1);

		// Remove potential namespace prefixes
		p = name.find_first_of("::");
		if (p != std::string::npos)
			name = name.substr(p + 2);

		return name;
	}

protected:
	class FileReader *m_pFileReader = nullptr;
	std::vector<T> m_data           = {};
	uint32_t m_sections             = 0;
	SecMap m_secElemCnt             = {};
};
