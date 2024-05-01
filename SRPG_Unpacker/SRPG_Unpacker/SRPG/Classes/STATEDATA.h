/*
 *  File: STATEDATA.h
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
#include "LEGENDDATA.h"

struct STATEDATA : public EDITDATA, public LEGENDDATA
{
	DWORD res     = 0;
	DWORD this_8  = 0;
	DWORD this_9  = 0;
	DWORD this_10 = 0;
	DWORD this_11 = 0;
	DWORD this_12 = 0;
	DWORD this_13 = 0;
	DWORD this_14 = 0;
	DWORD this_15 = 0;
	DWORD this_16 = 0;
	DWORD this_17 = 0;
	MemData this_18;
	class CMenuOperation* m_pTypeIDData = nullptr;
	DWORD this_31                       = 0;
	DWORD this_32                       = 0;
	DWORD this_33                       = 0;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;

private:
	DWORD this_19 = 0;
	DWORD this_20 = 0;
	DWORD this_21 = 0;
	DWORD this_22 = 0;
	DWORD this_23 = 0;
	DWORD this_24 = 0;
	DWORD this_25 = 0;
	DWORD this_26 = 0;
	DWORD this_27 = 0;
	DWORD this_28 = 0;
	DWORD this_29 = 0;
	DWORD this_34 = 0;
	MemData this_35;

	void sub_10E310(FileReader& fw);
};
