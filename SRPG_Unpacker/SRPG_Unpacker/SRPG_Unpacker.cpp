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

#include <CLI11/CLI11.hpp>
#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <nlohmann\json.hpp>
#include <string>

#include "Crypt.h"
#include "DTSTool.h"
#include "FileHeader.h"
#include "SRPG\SRPG_Project.h"
#include "SectionNames.h"

namespace fs = std::filesystem;

static const std::string APP_NAME = "SRPG_Unpacker v0.1.0";

// TODO:
// - Redesign section name handling, current solution is not great

// v1.140 (0x474) Added support for video archiving, before that it was not present in the archive

std::wstring RestoreFileName(const std::string& filename, const std::string& secName, const nlohmann::ordered_json& j)
{
	std::wstring fN = s2ws(filename);

	if (secName != "" && j.contains(secName))
	{
		try
		{
			std::string suffix = "";
			// Check if the file name contains a '-'
			const size_t pos = filename.find('-');

			// Get the '-' and everything after it
			if (pos != std::string::npos)
				suffix = filename.substr(pos);

			// Convert the name to a number
			const uint32_t num = std::stoul(filename.substr(0, pos), nullptr, 10);

			// Get the correct file name from the json
			const std::string correctName = j[secName][std::to_string(num)].get<std::string>();

			// Build the new file name
			const std::string newFilename = std::format("{}{}", correctName, suffix);

			// Update the file name
			fN = s2ws(newFilename);
		}
		catch ([[maybe_unused]] const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

	return fN;
}

void ProcessFile(const std::wstring& dtsFolder, const fs::path& path, const std::wstring& outFolder, const nlohmann::ordered_json& j)
{
	const std::wstring parentFolder = path.parent_path().wstring();
	std::wstring localPath          = parentFolder.substr(dtsFolder.size() + 1);

	const std::string secName = GetSecNameFromPath(ws2s(localPath));
	std::wstring ext          = path.extension().wstring();

	std::wstring fN = path.stem().wstring();

	std::vector<uint8_t> data;
	FileReader::ReadFile(path.wstring(), data);

	if (ext == L".srk")
	{
		std::wstring inSecPath = localPath.substr(secName.size());

		std::vector<std::wstring> folders = SplitString(inSecPath, L'\\');

		// Restore the name of each folder
		for (std::wstring& f : folders)
		{
			if (f.empty()) continue;
			f = RestoreFileName(ws2s(f), secName, j);
		}

		// Rebuild the path
		localPath = std::format(L"{}/{}", s2ws(secName), JoinString(folders, L'\\'));

		fN = RestoreFileName(ws2s(fN), secName, j);
		Crypt::DecryptData(data);
	}

	ext = GetFileExtension(data);

	fs::path outPath = std::format(L"{}/{}/{}{}", outFolder, localPath, fN, ext);

	// Make sure the folder exists
	fs::create_directories(outPath.parent_path());

	FileWriter::WriteFile(outPath.wstring(), data);
}

void CopyAndDecryptOpenData(const std::wstring& dtsFolder, const std::wstring& outFolder, const nlohmann::ordered_json& j)
{
	const static std::vector<std::wstring> FOLDER_NAMES = { L"Graphics", L"UI", L"Audio", L"Fonts", L"Video" };

	for (const auto& folder : FOLDER_NAMES)
	{
		std::wstring folderPath = std::format(L"{}/{}", dtsFolder, folder);

		if (fs::exists(folderPath))
		{
			std::cout << " - Processing folder: " << ws2s(folderPath) << " ... " << std::flush;
			for (const auto& entry : fs::recursive_directory_iterator(folderPath))
			{
				if (entry.is_regular_file())
					ProcessFile(dtsFolder, entry.path(), outFolder, j);
			}
			std::cout << "Done" << std::endl;
		}
	}
}

// From: https://stackoverflow.com/a/45588456
class MBuf : public std::stringbuf
{
public:
	int sync()
	{
		fputs(str().c_str(), stdout);
		str("");
		return 0;
	}
};

static MBuf g_buf;

void EnableUTF8Print()
{
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IONBF, 0);
	std::cout.rdbuf(&g_buf);
}

void readDatFile(const fs::path& dataFolder, std::vector<BYTE>& outData)
{
	const fs::path datFile = dataFolder / SRPG_Project::PROJECT_DAT_NAME;

	if (!fs::exists(datFile))
		throw std::runtime_error(std::format("Data file not found: {}", datFile.string()));

	std::ifstream file(datFile, std::ios::binary);

	if (!file)
		throw std::runtime_error(std::format("Failed to open: {}", datFile.string()));

	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	outData.resize(size);
	file.read(reinterpret_cast<char*>(outData.data()), size);
	file.close();
}

void readConfigFile(const fs::path& dataFolder, nlohmann::ordered_json& outJson)
{
	const fs::path configFile = dataFolder / FileHeader::CONFIG_NAME;

	if (!fs::exists(configFile))
		throw std::runtime_error(std::format("Config file not found: {}", configFile.string()));
	std::ifstream file(configFile);
	if (!file)
		throw std::runtime_error(std::format("Failed to open: {}", configFile.string()));
	outJson = nlohmann::ordered_json::parse(file);
	file.close();
}

void unpack(const fs::path& dtsFile, const fs::path& outFolder = L"output")
{
	DTSTool dtsT;

	if (dtsFile.extension() != L".dts")
		throw std::runtime_error("Invalid input file, must be a .dts file");

	dtsT.Unpack(dtsFile, outFolder);

	SRPG_Project sp({ dtsT.GetVersion(), dtsT.GetResourceFlags(), dtsT.GetProjectData() });
	sp.SetupInternalResources(dtsT.GetJson());
	sp.DumpProj(outFolder);

	std::cout << "Copying and decrypting data not in the archive ... " << std::endl;
	CopyAndDecryptOpenData(dtsFile.parent_path().wstring(), outFolder, sp.GetResMapping());
	std::cout << "Finished copying and decrypting data" << std::endl;
}

void pack(const fs::path& inFolder, const fs::path& outFile = L"output.dts")
{
	DTSTool dtsT;
	dtsT.Pack(inFolder, outFile);
}

enum class PatchMode
{
	Create,
	Apply
};

void patch(const fs::path& dataFolder, const fs::path& patchFolder, const PatchMode& mode)
{
	std::vector<BYTE> data;
	nlohmann::ordered_json config;

	readDatFile(dataFolder, data);
	readConfigFile(dataFolder, config);

	DWORD version = 0;
	DWORD resFlag = 0;

	if (config.contains("fileVersion"))
		version = config["fileVersion"].get<DWORD>();
	else
		throw std::runtime_error("Config file does not contain 'fileVersion'");

	if (config.contains("segments"))
		resFlag = config["segments"].get<DWORD>();
	else
		throw std::runtime_error("Config file does not contain 'segments'");

	SRPG_Project sp({ version, resFlag, data });

	if (mode == PatchMode::Create)
		sp.WritePatch(patchFolder);
	else if (mode == PatchMode::Apply)
	{
		sp.ApplyPatch(patchFolder);
		sp.Dump(dataFolder);
	}
	else
		throw std::runtime_error("Invalid patch mode");
}

int main(int argc, char* argv[])
{
	CLI::App app{ APP_NAME };
	argv = app.ensure_utf8(argv);

	std::wstring defaultUnpack = L"output";
	std::wstring defaultPack   = L"output.dts";
	std::wstring defaultPatch  = L"patch";

	std::wstring input;
	app.add_option("INPUT", input, "<data.dts>\n<data_folder>\n<project.dat>")->required();

	std::wstring output = L"";
	app.add_option("-o,--output", output, "Specify the output, Defaults:\nunpack: \"output\"\npack: output.dts\n");

	bool createPatch = false;
	app.add_flag("-c,--create-patch", createPatch, "Create a patch from the provided project.dat");

	bool applyPatch = false;
	app.add_flag("-a,--apply-patch", applyPatch, "Apply a patch to the provided project.dat");

	CLI11_PARSE(app, argc, argv);

	EnableUTF8Print();

	// Initialize the CryptEngine
	Crypt::GetInstance();

	try
	{
		fs::path inputPath = fs::path(input);

		if (inputPath.extension() == L".dts" && fs::exists(inputPath))
		{
			const fs::path outputPath = (output.empty() ? defaultUnpack : output);
			unpack(inputPath, outputPath);
			std::cout << "Successfully unpacked to: " << outputPath.string() << std::endl;
		}
		else if (fs::is_directory(inputPath))
		{
			const fs::path outputPath = (output.empty() ? defaultPack : output);
			pack(inputPath, outputPath);
			std::cout << "Successfully packed to: " << outputPath.string() << std::endl;
		}
		else if (inputPath.extension() == L".dat" && fs::exists(inputPath))
		{
			if (createPatch && applyPatch)
				throw std::runtime_error("Cannot create and apply a patch at the same time");
			if (!createPatch && !applyPatch)
				throw std::runtime_error("Must specify either --create-patch or --apply-patch");

			const fs::path patchPath = (output.empty() ? defaultPatch : output);
			patch(inputPath.parent_path(), patchPath, (createPatch ? PatchMode::Create : PatchMode::Apply));
		}
		else
		{
			throw std::runtime_error("Invalid input provided, must be a .dts file or a folder, or project.dat");
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}
