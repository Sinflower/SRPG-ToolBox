/*
 *  File: SRPG_Unpacker.cpp
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

#include <deque>
#include <exception>
#include <filesystem>
#include <format>
#include <iomanip>
#include <iostream>
#include <vector>

#include "ConfigManager.h"
#include "Crypt.h"
#include "FileAccess.h"
#include "MemData.h"
#include "Utils.h"

namespace fs  = std::filesystem;
using SecInfo = std::pair<uint32_t, uint32_t>;

// TODO:
// - Write file order to a json file
// - Add information if given file is a sub element

static const std::vector<std::string> SECTION_NAMES = {
	"Graphics\\mapchip",
	"Graphics\\charchip",
	"Graphics\\face",
	"Graphics\\icon",
	"Graphics\\motion",
	"Graphics\\effect",
	"Graphics\\weapon",
	"Graphics\\bow",
	"Graphics\\thumbnail",
	"Graphics\\battleback",
	"Graphics\\eventback",
	"Graphics\\screenback",
	"Graphics\\worldmap",
	"Graphics\\eventstill",
	"Graphics\\charillust",
	"Graphics\\picture",
	"UI\\menuwindow",
	"UI\\textwindow",
	"UI\\title",
	"UI\\number",
	"UI\\bignumber",
	"UI\\gauge",
	"UI\\line",
	"UI\\risecursor",
	"UI\\mapcursor",
	"UI\\pagecursor",
	"UI\\selectcursor",
	"UI\\scrollcursor",
	"UI\\panel",
	"UI\\faceframe",
	"UI\\screenframe",
	"Audio\\music",
	"Audio\\sound",
	"Font",
	"Video",
	"Script"
};

class DataBase
{
public:
	DataBase(FileReader *pFileReader, const uint32_t &idx = -1) :
		m_pFileReader(pFileReader),
		m_idx(idx)
	{
	}

	DataBase(const uint32_t &idx) :
		m_idx(idx)
	{
	}

	virtual ~DataBase() = default;

	void Unpack(const std::wstring &outputFolder) const
	{
		const std::wstring dirPath = std::format(L"{}/{}/", outputFolder, (m_idx == -1 ? L"" : s2ws(SECTION_NAMES[m_idx])));

		if (!fs::exists(dirPath))
			fs::create_directories(dirPath);

		uint32_t subElemIdx = 0;

		// TODO: Fully implement sub elements
		for (const MemData<uint32_t> &data : m_data)
		{
			std::vector<uint8_t> dat(data.size, 0);
			m_pFileReader->ReadBytesVecAt(dat, data.offset, data.size);

			if (m_decrypt)
				DecryptData(dat);

			std::wstring fileName = m_name.ToWString();
			std::wstring ext      = L"";

			// Check if the file already has an extension
			if (fs::path(fileName).extension().empty())
				ext = getFileExtension(dat.data());

			fileName                    = std::format(L"{}{}{}", fileName, (subElemIdx > 0 ? std::to_wstring(subElemIdx) : L""), ext);
			const std::wstring filePath = std::format(L"{}{}", dirPath, fileName);

			if (subElemIdx == 0)
				add2Config(fs::path(fileName));

			if (!fs::exists(fs::path(filePath).parent_path()))
				fs::create_directories(fs::path(filePath).parent_path());

			write2File(filePath, dat);
			subElemIdx++;
		}
	}

	virtual void Pack(FileWriter &fileWriter) const
	{
		if (m_data.empty())
			return;

		fileWriter.Write<uint32_t>(m_name.size);
		fileWriter.WriteBytesVec(m_name.data);

		fileWriter.Write<uint32_t>(m_reserved0);
		fileWriter.Write<uint32_t>(m_reserved1);
		fileWriter.Write<uint32_t>(m_subElemCount);

		for (const MemData<uint32_t> &data : m_data)
			fileWriter.Write<uint32_t>(data.size);

		for (const MemData<uint32_t> &data : m_data)
		{
			std::vector<uint8_t> dat(data.size, 0);

			// Read the file associated with data from disk
			readFromFile(data.fileName, dat);

			if (m_decrypt)
				EncryptData(dat);

			fileWriter.WriteBytesVec(dat);
		}
	}

	virtual uint32_t Size() const
	{
		uint32_t size = 0;
		size += 4;                  // Name size
		size += m_name.size;        // Name data
		size += 4;                  // Reserved 0
		size += 4;                  // Reserved 1
		size += 4;                  // Sub element count
		size += m_subElemCount * 4; // Sub element sizes

		for (const MemData<uint32_t> &data : m_data)
			size += data.size;

		return size;
	}

protected:
	virtual void add2Config(const fs::path &file) const
	{
		if (m_idx == -1) return;

		Config.Add2Array(SECTION_NAMES[m_idx], file.filename().wstring(), { m_reserved0, m_reserved1, m_subElemCount });
	}

	virtual void write2File(const std::wstring &filePath, const std::vector<uint8_t> &data) const
	{
		std::ofstream outFile(filePath, std::ofstream::binary);

		outFile.write((const char *)data.data(), data.size());
		outFile.close();
	}

	virtual void readFromFile(const std::wstring &filePath, std::vector<uint8_t> &data) const
	{
		std::ifstream inFile(filePath, std::ifstream::binary);

		if (!inFile.is_open())
			throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

		inFile.seekg(0, inFile.end);
		std::size_t size = inFile.tellg();
		inFile.seekg(0, inFile.beg);

		if (data.empty())
			data.resize(size, 0);
		else if (size != data.size())
			throw std::runtime_error(std::format("File size mismatch: {} - Got: {} - Expected: {}", ws2s(filePath), size, data.size()));

		inFile.read(reinterpret_cast<char *>(data.data()), size);
		inFile.close();
	}

	virtual void loadData()
	{
		InitMemData<uint32_t>(m_name, *m_pFileReader);
		m_reserved0    = m_pFileReader->ReadUInt32();
		m_reserved1    = m_pFileReader->ReadUInt32();
		m_subElemCount = m_pFileReader->ReadUInt32();

		for (uint32_t i = 0; i < m_subElemCount; i++)
			m_dataSizes.push_back(m_pFileReader->ReadUInt32());

		for (const uint32_t dataSize : m_dataSizes)
			m_data.push_back(InitMemData<uint32_t>(*m_pFileReader, dataSize, false));
	}

	virtual void buildData(const std::wstring &inputFolder)
	{
		const std::wstring dirPath     = std::format(L"{}/{}", inputFolder, s2ws(SECTION_NAMES[m_idx]));
		const nlohmann::ordered_json j = Config.GetNext(SECTION_NAMES[m_idx]);

		if (j.empty()) return;

		const std::string file = j["name"].get<std::string>();
		const std::wstring ext = s2ws(fs::path(file).extension().string());

		m_name         = s2ws(fs::path(file).stem().string());
		m_reserved0    = j["elems"][0].get<uint32_t>();
		m_reserved1    = j["elems"][1].get<uint32_t>();
		m_subElemCount = j["elems"][2].get<uint32_t>();

		m_dataSizes.clear();

		for (uint32_t i = 0; i < m_subElemCount; i++)
		{
			const std::wstring filePath = std::format(L"{}/{}{}{}", dirPath, m_name.ToWString(), (i > 0 ? std::to_wstring(i) : L""), ext);
			if (!fs::exists(filePath))
				throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));

			m_data.push_back(MemData<uint32_t>(filePath, static_cast<uint32_t>(fs::file_size(filePath))));
		}
	}

	// TODO: Find a way to handle this without reading the entire file, but probably not possible
	//       fs::file_size() * 2 does not return the correct size for this type of file
	uint32_t getFileSizeUTF16(const std::wstring &filePath) const
	{
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		std::wifstream file(filePath, std::ios::in | std::ios::binary);

		if (file.fail())
			throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

		file.imbue(utf8_locale);
		std::wstringstream buffer;
		buffer << file.rdbuf();

		buffer.seekg(0, std::ios::end);
		std::size_t size = buffer.tellg() * 2;

		file.close();

		return static_cast<uint32_t>(size);
	}

private:
	std::wstring getFileExtension(const uint8_t *pData) const
	{
		unsigned char pngHeader[]  = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
		unsigned char oggHeader[]  = { 0x4F, 0x67, 0x67, 0x53 };
		unsigned char jpgHeader[]  = { 0xFF, 0xD8, 0xFF, 0xE0 };
		unsigned char jpgHeader2[] = { 0xFF, 0xD8, 0xFF, 0xE1 };
		unsigned char psHeader[]   = { 0x38, 0x42, 0x50, 0x53 };

		if (std::memcmp(pData, pngHeader, 8) == 0)
			return L".png";

		if (std::memcmp(pData, oggHeader, 4) == 0)
			return L".ogg";

		if (std::memcmp(pData, jpgHeader, 4) == 0 || std::memcmp(pData, jpgHeader2, 4) == 0)
			return L".jpg";

		if (std::memcmp(pData, psHeader, 4) == 0)
			return L".psd";

		return L".txt";
	}

protected:
	FileReader *m_pFileReader = nullptr;
	uint32_t m_idx            = 0;
	bool m_decrypt            = true;

	MemData<uint32_t> m_name = {};
	uint32_t m_reserved0     = 0;
	uint32_t m_reserved1     = 0;
	uint32_t m_subElemCount  = 0;

	std::vector<uint32_t> m_dataSizes = {};
	MemDataVec<uint32_t> m_data       = {};
};

class SectionData : public DataBase
{
public:
	SectionData(FileReader *pFileReader, const uint32_t &idx) :
		DataBase(pFileReader, idx)
	{
		loadData();
	}

	SectionData(const std::wstring &inputFolder, const uint32_t &idx) :
		DataBase(idx)
	{
		buildData(inputFolder);
	}
};

class ScriptData : public DataBase
{
public:
	ScriptData(FileReader *pFileReader, const uint32_t idx = -1) :
		DataBase(pFileReader, idx)
	{
		m_decrypt = false;
		loadData();
	}

	ScriptData(const std::wstring &inputFolder, const uint32_t &idx) :
		DataBase(idx)
	{
		buildData(inputFolder);
	}

	void Pack(FileWriter &fileWriter) const override
	{
		if (m_data.empty())
			return;

		fileWriter.Write<uint32_t>(m_name.size);
		fileWriter.WriteBytesVec(m_name.data);

		for (const MemData<uint32_t> &data : m_data)
		{
			std::vector<uint8_t> dat;

			// Read the file associated with data from disk
			readFromFile(data.fileName, dat);

			fileWriter.Write<uint32_t>(static_cast<uint32_t>(dat.size()));
			fileWriter.WriteBytesVec(dat);
		}
	}

	uint32_t Size() const override
	{
		uint32_t size = 0;
		size += 4;           // Name size
		size += m_name.size; // Name data

		for (const MemData<uint32_t> &data : m_data)
			size += (data.size + 2 /* 2-Bytes null-terminator */);

		size += 4; // Material count

		return size;
	}

protected:
	void add2Config(const fs::path &file) const override
	{
		Config.Add2Array(SECTION_NAMES[m_idx], file.wstring(), {});
	}

	void write2File(const std::wstring &filePath, const std::vector<uint8_t> &data) const override
	{
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		std::wofstream file(filePath, std::ios::out | std::ios::binary);

		if (file.fail())
			throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

		file.imbue(utf8_locale);

		std::size_t size = data.size();

		if (data.back() == 0x0)
			size -= 2;

		file.write(reinterpret_cast<const wchar_t *>(data.data()), size / 2);
		file.close();
	}

	void readFromFile(const std::wstring &filePath, std::vector<uint8_t> &data) const override
	{
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		std::wifstream file(filePath, std::ios::in | std::ios::binary);

		if (file.fail())
			throw std::runtime_error(std::format("Failed to open file: {}", ws2s(filePath)));

		file.imbue(utf8_locale);
		std::wstringstream buffer;
		buffer << file.rdbuf();

		buffer.seekg(0, std::ios::end);
		std::size_t size = buffer.tellg() * 2;
		buffer.seekg(0, std::ios::beg);

		data.resize(size, 0);
		std::memcpy(data.data(), (uint8_t *)buffer.str().c_str(), size);

		data.push_back(0x0);
		data.push_back(0x0);

		file.close();
	}

	void loadData() override
	{
		InitMemData<uint32_t>(m_name, *m_pFileReader);

		m_data.push_back(InitMemData<uint32_t>(*m_pFileReader, ~0, false));
	}

	void buildData(const std::wstring &inputFolder) override
	{
		const std::wstring dirPath     = std::format(L"{}/{}", inputFolder, s2ws(SECTION_NAMES[m_idx]));
		const nlohmann::ordered_json j = Config.GetNext(SECTION_NAMES[m_idx]);

		if (j.empty()) return;

		m_name = s2ws(j["name"].get<std::string>());

		const std::wstring filePath = std::format(L"{}/{}", dirPath, m_name.ToWString());

		if (!fs::exists(filePath))
			throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));

		m_data.push_back(MemData<uint32_t>(filePath, static_cast<uint32_t>(getFileSizeUTF16(filePath))));
	}
};

class ProjectData : public DataBase
{
	inline static const std::wstring SECTION_NAME = L"project.dat";

public:
	ProjectData(FileReader *pFileReader, [[maybe_unused]] const uint32_t idx = -1) :
		DataBase(pFileReader, idx)
	{
		loadData();
	}

	ProjectData(const std::wstring &inputFolder, const uint32_t &idx = -1) :
		DataBase(idx)
	{
		buildData(inputFolder);
	}

	void Pack(FileWriter &fileWriter) const override
	{
		if (m_data.empty())
			return;

		std::vector<uint8_t> dat;

		// Read the file associated with data from disk
		readFromFile(m_data.front().fileName, dat);

		if (m_decrypt)
			EncryptData(dat);

		fileWriter.WriteBytesVec(dat);
	}

protected:
	void loadData() override
	{
		m_name = SECTION_NAME;
		m_data.push_back(InitMemData<uint32_t>(*m_pFileReader, m_pFileReader->Remaining(), false));
	}

	void buildData(const std::wstring &inputFolder) override
	{
		m_name = SECTION_NAME;

		const std::wstring filePath = std::format(L"{}/{}", inputFolder, m_name.ToWString());

		if (!fs::exists(filePath))
			throw std::runtime_error(std::format("File not found: {}", ws2s(filePath)));

		m_data.push_back(MemData<uint32_t>(filePath, static_cast<uint32_t>(fs::file_size(filePath))));
	}
};

//////////////////////////////////////
///
//////////////////////////////////////

template<typename T>
class SectionBase
{
public:
	SectionBase(const uint32_t &sections = 1) :
		m_sections(sections)
	{
	}

	virtual ~SectionBase() = default;

	void Init(FileReader *pFileReader, std::deque<SecInfo> &secInfos)
	{
		m_pFileReader = pFileReader;
		loadSections(secInfos);
	}

	virtual std::vector<uint32_t> SecSizes() const
	{
		std::vector<uint32_t> sizes;

		std::size_t dataIdx = 0;

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

		return sizes;
	}

	void Unpack(const std::wstring &outputFolder) const
	{
		std::cout << std::format("Unpacking {} ... ", name()) << std::flush;

		Config.Add(name(), m_secElemCnt);

		for (const T &data : m_data)
			data.Unpack(outputFolder);

		std::cout << "Done" << std::endl;
	}

	void Reset()
	{
		m_data.clear();
	}

	virtual void Build(const std::wstring &inputFolder)
	{
		std::cout << std::format("Building {} ... ", name()) << std::flush;

		m_secElemCnt = Config.Get<std::map<uint32_t, uint32_t>>(name());

		for (const auto &[secIdx, cnt] : m_secElemCnt)
		{
			for (uint32_t i = 0; i < cnt; i++)
				m_data.push_back(T(inputFolder, secIdx));
		}

		std::cout << "Done" << std::endl;
	}

	void Pack(FileWriter &fileWriter) const
	{
		std::cout << std::format("Packing {} ... ", name()) << std::flush;
		writeSections(fileWriter);
		std::cout << "Done" << std::endl;
	}

protected:
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
	FileReader *m_pFileReader                 = nullptr;
	std::vector<T> m_data                     = {};
	uint32_t m_sections                       = 0;
	std::map<uint32_t, uint32_t> m_secElemCnt = {};
};

class GraphicSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 16;

public:
	GraphicSection() :
		SectionBase(SECTIONS)
	{
	}
};

class UiSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 15;

public:
	UiSection() :
		SectionBase(SECTIONS)
	{
	}
};

class AudioSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 2;

public:
	AudioSection() :
		SectionBase(SECTIONS)
	{
	}
};

class FontSection : public SectionBase<SectionData>
{
public:
	FontSection() :
		SectionBase()
	{
	}
};

class VideoSection : public SectionBase<SectionData>
{
public:
	VideoSection() :
		SectionBase()
	{
	}
};

class ScriptSection : public SectionBase<ScriptData>
{
public:
	ScriptSection() :
		SectionBase()
	{
	}

	virtual std::vector<uint32_t> SecSizes() const override
	{
		uint32_t size = 0;

		for (const auto &[secIdx, cnt] : m_secElemCnt)
		{
			size += 4; // Element count

			for (uint32_t i = 0; i < cnt; i++)
				size += m_data[i].Size();
		}

		size += 4; // Material count

		for (const ScriptData &data : m_matData)
			size += data.Size();

		return { size };
	}

protected:
	void loadSections(std::deque<SecInfo> &secInfos) override
	{
		SecInfo secInfo = secInfos.front();
		secInfos.pop_front();

		const uint32_t &offset = secInfo.second;

		if (offset != m_pFileReader->GetOffset())
			throw std::runtime_error(std::format("[ScriptSection] Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

		uint32_t startOffset  = m_pFileReader->GetOffset();
		uint32_t elementCount = m_pFileReader->ReadUInt32();

		m_secElemCnt[secInfo.first] = elementCount;

		for (uint32_t elem = 0; elem < elementCount; elem++)
			m_data.push_back(ScriptData(m_pFileReader, secInfo.first));

		loadScriptMaterials();
	}

	void writeSections(FileWriter &fileWriter) const override
	{
		for (const auto &[secIdx, cnt] : m_secElemCnt)
		{
			fileWriter.Write<uint32_t>(cnt);

			for (const ScriptData &data : m_data)
				data.Pack(fileWriter);
		}

		writeScriptMaterials(fileWriter);
	}

private:
	void loadScriptMaterials()
	{
		uint32_t matCount = m_pFileReader->ReadUInt32();

		if (matCount != 0x0)
		{
			throw std::runtime_error("Script materials are not supported yet");

			for (uint32_t elem = 0; elem < matCount; elem++)
				m_matData.push_back(ScriptData(m_pFileReader));
		}
	}

	void writeScriptMaterials(FileWriter &fileWriter) const
	{
		fileWriter.Write<uint32_t>(static_cast<uint32_t>(m_matData.size()));

		for (const ScriptData &data : m_matData)
			data.Pack(fileWriter);
	}

private:
	std::vector<ScriptData> m_matData = {};
};

class ProjectSection : public SectionBase<ProjectData>
{
public:
	ProjectSection() :
		SectionBase()
	{
	}

	void Init(FileReader *pFileReader, const uint32_t &offset)
	{
		m_pFileReader = pFileReader;
		loadSections(offset);
	}

	virtual std::vector<uint32_t> SecSizes() const override
	{
		uint32_t size = 0;

		if (!m_data.empty())
			size = m_data.front().Size();

		return { size };
	}

	void Build(const std::wstring &inputFolder) override
	{
		std::cout << std::format("Building {} ... ", name()) << std::flush;

		m_data.push_back(ProjectData(inputFolder));

		std::cout << "Done" << std::endl;
	}

protected:
	void loadSections(const uint32_t &offset)
	{
		if (offset != m_pFileReader->GetOffset())
			throw std::runtime_error(std::format("[ProjectSection] Offset mismatch - Expected {:#x}, At {:#x}", offset, m_pFileReader->GetOffset()));

		m_data.push_back(ProjectData(m_pFileReader));
	}

	void writeSections(FileWriter &fileWriter) const override
	{
		if (m_data.empty())
			return;

		m_data.front().Pack(fileWriter);
	}
};

//////////////////////////////////////
///
//////////////////////////////////////

class FileHeader
{
	static constexpr uint32_t HEADER_MAGIC      = 0x53544453; // SDTS
	static constexpr uint32_t DATA_START_OFFSET = 0xA8;
	static constexpr uint32_t SECTION_COUNT     = 36;

	static inline const std::wstring CONFIG_NAME = L"config.json";

	enum Sections
	{
		Graphics = 1,
		UI       = 2,
		Audio    = 4,
		Font     = 8,
		Script   = 0x10, // Might also be encrypted flag
		Video    = 0x20
	};

public:
	FileHeader(const std::wstring fileName)
	{
		if (fs::path(fileName).extension() == L".dts")
			initDTS(fileName);
		else
			initFolder(fileName);
	}

	~FileHeader()
	{
	}

	void Print() const
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

	void InitSections(bool verbose = false)
	{
		if (m_initSections || !m_fileReader) return;

		std::cout << "Initializing sections ...";

		if (verbose)
			std::cout << std::endl;

		std::deque<SecInfo> secInfos = m_sectionDataAddresses;

		if (m_presentSegments & Sections::Graphics)
			m_gSec.Init(&m_fileReader, secInfos);
		if (m_presentSegments & Sections::UI)
			m_uSec.Init(&m_fileReader, secInfos);
		if (m_presentSegments & Sections::Audio)
			m_aSec.Init(&m_fileReader, secInfos);
		if (m_presentSegments & Sections::Font)
			m_fSec.Init(&m_fileReader, secInfos);
		if (m_presentSegments & Sections::Video)
			m_vSec.Init(&m_fileReader, secInfos);

		// if (m_presentSegments & Sections::Script)
		m_sSec.Init(&m_fileReader, secInfos);

		m_pSec.Init(&m_fileReader, m_projectDataAddress);

		if (!m_fileReader.IsEoF())
			throw std::runtime_error("FileReader did not reach EOF");

		if (verbose)
			std::cout << "Initializing sections ... Done" << std::endl;
		else
			std::cout << " Done" << std::endl;

		m_initSections = true;
	}

	void Unpack(const std::wstring &outputFolder)
	{
		if (!m_initSections)
			InitSections();

		m_gSec.Unpack(outputFolder);
		m_uSec.Unpack(outputFolder);
		m_aSec.Unpack(outputFolder);
		m_fSec.Unpack(outputFolder);
		m_vSec.Unpack(outputFolder);
		m_sSec.Unpack(outputFolder);
		m_pSec.Unpack(outputFolder);

		Config.Save(std::format(L"{}/{}", outputFolder, CONFIG_NAME));
	}

	void Pack(const std::wstring &inputFolder, const std::wstring &outputFile)
	{
		FileWriter fileWriter;
		fileWriter.Open(outputFile);

		fileWriter.Write<uint32_t>(m_magicNumber);
		fileWriter.Write<uint32_t>(m_encrypted);
		fileWriter.Write<uint32_t>(m_fileVersion);
		fileWriter.Write<uint32_t>(m_loadRuntime);
		fileWriter.Write<uint32_t>(m_presentSegments);

		std::vector<uint32_t> gSecSize = m_gSec.SecSizes();
		std::vector<uint32_t> uSecSize = m_uSec.SecSizes();
		std::vector<uint32_t> aSecSize = m_aSec.SecSizes();
		std::vector<uint32_t> fSecSize = m_fSec.SecSizes();
		std::vector<uint32_t> vSecSize = m_vSec.SecSizes();
		std::vector<uint32_t> sSecSize = m_sSec.SecSizes();

		uint32_t allSecSize = SumVector(gSecSize) + SumVector(uSecSize) + SumVector(aSecSize) + SumVector(fSecSize) + SumVector(vSecSize) + SumVector(sSecSize);

		fileWriter.Write<uint32_t>(allSecSize);

		uint32_t offset = 0;

		writeOffsets(fileWriter, gSecSize, offset);
		writeOffsets(fileWriter, uSecSize, offset);
		writeOffsets(fileWriter, aSecSize, offset);
		writeOffsets(fileWriter, fSecSize, offset);
		writeOffsets(fileWriter, vSecSize, offset);
		writeOffsets(fileWriter, sSecSize, offset);

		m_gSec.Pack(fileWriter);
		m_uSec.Pack(fileWriter);
		m_aSec.Pack(fileWriter);
		m_fSec.Pack(fileWriter);
		m_vSec.Pack(fileWriter);
		m_sSec.Pack(fileWriter);
		m_pSec.Pack(fileWriter);
	}

private:
	void writeOffsets(FileWriter &fileWriter, const std::vector<uint32_t> &sizes, uint32_t &offset) const
	{
		for (const uint32_t &size : sizes)
		{
			fileWriter.Write<uint32_t>(offset);
			offset += size;
		}
	}

	void initDTS(const std::wstring &fileName)
	{
		m_fileReader.Open(fileName);

		m_magicNumber = m_fileReader.ReadUInt32();

		if (m_magicNumber != HEADER_MAGIC)
		{
			std::cerr << "File does not contain SRPG magic number, either the file is invalid or is encrypted." << std::endl;
			std::cerr << "Exiting ..." << std::endl;
			exit(0);
		}

		m_encrypted   = m_fileReader.ReadUInt32();
		m_fileVersion = m_fileReader.ReadUInt32();

		m_loadRuntime     = m_fileReader.ReadUInt32();
		m_presentSegments = m_fileReader.ReadUInt32();

		m_projectDataAddress = m_fileReader.ReadUInt32() + DATA_START_OFFSET;

		for (uint32_t i = 0; i < SECTION_COUNT; i++)
			m_sectionDataAddresses.push_back({ i, m_fileReader.ReadUInt32() + DATA_START_OFFSET });

		Config.Add("magicNumber", m_magicNumber);
		Config.Add("encrypted", m_encrypted);
		Config.Add("fileVersion", m_fileVersion);
		Config.Add("loadRuntime", m_loadRuntime);
		Config.Add("segments", m_presentSegments);
	}

	void initFolder(const std::wstring &inputFolder)
	{
		Config.Load(std::format(L"{}/{}", inputFolder, CONFIG_NAME));

		m_magicNumber     = Config.Get<uint32_t>("magicNumber");
		m_encrypted       = Config.Get<uint32_t>("encrypted");
		m_fileVersion     = Config.Get<uint32_t>("fileVersion");
		m_loadRuntime     = Config.Get<uint32_t>("loadRuntime");
		m_presentSegments = Config.Get<uint32_t>("segments");

		m_gSec.Reset();
		m_uSec.Reset();
		m_aSec.Reset();
		m_fSec.Reset();
		m_vSec.Reset();
		m_sSec.Reset();
		m_pSec.Reset();

		if (m_presentSegments & Sections::Graphics)
			m_gSec.Build(inputFolder);
		if (m_presentSegments & Sections::UI)
			m_uSec.Build(inputFolder);
		if (m_presentSegments & Sections::Audio)
			m_aSec.Build(inputFolder);
		if (m_presentSegments & Sections::Font)
			m_fSec.Build(inputFolder);
		if (m_presentSegments & Sections::Video)
			m_vSec.Build(inputFolder);

		m_sSec.Build(inputFolder);
		m_pSec.Build(inputFolder);
	}

private:
	FileReader m_fileReader = {};

	uint32_t m_magicNumber     = 0;
	uint32_t m_encrypted       = 0;
	uint32_t m_fileVersion     = 0;
	uint32_t m_loadRuntime     = 0;
	uint32_t m_presentSegments = 0;

	uint32_t m_projectDataAddress              = 0;
	std::deque<SecInfo> m_sectionDataAddresses = {};

	bool m_initSections = false;

	GraphicSection m_gSec = {};
	UiSection m_uSec      = {};
	AudioSection m_aSec   = {};
	FontSection m_fSec    = {};
	VideoSection m_vSec   = {};
	ScriptSection m_sSec  = {};
	ProjectSection m_pSec = {};
};

int main()
{
	try
	{
		// Initialize the CryptEngine
		Crypt::GetInstance();

#if 1
		FileHeader fh(L"output");
		fh.Pack(L"output", L"output.dts");
#else
		FileHeader fh(L"data.dts");
		fh.InitSections();
		fh.Unpack(L"output");
#endif
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
