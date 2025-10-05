/*
 *  File: SRPG_BaseSettings.hpp
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

#pragma once

#include "SRPG_ContainerBase.hpp"

#include <array>

class CMenuOperation;

class SRPG_BaseSettings : public SRPG_ContainerBase
{
public:
	SRPG_BaseSettings() {}
	virtual ~SRPG_BaseSettings() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;

	std::string GetSaveFileTitle() const
	{
		return saveFileTitle.ToString();
	}

	void SetSaveFileTitle(const std::string& title)
	{
		saveFileTitle = title;
	}

private:
	CMenuOperation* m_pShops     = nullptr;
	CMenuOperation* m_pBonuses   = nullptr;
	CMenuOperation* m_pQuests    = nullptr;
	CMenuOperation* m_pRestAreas = nullptr;

	std::array<CMenuOperation*, 6> m_pEventDatas = { nullptr };
	CMenuOperation* m_pSwitchData                = nullptr;
	MemData saveFileTitle;

	DWORD this_417 = 0;

	CMenuOperation* m_pTestMember = nullptr;

	DWORD this_419 = 0;
	DWORD this_420 = 0;
	DWORD this_421 = 0;
	DWORD this_422 = 0;
	DWORD this_423 = 0;

	CMenuOperation* m_pItemGroupData = nullptr;

	DWORD this_425 = 0;
	DWORD this_426 = 0;
	DWORD this_427 = 0;
	DWORD this_428 = 0;
	DWORD this_429 = 0;
};
