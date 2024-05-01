/*
 *  File: ProjectSection.cpp
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

#include "ProjectSection.h"

#include <format>

ProjectSection::ProjectSection() :
	SectionBase()
{
}

void ProjectSection::Init(FileReader *pFileReader, const uint32_t &offset)
{
	m_pFileReader = pFileReader;
	loadSections(offset);
}

std::vector<uint32_t> ProjectSection::SecSizes() const
{
	uint32_t size = 0;

	if (!m_data.empty())
		size = m_data.front().Size();

	return { size };
}

void ProjectSection::build(const std::wstring &inputFolder)
{
	m_data.push_back(ProjectData(inputFolder));
}

void ProjectSection::loadSections(const uint32_t &offset)
{
	if (offset != m_pFileReader->GetOffset())
		throw std::runtime_error(std::format("[ProjectSection] Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

	m_data.push_back(ProjectData(m_pFileReader));
}

void ProjectSection::writeSections(FileWriter &fileWriter) const
{
	if (m_data.empty())
		return;

	m_data.front().Pack(fileWriter);
}