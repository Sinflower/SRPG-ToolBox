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
// - Check for existing graphics, audio etc. files and if encrypted decrypt them
// - Redesign section name handling, current solution is not great

// v1.140 (0x474) Added support for video archiving, before that it was not present in the archive

int main(int argc, char *argv[])
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
		LPWSTR *szArgList;
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
		}
		else if (fs::is_directory(arg1))
		{
			std::wstring outFile = L"output.dts";
			if (nArgs == 3)
				outFile = fs::path(szArgList[2]).wstring();

			dtsT.Pack(arg1.wstring(), outFile);
		}
		else if (std::wstring(szArgList[1]) == L"dec" && nArgs >= 3)
		{
			// If res_mapping.json exists, use it to get the correct file names
			nlohmann::ordered_json j;
			if (fs::exists("res_mapping.json"))
			{
				std::ifstream f("res_mapping.json");
				f >> j;
				f.close();

				nlohmann::ordered_json j2;

				// Build a new json with the correct mapping
				// Iterate over all objects in the json
				for (const auto &[key, value] : j.items())
				{
					nlohmann::ordered_json j3;
					// Iterate over the array in the object
					for (const auto &v : value)
					{
						// Get the name of the object
						std::string name = v["data"]["name"].get<std::string>();

						// Get the number of the object
						uint32_t id = v["id"].get<uint32_t>();

						// Add the object to the new json
						j3[std::to_string(id)] = name;
					}

					// Add the object to the new json
					j2[key] = j3;
				}

				// Update the json
				j = j2;
			}

			for (int32_t i = 2; i < nArgs; i++)
			{
				std::wstring folder = szArgList[i];

				// Iterate over all files in the folder and its subfolders and decrypt them
				for (const auto &entry : fs::recursive_directory_iterator(folder))
				{
					if (entry.is_regular_file())
					{
						std::wstring filePath = entry.path().wstring();
						std::wstring ext      = entry.path().extension().wstring();

						if (ext == L".srk")
						{
							// Get the parent folder name
							std::wstring parentFolder = entry.path().parent_path().wstring();

							std::string secName = GetSecNameFromPath(ws2s(parentFolder));
							std::wstring fN     = entry.path().filename().wstring();

							if (secName != "" && j.contains(secName))
							{
								try
								{
									// Get the file name of the current file without the extension
									std::string filename = ws2s(entry.path().filename().stem().wstring());

									std::string suffix = "";
									// Check if the file name contains a '-'
									size_t pos = filename.find('-');
									// Get the '-' and everything after it
									if (pos != std::string::npos)
										suffix = filename.substr(pos);

									// Convert the name to a number
									uint32_t num = std::stoul(filename.substr(0, pos), nullptr, 10);

									// Get the correct file name from the json
									std::string correctName = j[secName][std::to_string(num)].get<std::string>();

									// Build the new file name
									std::string newFilename = std::format("{}{}.srk", correctName, suffix);

									// Update the file name
									fN = s2ws(newFilename);
								}
								catch ([[maybe_unused]] const std::exception &e)
								{
									std::cerr << "Error: " << e.what() << std::endl;
								}
							}

							std::wcout << L"Decrypting: " << filePath << std::endl;

							std::vector<uint8_t> data;
							FileReader::ReadFile(filePath, data);

							DecryptData(data);

							std::wstring ext = GetFileExtension(data);

							fs::path outPath = entry.path();
							outPath.replace_filename(fN);
							outPath.replace_extension(ext);

							// std::wcout << L"Writing: " << outPath << std::endl;
							FileWriter::WriteFile(outPath, data);
						}
					}
				}
			}
		}
		else
		{
			std::wcerr << "Invalid argument provided: " << szArgList[1] << std::endl;
			return 1;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
