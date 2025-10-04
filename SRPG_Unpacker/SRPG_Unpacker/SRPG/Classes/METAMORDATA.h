/*
 *  File: METAMORDATA.h
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

#pragma once

#include "LEGENDDATA.h"

#include <array>

struct METAMORDATA : public LEGENDDATA
{
	DWORD this_8  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	MemData command;
	std::array<DWORD, 12> this_17            = { 0 };
	std::array<DWORD, 12> this_29            = { 0 };
	DWORD this_41                            = 0;
	DWORD this_42                            = 0;
	class CMenuOperation* m_pTypeIDData1     = nullptr;
	class CMenuOperation* m_pItemConvertData = nullptr;
	MemData this_45;
	class CMenuOperation* m_pTypeIDData2 = nullptr;
	std::array<DWORD, 66> this_47        = { 0 };
	DWORD this_48                        = 0;
	DWORD this_49                        = 0;
	DWORD this_50                        = 0;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	void init(FileReader& fw) override;
	void dump([[maybe_unused]] FileWriter& fw) const override;

protected:
	nlohmann::ordered_json toJson() const override;
};
