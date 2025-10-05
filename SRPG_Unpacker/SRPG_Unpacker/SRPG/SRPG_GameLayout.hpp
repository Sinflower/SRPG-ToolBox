/*
 *  File: SRPG_GameLayout.hpp
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

class CMenuOperation;

class SRPG_GameLayout : public SRPG_ContainerBase
{
public:
	SRPG_GameLayout();
	virtual ~SRPG_GameLayout() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;
	void ApplyPatches(const std::filesystem::path& patchPath) override;

private:
	DWORD this_375 = 0;
	DWORD this_376 = 0;
	DWORD this_377 = 0;
	DWORD this_378 = 0;
	DWORD this_379 = 0;
	DWORD this_380 = 0;
	DWORD this_381 = 0;

	CMenuOperation* m_pMessageLayout = nullptr;
	CMenuOperation* m_pShopLayout    = nullptr;

	CMenuOperation* m_pTypeIDData = nullptr;

	CMenuOperation* m_pTitleLayout       = nullptr;
	CMenuOperation* m_pBattlePrepLayout  = nullptr;
	CMenuOperation* m_pMapCommandsLayout = nullptr;
	CMenuOperation* m_pBaseLayout        = nullptr;
	CMenuOperation* m_pManageLayout      = nullptr;

	struct RESOURCELAYOUTDATA* m_pResourceLayout = nullptr;
};
