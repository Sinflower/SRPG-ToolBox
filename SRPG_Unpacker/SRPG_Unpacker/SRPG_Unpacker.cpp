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
		DecryptData(data);
	}

	ext = GetFileExtension(data);

	fs::path outPath = std::format(L"{}/{}/{}{}", outFolder, localPath, fN, ext);

	// Make sure the folder exists
	fs::create_directories(outPath.parent_path());

	FileWriter::WriteFile(outPath.wstring(), data);
}

void CopyAndDecryptOpenData(const std::wstring& dtsFolder, const std::wstring& outFolder, const nlohmann::ordered_json& j)
{
	static std::vector<std::wstring> FOLDER_NAMES = { L"Graphics", L"UI", L"Audio", L"Fonts", L"Video" };

	for (const auto& folder : FOLDER_NAMES)
	{
		std::wstring folderPath = std::format(L"{}/{}", dtsFolder, folder);

		if (fs::exists(folderPath))
		{
			for (const auto& entry : fs::recursive_directory_iterator(folderPath))
			{
				if (entry.is_regular_file())
					ProcessFile(dtsFolder, entry.path(), outFolder, j);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::string exeName = fs::path(argv[0]).filename().string();

		std::cout << "Usage: " << std::endl
				  << "Extract: " << exeName << " <IN_DTS> <OUT_FOLDER>" << std::endl
				  << "Pack: " << exeName << " <FOLDER> <OUT_DTS>" << std::endl;
		return 0;
	}

	try
	{
		LPWSTR* szArgList;
		int32_t nArgs;

		DTSTool dtsT;

		szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);

		// Initialize the CryptEngine
		Crypt::GetInstance();

		fs::path arg1 = fs::path(szArgList[1]);

		if (arg1.extension() == L".dts")
		{
			std::wstring outFolder = L"output";
			if (nArgs == 3)
				outFolder = fs::path(szArgList[2]).wstring();

			dtsT.Unpack(arg1.wstring(), outFolder);

			SRPG_Project sp({ dtsT.GetVersion(), dtsT.GetResourceFlags(), dtsT.GetProjectData() });
			sp.Dump(outFolder);

			CopyAndDecryptOpenData(arg1.parent_path().wstring(), outFolder, sp.GetResMapping());
		}
		else if (fs::is_directory(arg1))
		{
			std::wstring outFile = L"output.dts";
			if (nArgs == 3)
				outFile = fs::path(szArgList[2]).wstring();

			dtsT.Pack(arg1.wstring(), outFile);
		}
		else
		{
			std::wcerr << "Invalid argument provided: " << szArgList[1] << std::endl;
			return 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}
