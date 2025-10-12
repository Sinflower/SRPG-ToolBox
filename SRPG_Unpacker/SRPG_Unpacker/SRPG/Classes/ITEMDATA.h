/*
 *  File: ITEMDATA.h
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

#include "../Commands/SWITCHACTION.h"
#include "EDITDATA.h"
#include "ITEMBASE.h"

struct ITEMDATA : public ITEMBASE
{
	struct ELEM_65
	{
		DWORD this_0 = 0;
		DWORD this_1 = 0;

		class CMenuOperation* pTypeIDData = nullptr;
	};

	struct ELEM_75
	{
		DWORD this_0 = 0;
		DWORD this_1 = 0;
		DWORD this_2 = 0;

		class CMenuOperation* pTypeIDData = nullptr;
	};

	struct ELEM_78
	{
		class CMenuOperation* pTypeIDData = nullptr;

		DWORD this_1 = 0;
	};

	DWORD res      = 0;
	DWORD itemType = 0;
	DWORD expGain  = 0;
	DWORD this_52  = 0;
	DWORD this_54  = 0;
	DWORD this_55  = 0;
	DWORD this_56  = 0;
	DWORD this_57  = 0;
	DWORD this_58  = 0;

	class CMenuOperation* m_pTypeIDData1 = nullptr;

	DWORD this_60 = 0;

	class CMenuOperation* m_pTypeIDData2 = nullptr;

	DWORD this_62[3] = { 0 };
	DWORD this_63[3] = { 0 };
	DWORD this_64[3] = { 0 };
	ELEM_65 this_65;
	DWORD this_66[12] = { 0 };
	DWORD this_67[2]  = { 0 };
	DWORD this_68[3]  = { 0 };
	DWORD this_69     = 0;
	DWORD this_70[2]  = { 0 };
	DWORD this_71     = 0;
	DWORD this_72[2]  = { 0 };
	DWORD this_73     = 0;
	DWORD this_74[4]  = { 0 };
	ELEM_75 this_75;
	SWITCHACTION this_76;
	DWORD this_77[3] = { 0 };
	ELEM_78 this_78;
	MemData this_79;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;

private:
	void sub_10E310(FileReader& fw);
};
