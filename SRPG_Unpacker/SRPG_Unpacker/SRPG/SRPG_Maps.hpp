/*
 *  File: SRPG_Maps.hpp
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

#include <array>

#include "SRPG_ContainerBase.hpp"

class SRPG_Maps : public SRPG_ContainerBase
{
public:
	SRPG_Maps() {}
	~SRPG_Maps() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;
	void ApplyPatches(const std::filesystem::path& patchPath) override;

private:
	std::wstring formatMapFileName(const DWORD& mapID) const;

private:
	CMenuOperation* m_pMapData         = nullptr;
	CMenuOperation* m_pMapTreeData1    = nullptr;
	CMenuOperation* m_pMapTreeData2    = nullptr;
	CMenuOperation* m_pDayNightData    = nullptr;
	CMenuOperation* m_pMapCommonEvents = nullptr;
	CMenuOperation* m_pBookmarkEvents  = nullptr;
	CMenuOperation* m_pBookmarkUnits   = nullptr;

	// sub_F8F6E0 - this_15
	DWORD this_21 = 0;
	BYTE this_22  = 0;
	DWORD this_23 = 0;
	BYTE this_24  = 0;

	std::array<CMenuOperation*, 12> m_pJumpIDData   = { nullptr };
	std::array<CMenuOperation*, 10> m_pJumpIDData2  = { nullptr };
	std::array<CMenuOperation*, 6> m_pParamHeadData = { nullptr };
	MemData this_37;
};
