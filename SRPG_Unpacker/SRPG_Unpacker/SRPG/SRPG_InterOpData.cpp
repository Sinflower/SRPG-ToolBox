/*
 *  File: SRPG_InterOpData.cpp
 *  Copyright (c) 2025 Sinflower
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

#include "SRPG_InterOpData.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_InterOpData::Init(FileReader& fw)
{
#ifdef DEBUG_PRINT
	std::cout << "==== Method " << __FUNCSIG__ << " START ====" << std::endl;
	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropAnimeData, SRPGClasses::INTEROPANIMEDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPANIMEDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropMediaData, SRPGClasses::INTEROPMEDIADATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPMEDIADATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropGraphicsData, SRPGClasses::INTEROPGRAPHICSDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPGRAPHICSDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropUIData, SRPGClasses::INTEROPUIDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPUIDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropTextUIData, SRPGClasses::INTEROPTEXTUIDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPTEXTUIDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropScreenData, SRPGClasses::INTEROPSCREENDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSCREENDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropStringData1, SRPGClasses::INTEROPSTRINGDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSTRINGDATA=" << fw.GetOffset() << std::endl;
#endif

	allocAndSetCMenuOp(&m_pInteropStringData2, SRPGClasses::INTEROPSTRINGDATA, fw);
#ifdef DEBUG_PRINT
	std::cout << "OFFSET-INTEROPSTRINGDATA=" << fw.GetOffset() << std::endl;

	std::cout << "OFFSET=" << fw.GetOffset() << std::endl;
	std::cout << "==== Method END ====" << std::endl;
#endif
}

void SRPG_InterOpData::Dump(FileWriter& fw) const
{
	m_pInteropAnimeData->dump(fw);
	m_pInteropMediaData->dump(fw);
	m_pInteropGraphicsData->dump(fw);
	m_pInteropUIData->dump(fw);
	m_pInteropTextUIData->dump(fw);
	m_pInteropScreenData->dump(fw);
	m_pInteropStringData1->dump(fw);
	m_pInteropStringData2->dump(fw);
}

void SRPG_InterOpData::WritePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path resourceLocPath = SRPG_ContainerBase::ResourceLocationPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pInteropStringData1, resourceLocPath, L"strings.json");
	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pInteropScreenData, resourceLocPath, L"screens.json");
}

void SRPG_InterOpData::ApplyPatches(const std::filesystem::path& patchPath)
{
	const std::filesystem::path resourceLocPath = SRPG_ContainerBase::ResourceLocationPath(patchPath);

	CHECK_OBJ_AND_APPLY_PATCH(m_pInteropStringData1, resourceLocPath, L"strings.json");
	CHECK_OBJ_AND_APPLY_PATCH(m_pInteropScreenData, resourceLocPath, L"screens.json");
}
