/*
 *  File: WEAPONDATA.h
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

#include "EDITDATA.h"
#include "ITEMBASE.h"

struct WEAPONDATA : public ITEMBASE
{
	DWORD res = 0;

	DWORD this_50     = 0;
	DWORD mt          = 0;
	DWORD rangeStart  = 0;
	DWORD rangeEnd    = 0;
	DWORD hit         = 0;
	DWORD crt         = 0;
	DWORD attackCount = 0;
	DWORD weaponLevel = 0;
	DWORD this_58     = 0;
	DWORD this_60     = 0;
	DWORD this_61     = 0;
	DWORD this_62     = 0;
	DWORD this_63     = 0;
	DWORD this_64     = 0;

	class CMenuOperation* m_pTypeIDData3 = nullptr;

	DWORD this_66 = 0;

	class CMenuOperation* m_pMotionIDData1 = nullptr;
	class CMenuOperation* m_pMotionIDData2 = nullptr;
	class CMenuOperation* m_pMotionIDData3 = nullptr;

	DWORD this_70 = 0;
	DWORD this_71 = 0;
	DWORD this_72 = 0;
	DWORD this_73 = 0;

	class CMenuOperation* m_pImageIDData1 = nullptr;
	class CMenuOperation* m_pImageIDData2 = nullptr;

	// OLD
	std::vector<DWORD> old_0;
	std::vector<DWORD> old_1;
	std::vector<DWORD> old_2;
	std::array<DWORD, 24> old_4;
	//////

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	void sub_102420(FileReader& fw);
	void sub_100680(FileReader& fw);
	void sub_FFF20(FileReader& fw);
	void dump_sub_FFF20(FileWriter& fw) const;
	void sub_102390(FileReader& fw);

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
};
