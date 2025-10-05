/*
 *  File: SRPG_RecollectionEvents.cpp
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

#include "SRPG_RecollectionEvents.hpp"

#include "CMenuOperation.h"
#include "Functions.h"
#include "SRPG_Project.h"
#include "Version.h"

void SRPG_RecollectionEvents::Init(FileReader& fw)
{
	allocAndSetCMenuOp(&m_pRecollectionEvents, SRPGClasses::EVENTDATA, fw);
}

void SRPG_RecollectionEvents::Dump(FileWriter& fw) const
{
	m_pRecollectionEvents->dump(fw);
}

void SRPG_RecollectionEvents::WritePatches(const std::filesystem::path& outPath) const
{
	const std::filesystem::path extraFolder = ExtraPath(outPath);

	CHECK_OBJ_AND_WRITE_JSON_FILE(m_pRecollectionEvents, extraFolder, L"recollection.json");
}
