/*
 *  File: BACKGROUNDCHANGE.cpp
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

// Compatible up to v1.292

#include "BACKGROUNDCHANGE.h"

void BACKGROUNDCHANGE::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), 28);

	if (g_ArcVersion >= 0x4E1)
	{
		this_11 = fw.ReadDWord();
		if (this_11 == 2 || this_11 == 3)
		{
			this_12 = fw.ReadDWord();
			this_13 = fw.ReadDWord();
			this_14 = fw.ReadDWord();
			this_15 = fw.ReadDWord();
		}
	}

	if (g_ArcVersion >= 0x4ED)
	{
		if (this_11)
			this_16 = fw.ReadDWord();
	}
}

void BACKGROUNDCHANGE::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), 28);

	if (g_ArcVersion >= 0x4E1)
	{
		fw.Write(this_11);
		if (this_11 == 2 || this_11 == 3)
		{
			fw.Write(this_12);
			fw.Write(this_13);
			fw.Write(this_14);
			fw.Write(this_15);
		}
	}

	if (g_ArcVersion >= 0x4ED)
	{
		if (this_11)
			fw.Write(this_16);
	}
}
