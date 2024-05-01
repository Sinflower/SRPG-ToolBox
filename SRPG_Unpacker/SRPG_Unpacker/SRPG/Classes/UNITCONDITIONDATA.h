/*
 *  File: UNITCONDITIONDATA.h
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

struct UNITCONDITIONDATA : public EDITDATA
{
	DWORD this_3                      = 0;
	DWORD this_4                      = 0;
	DWORD this_5                      = 0;
	DWORD this_6                      = 0;
	DWORD this_7                      = 0;
	DWORD this_8                      = 0;
	DWORD this_9                      = 0;
	std::array<DWORD, 12> this_10     = { 0 };
	std::array<DWORD, 12> this_22     = { 0 };
	DWORD this_34                     = 0;
	DWORD this_35                     = 0;
	class CMenuOperation* pTypeIDData = nullptr;
	DWORD this_37                     = 0;
	DWORD this_38                     = 0;
	DWORD this_39                     = 0;
	DWORD this_40                     = 0;
	DWORD this_41                     = 0;
	DWORD this_42                     = 0;

	// NEW
	std::array<DWORD, 12> this_130;
	std::array<DWORD, 12> this_131;
	DWORD this_132 = 0;

	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
};
