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

#include "FileHeader.h"

#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <vector>

#include "Crypt.h"

namespace fs = std::filesystem;

// TODO:
// - Check for existing graphics, audio etc. files and if encrypted decrypt them

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

		szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);

		// Initialize the CryptEngine
		Crypt::GetInstance();

		fs::path arg1 = fs::path(szArgList[1]);

		if (arg1.extension() == L".dts")
		{
			std::wstring outFolder = L"output";
			if (nArgs == 3)
				outFolder = fs::path(szArgList[2]).wstring();

			FileHeader fh(arg1.wstring());
			fh.InitSections();
			fh.Unpack(outFolder);
		}
		else if (fs::is_directory(arg1))
		{
			std::wstring outFile = L"output.dts";
			if (nArgs == 3)
				outFile = fs::path(szArgList[2]).wstring();

			FileHeader fh(arg1.wstring());
			fh.Pack(outFile);
		}
		else if (std::wstring(szArgList[1]) == L"dec" && nArgs >= 3)
		{
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
							std::wcout << L"Decrypting: " << filePath << std::endl;

							std::vector<uint8_t> data;
							FileReader::ReadFile(filePath, data);

							Crypt::GetInstance().Decrypt(data);

							std::wstring ext = GetFileExtension(data);

							fs::path outPath = entry.path();
							outPath.replace_extension(ext);

							std::wcout << L"Writing: " << outPath << std::endl;
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
