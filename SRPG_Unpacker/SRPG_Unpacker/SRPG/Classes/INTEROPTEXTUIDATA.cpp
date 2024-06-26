/*
 *  File: INTEROPTEXTUIDATA.cpp
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

#include "INTEROPTEXTUIDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void INTEROPTEXTUIDATA::init(FileReader& fw)
{
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	INTEROPBASE::init(fw);

	// this_6 = (BYTE0(this_6) << 16) | (BYTE1(this_6) << 8) | BYTE2(this_6);
}

void INTEROPTEXTUIDATA::dump(FileWriter& fw) const
{
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);

	INTEROPBASE::dump(fw);
}
