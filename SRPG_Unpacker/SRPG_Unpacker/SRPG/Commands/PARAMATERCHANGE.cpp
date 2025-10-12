/*
 *  File: PARAMATERCHANGE.cpp
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

// Compatible up to v1.317

#include "PARAMATERCHANGE.h"

void PARAMATERCHANGE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();

	sub_EBE310(fw);

	this_15 = fw.ReadDWord();
}

void PARAMATERCHANGE::dump(FileWriter& fw) const
{
	fw.Write(this_3);

	//////

	if (g_ArcVersion < 0x418)
	{
		fw.Write(this_4);
		fw.Write(this_5);
		fw.Write(this_6);
		fw.Write(this_7);
		fw.Write(this_8);
		fw.Write(this_9);
		fw.Write(this_10);
		fw.Write(this_11);
		fw.Write(this_12);
	}
	else
	{
		fw.Write(res);

		if (!res)
		{
			fw.Write(this_4);
			fw.Write(this_5);
			fw.Write(this_6);
			fw.Write(this_7);
			fw.Write(this_8);
			fw.Write(this_9);
			fw.Write(this_10);
			fw.Write(this_11);
			fw.Write(this_12);
			fw.Write(this_13);
			fw.Write(this_14);
		}
	}

	//////

	fw.Write(this_15);
}

void PARAMATERCHANGE::sub_EBE310(FileReader& fw)
{
	if (g_ArcVersion < 0x418)
	{
		this_4  = fw.ReadDWord();
		this_5  = fw.ReadDWord();
		this_6  = fw.ReadDWord();
		this_7  = fw.ReadDWord();
		this_8  = fw.ReadDWord();
		this_9  = fw.ReadDWord();
		this_10 = fw.ReadDWord();
		this_11 = fw.ReadDWord();
		this_12 = fw.ReadDWord();
	}
	else
	{
		res = fw.ReadDWord();

		if (res)
		{
			this_4  = 0;
			this_5  = 0;
			this_6  = 0;
			this_7  = 0;
			this_8  = 0;
			this_9  = 0;
			this_10 = 0;
			this_11 = 0;
			this_12 = 0;
			this_13 = 0;
			this_14 = 0;
		}
		else
		{
			this_4  = fw.ReadDWord();
			this_5  = fw.ReadDWord();
			this_6  = fw.ReadDWord();
			this_7  = fw.ReadDWord();
			this_8  = fw.ReadDWord();
			this_9  = fw.ReadDWord();
			this_10 = fw.ReadDWord();
			this_11 = fw.ReadDWord();
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
		}
	}
}
