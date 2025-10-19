/*
 *  File: FileHeader.cpp
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

#include "FileHeader.h"

#include <filesystem>

#include "Crypt.h"
#include "SRPG/Version.h"

namespace fs = std::filesystem;

FileHeader::FileHeader(const std::filesystem::path &fileName)
{
	Init(fileName);
}

void FileHeader::Init(const std::filesystem::path &fileName)
{
	if (fs::path(fileName).extension() == L".dts")
		initDTS(fileName);
	else
		initFolder(fileName.wstring());
}

void FileHeader::Print() const
{
	std::cout << "Magic Numnber          : " << std::format("{:#x}", m_magicNumber) << std::endl
			  << "Encryption             : " << (m_encrypted ? "Enabled" : "Disabled") << std::endl
			  << "File Version           : " << std::format("{:#x}", m_fileVersion) << std::endl
			  << "Load Runtime           : " << m_loadRuntime << std::endl
			  << "Segments Present       : " << m_presentSegments << std::endl
			  << "Project Data Address   : " << std::format("{:#x}", m_projectDataAddress) << std::endl
			  << "Section Data Addresses : " << std::endl;

	for (const auto &[idx, addr] : m_sectionDataAddresses)
		std::cout << std::format("{:#010x}\n", addr);
}

void FileHeader::Unpack(const std::wstring &outputFolder)
{
	if (!m_sectionInitDone)
		initSections();

	m_gSec.Unpack(outputFolder);
	m_uSec.Unpack(outputFolder);
	m_aSec.Unpack(outputFolder);
	m_fSec.Unpack(outputFolder);

	if (!m_oldFormat)
		m_vSec.Unpack(outputFolder);
	m_sSec.Unpack(outputFolder);
	m_pSec.Unpack(outputFolder);

	Config.Save(std::format(L"{}/{}", outputFolder, CONFIG_NAME));
}

void FileHeader::Pack(const std::wstring &outputFile)
{
	FileWriter fileWriter;
	fileWriter.Open(outputFile);

	std::vector<uint32_t> gSecSize = m_gSec.SecSizes();
	std::vector<uint32_t> uSecSize = m_uSec.SecSizes();
	std::vector<uint32_t> aSecSize = m_aSec.SecSizes();
	std::vector<uint32_t> fSecSize = m_fSec.SecSizes();
	std::vector<uint32_t> vSecSize = m_vSec.SecSizes();
	std::vector<uint32_t> sSecSize = m_sSec.SecSizes();

	uint32_t projectDataAddr = SumVector(gSecSize) + SumVector(uSecSize) + SumVector(aSecSize) + SumVector(fSecSize) + SumVector(vSecSize) + SumVector(sSecSize);

	if (m_magicNumber == -1)
	{
		// Switch the filewriter to buffer mode
		fileWriter.OpenInBufferMode();

		fileWriter.Write<uint32_t>(m_fileVersion);
		fileWriter.Write<uint32_t>(m_loadRuntime);
		fileWriter.Write<uint32_t>(projectDataAddr);

		fileWriter.Write<uint32_t>(m_presentSegments & Sections::Graphics ? 1 : 0);
		fileWriter.Write<uint32_t>(m_presentSegments & Sections::UI ? 1 : 0);
		fileWriter.Write<uint32_t>(m_presentSegments & Sections::Audio ? 1 : 0);
		fileWriter.Write<uint32_t>(m_presentSegments & Sections::Font ? 1 : 0);
		fileWriter.Write<uint32_t>(m_presentSegments & Sections::Script ? 1 : 0);
	}
	else
	{
		fileWriter.Write<uint32_t>(m_magicNumber);
		fileWriter.Write<uint32_t>(m_encrypted);
		fileWriter.Write<uint32_t>(m_fileVersion);
		fileWriter.Write<uint32_t>(m_loadRuntime);
		fileWriter.Write<uint32_t>(m_presentSegments);

		// Write project data address
		fileWriter.Write<uint32_t>(projectDataAddr);
	}

	uint32_t offset = 0;

	writeOffsets(fileWriter, gSecSize, offset);
	writeOffsets(fileWriter, uSecSize, offset);
	writeOffsets(fileWriter, aSecSize, offset);
	writeOffsets(fileWriter, fSecSize, offset);
	if (!m_oldFormat)
		writeOffsets(fileWriter, vSecSize, offset);
	writeOffsets(fileWriter, sSecSize, offset);

	m_gSec.Pack(fileWriter);
	m_uSec.Pack(fileWriter);
	m_aSec.Pack(fileWriter);
	m_fSec.Pack(fileWriter);
	if (!m_oldFormat)
		m_vSec.Pack(fileWriter);
	m_sSec.Pack(fileWriter);
	m_pSec.Pack(fileWriter);

	if (m_magicNumber == -1)
	{
		std::cout << "Encrypting file with very old encryption method ... " << std::flush;
		veryOldDtsCrypt(fileWriter.GetVec(), 1, false);
		std::cout << "Done" << std::endl;

		std::cout << "Writing entire file to disk ... " << std::flush;
		fileWriter.WriteToFile(outputFile);
		std::cout << "Done" << std::endl;
	}
}

void FileHeader::Reset()
{
	m_gSec.Reset();
	m_uSec.Reset();
	m_aSec.Reset();
	m_fSec.Reset();
	m_vSec.Reset();
	m_sSec.Reset();
	m_pSec.Reset();

	m_fileReader.Close();
	m_sectionDataAddresses.clear();

	m_sectionInitDone = false;
}

std::vector<uint8_t> FileHeader::GetProjectData() const
{
	return m_pSec.GetData();
}

void FileHeader::initSections(bool verbose)
{
	if (m_sectionInitDone || !m_fileReader) return;

	std::cout << "Initializing sections ..." << std::flush;

	if (verbose)
		std::cout << std::endl;

	std::deque<SecInfo> secInfos = m_sectionDataAddresses;

	m_gSec.Init(&m_fileReader, (m_presentSegments & Sections::Graphics), secInfos);
	m_uSec.Init(&m_fileReader, (m_presentSegments & Sections::UI), secInfos);
	m_aSec.Init(&m_fileReader, (m_presentSegments & Sections::Audio), secInfos);
	m_fSec.Init(&m_fileReader, (m_presentSegments & Sections::Font), secInfos);

	if (!m_oldFormat)
		m_vSec.Init(&m_fileReader, (m_presentSegments & Sections::Video), secInfos);

	// Not really sure on the conditions here, but it looks like the script section is always present in the archive if the file is encrypted.
	// Additionally, the material section is only present if the script section is truely present, i.e., part of the segment flag.
	m_sSec.Init(&m_fileReader, (m_presentSegments & Sections::Script) || (m_encrypted == 1), (m_presentSegments & Sections::Script), secInfos);
	m_pSec.Init(&m_fileReader, m_projectDataAddress);

	if (!m_fileReader.IsEoF())
		throw std::runtime_error("FileReader did not reach EOF");

	if (verbose)
		std::cout << "Initializing sections ... Done" << std::endl;
	else
		std::cout << " Done" << std::endl;

	m_sectionInitDone = true;
}

void FileHeader::writeOffsets(FileWriter &fileWriter, const std::vector<uint32_t> &sizes, uint32_t &offset) const
{
	for (const uint32_t &size : sizes)
	{
		// Note: If size is 0, it looks like the offset is written as 0
		// analyze this further in case errors arise
		fileWriter.Write<uint32_t>((size > 0 ? offset : 0));
		offset += size;
	}
}

void FileHeader::initDTS(const std::filesystem::path &fileName)
{
	m_fileReader.Open(fileName.wstring());

	m_magicNumber = m_fileReader.ReadUInt32();

	if (m_magicNumber != HEADER_MAGIC)
	{
		std::cerr << "File does not contain SRPG magic number, either the file is invalid or is encrypted, trying very old parsing style ..." << std::endl;
		m_fileReader.Seek(0);
		m_magicNumber = -1;

		std::cout << "Reading entire file into memory ... " << std::flush;
		DWORD fileSize = m_fileReader.GetSize();
		std::vector<uint8_t> fileData(fileSize);
		m_fileReader.ReadBytesVec(fileData);
		m_fileReader.Close();
		std::cout << "Done" << std::endl;

		std::cout << "Decrypting file with very old decryption method ... " << std::flush;
		veryOldDtsCrypt(fileData, 1);
		std::cout << "Done" << std::endl;

		m_fileReader.InitData(fileData);

		m_encrypted   = 0;
		m_fileVersion = m_fileReader.ReadUInt32();

		m_loadRuntime = m_fileReader.ReadUInt32();

		m_projectDataAddress = m_fileReader.ReadUInt32();

		const DWORD graphicsFlag = m_fileReader.ReadUInt32();
		const DWORD uiFlag       = m_fileReader.ReadUInt32();
		const DWORD audioFlag    = m_fileReader.ReadUInt32();
		const DWORD fontFlag     = m_fileReader.ReadUInt32();
		const DWORD scriptFlag   = m_fileReader.ReadUInt32();

		m_presentSegments = 0;
		if (graphicsFlag != 0) m_presentSegments |= Sections::Graphics;
		if (uiFlag != 0) m_presentSegments |= Sections::UI;
		if (audioFlag != 0) m_presentSegments |= Sections::Audio;
		if (fontFlag != 0) m_presentSegments |= Sections::Font;
		if (scriptFlag != 0) m_presentSegments |= Sections::Script;
	}
	else
	{
		m_encrypted   = m_fileReader.ReadUInt32();
		m_fileVersion = m_fileReader.ReadUInt32();

		// Since version 1.301 the encryption key has changed
		if (m_fileVersion >= NEW_CRYPT_START_VERSION)
			Crypt::SwitchToNewKey();

		m_loadRuntime     = m_fileReader.ReadUInt32();
		m_presentSegments = m_fileReader.ReadUInt32();

		m_projectDataAddress = m_fileReader.ReadUInt32();
	}

	// End of structure that differs between the very old and newer format
	// ---------------------------------------------------------------------

	if (m_fileVersion < NEW_FILE_FORMAT_START_VERSION)
		m_oldFormat = true;

	for (uint32_t i = 0; i < (m_oldFormat ? SECTION_COUNT_OLD : SECTION_COUNT); i++)
	{
		uint32_t sectionIdx = i;
		if (m_oldFormat && i >= 34)
			sectionIdx++; // Skip video section in old format
		m_sectionDataAddresses.push_back({ sectionIdx, m_fileReader.ReadUInt32() });
	}

	m_projectDataAddress += m_fileReader.GetOffset();

	for (SecInfo &info : m_sectionDataAddresses)
		info.second += m_fileReader.GetOffset();

	Config.Add("magicNumber", m_magicNumber);
	Config.Add("encrypted", m_encrypted);
	Config.Add("fileVersion", m_fileVersion);
	Config.Add("loadRuntime", m_loadRuntime);
	Config.Add("segments", m_presentSegments);

	Crypt::EnableCrypt(m_encrypted == 1);
}

void FileHeader::veryOldDtsCrypt(std::vector<uint8_t> &data, const uint32_t &mode, const bool &decrypt) const
{
	Crypt::SwitchToVeryOldKey();
	std::array<uint32_t, 4> xors = { 0x58C19454, 0x1B924CF4, 0x3A9EE0AD, 0x92C9D149 };

	if (mode == 1)
		xors[2] = 0x3A8EE0AD;
	else if (mode == 2)
		xors[3] = 0x92C9D148;

	if (!decrypt)
		Crypt::EncryptData(data, true);

	DWORD *pData = reinterpret_cast<DWORD *>(data.data());

	for (uint32_t i = 0; i < 4; i++)
		pData[i] ^= xors[i];

	if (decrypt)
		Crypt::DecryptData(data, true);
}

void FileHeader::initFolder(const std::wstring &inputFolder)
{
	Config.Load(std::format(L"{}/{}", inputFolder, CONFIG_NAME));

	m_magicNumber     = Config.Get<uint32_t>("magicNumber");
	m_encrypted       = Config.Get<uint32_t>("encrypted");
	m_fileVersion     = Config.Get<uint32_t>("fileVersion");
	m_loadRuntime     = Config.Get<uint32_t>("loadRuntime");
	m_presentSegments = Config.Get<uint32_t>("segments");

	if (m_fileVersion < NEW_FILE_FORMAT_START_VERSION)
		m_oldFormat = true;

	if (m_fileVersion >= NEW_CRYPT_START_VERSION)
		Crypt::SwitchToNewKey();

	Crypt::EnableCrypt(m_encrypted == 1);

	if (m_presentSegments & Sections::Graphics)
		m_gSec.Build(inputFolder);
	if (m_presentSegments & Sections::UI)
		m_uSec.Build(inputFolder);
	if (m_presentSegments & Sections::Audio)
		m_aSec.Build(inputFolder);
	if (m_presentSegments & Sections::Font)
		m_fSec.Build(inputFolder);
	if (m_presentSegments & Sections::Video && !m_oldFormat)
		m_vSec.Build(inputFolder);

	m_sSec.Build(inputFolder);
	m_pSec.Build(inputFolder);
}
